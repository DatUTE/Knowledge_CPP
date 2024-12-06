// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <memory>
#include <string_view> 
#include "TaskWorker.h"
#include "HTTPSManager.h"

int main() 
{
    // URL to make GET request to
    // std::string url = "https://catfact.ninja/fact"; // Replace with your desired URL
    std::string url2 = "https://jsonplaceholder.typicode.com/posts/1"; // Replace with your desired URL
    // std::string url3 = "https://jsonplaceholder.typicode.com/posts/2"; // Replace with your desired URL
    std::unique_ptr<TaskWorker> worker = std::make_unique<TaskWorker>();

    auto callback = [&](const std::string& p_url)
    {
        HTTPSManager::getInstance().requestData(p_url);
    };
    worker->setCallback(callback);
    
    /* Using std::this_thread::sleep_for to simulate some work 
        between pushData to trigger request Data from server
    */
    worker->runThread();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    worker->pushData(url2);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    HTTPSManager::getInstance().parserJsonData("title");

    // worker->pushData(url2);
    // std::this_thread::sleep_for(std::chrono::milliseconds(300));

    // //worker->stop();
    // //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // worker->pushData(url3);

    // Let the worker thread process the data
    // The thread loop will query data from server within 10s continuously
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return 0;
}