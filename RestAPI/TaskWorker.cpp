#include "TaskWorker.h"

void TaskWorker::pushData(const std::string& data)
{
    // Lock the queue while pushing data
    std::lock_guard<std::mutex> lock(queueMutex);

    m_queue.push(data);

    // Notify worker thread that new data is available
    cv.notify_one();
}

void TaskWorker::threadLoop()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    std::cout << "isRunning = " << isRunning << std::endl;
    while(isRunning)
    {
        // Wait until there is data in the queue or stop flag is set
        // cv will check condition check very second because we set it in wait_for
        cv.wait_for(lock, std::chrono::seconds(1), [&]()
        {
            return !m_queue.empty();
        });

        std::cout << "m_queue.empty() = " << m_queue.empty() << std::endl;
        std::cout << "\n";
        if(!m_queue.empty())
        {
            std::lock_guard<std::mutex> queueLock(queueMutex);
            auto data = m_queue.front();
            std::cout << "get data from link: " << data << std::endl;

            // Unlock mutex before calling callback to avoid deadlock
            lock.unlock();

            m_queue.pop();

            // Execute the callback with the data
            m_task(data);
            lock.lock();
        }
    }
}

void TaskWorker::stop() 
{
    std::cout << "stop thread loop\n";
    isRunning = false;

    // Ensure the worker exits if it's waiting
    cv.notify_all();
}

void TaskWorker::runThread()
{
    isRunning = true;
    std::thread worker(std::bind(&TaskWorker::threadLoop, this));

    // Detach the worker thread so it runs independently
    worker.detach();
}