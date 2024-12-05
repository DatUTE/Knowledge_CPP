// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <memory>
#include <curl/curl.h>
#include "TaskWorker.h"

// This function will be called to write the response data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) 
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

void GetData(const std::string& url) {
    CURL* curl;
    CURLcode res;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the write callback to capture the response
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Perform the GET request
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Output the response
            std::cout << "Response:\n" << response_string << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize curl!" << std::endl;
    }

    // Global cleanup
    curl_global_cleanup();
}

int main() {
    // URL to make GET request to
    std::string url = "https://catfact.ninja/fact"; // Replace with your desired URL
    std::string url2 = "https://jsonplaceholder.typicode.com/posts/1"; // Replace with your desired URL
    std::string url3 = "https://jsonplaceholder.typicode.com/posts/2"; // Replace with your desired URL
    std::unique_ptr<TaskWorker> worker = std::make_unique<TaskWorker>();

    auto callback = [&](const std::string& url)
    {
        GetData(url);
    };
    worker->setCallback(callback);
    
    /* Using std::this_thread::sleep_for to simulate some work 
        between pushData to trigger request Data from server
    */
    worker->runThread();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    worker->pushData(url);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    worker->pushData(url2);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    //worker->stop();
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    worker->pushData(url3);

    // Let the worker thread process the data
    // The thread loop will query data from server within 10s continuously
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}