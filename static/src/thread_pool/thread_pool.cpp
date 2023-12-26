#include "thread_pool.h"
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
            std::unique_lock<std::mutex> lock(return_values);
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