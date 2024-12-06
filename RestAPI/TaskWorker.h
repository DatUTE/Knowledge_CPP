#include <iostream>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <mutex>
#include <chrono>
#include <queue>
#include <thread>

// Callback function type definition
using Task = std::function<void(const std::string& url)>;


class TaskWorker
{
    public:
    TaskWorker() = default;

    // Thread-safe function to push data to the queue
    void pushData(const std::string& url);

    // Worker thread function that processes data from the queue
    void threadLoop();

    void runThread();

    // Stop the worker thread (for cleanup or shutdown)
    void stop();

    void setCallback(Task p_task) {m_task = p_task;}

    private:
    Task m_task;
    std::condition_variable cv;
    std::atomic<bool> isRunning {false};
    std::mutex m_mtx;
    std::mutex queueMutex;
    std::queue<std::string> m_queue;
};