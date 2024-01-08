#ifndef GRAYVE_THREADPOOL_H
#define GRAYVE_THREADPOOL_H
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

/**
 * @class ThreadPool
 * @brief A basic thread pool implementation for managing concurrent tasks.
 * @tparam T The return type of the tasks.
 */
template<typename T>
class ThreadPool {
public:
    /**
     * @brief Initializes the thread pool and starts worker threads.
     */
    void Start();

    /**
     * @brief Queues a new job to be executed by the thread pool.
     * @param job The job to be executed.
     */
    void QueueJob(const std::function<T()>& job);

    /**
     * @brief Stops all worker threads and terminates the thread pool.
     */
    void Stop();

    /**
     * @brief Checks if there are any jobs pending in the thread pool.
     * @return True if there are pending jobs, false otherwise.
     */
    bool busy();

    std::vector<T> return_values; /**< Vector to store return values from completed jobs. */

private:
    /**
     * @brief Function that represents the main loop for each worker thread.
     */
    void ThreadLoop();

    bool should_terminate = false; /**< Flag to signal termination of the thread pool. */
    std::mutex queue_mutex; /**< Mutex to protect access to the job queue. */
    std::mutex vector_mutex; /**< Mutex to protect access to the return values vector. */
    std::condition_variable mutex_condition; /**< Condition variable for synchronization. */
    std::vector<std::thread> threads; /**< Collection of worker threads. */
    std::queue<std::function<T()>> jobs; /**< Queue for storing jobs. */
};

template<typename T>
void ThreadPool<T>::Start() {
    const uint32_t num_threads = std::thread::hardware_concurrency();
    for (uint32_t ii = 0; ii < num_threads; ++ii) {
        threads.emplace_back(std::thread(&ThreadPool::ThreadLoop,this));
    }
}

template<typename T>
void ThreadPool<T>::ThreadLoop() {
    while (true) {
        std::function<T()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, [this] {
                return !jobs.empty() || should_terminate;
            });
            if (should_terminate) {
                return;
            }
            job = jobs.front();
            jobs.pop();
        }
        T value = job();
        {
            std::unique_lock<std::mutex> lock(vector_mutex);
            return_values.push_back(value);
        }
    }
}

template<typename T>
void ThreadPool<T>::QueueJob(const std::function<T()>& job) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

template<typename T>
bool ThreadPool<T>::busy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        poolbusy = !jobs.empty();
    }
    return poolbusy;
}

template<typename T>
void ThreadPool<T>::Stop() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (std::thread& active_thread : threads) {
        active_thread.join();
    }
    threads.clear();
}

#endif //GRAYVE_THREADPOOL_H
