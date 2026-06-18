#include "TaskWorker.h"

void TaskWorker::pushData(const std::string& url)
{
    // Lock the queue while pushing data
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        std::cout <<"=========================================\n";
        std::cout << "push data with url: " << url << std::endl;
        m_queue.push(url);
    }

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
        cv.wait_for(lock, std::chrono::milliseconds(100), [&]()
        {
            return !m_queue.empty() || !isRunning;
        });
        std::cout << "m_queue.empty() = " << m_queue.empty() << std::endl;
        std::cout << "\n";
        while(!m_queue.empty())
        {
            auto url = m_queue.front();
            std::cout << "get data from link: " << url << std::endl;
            m_queue.pop();

            // Unlock mutex before calling callback so pushData can proceed
            lock.unlock();
            m_task(url);
            lock.lock();
        }
    }
}

void TaskWorker::stop() 
{
    std::cout << "stop thread loop\n";
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        isRunning = false;
    }
    cv.notify_all();
}

void TaskWorker::runThread()
{
    isRunning = true;
    std::thread worker(std::bind(&TaskWorker::threadLoop, this));

    // Detach the worker thread so it runs independently
    worker.detach();
}
