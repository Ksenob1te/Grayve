#ifndef GRAYVE_THREADPOOL_H
#define GRAYVE_THREADPOOL_H
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

template<typename T>
class ThreadPool {
public:
    void Start();
    void QueueJob(const std::function<T()>& job);
    void Stop();
    bool busy();
    std::vector<T> return_values;
private:
    void ThreadLoop();

    bool should_terminate = false;           
    std::mutex queue_mutex;                  
    std::condition_variable mutex_condition; 
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
};

#endif //GRAYVE_THREADPOOL_H
