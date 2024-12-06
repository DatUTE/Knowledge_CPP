#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace nlohmann;

class HTTPSManager
{
public:

    /**
     * @brief Deleted copy/move constructor and copy/move assigment operator
     * for the HTTPSManager class.
     * 
     * The copy/move constructor and copy/move assigment operator is deleted 
     * to prevent copying and moving of the singleton instance.
     * A singleton should have only one instance, and copying it would violate this design.
     */
    HTTPSManager(HTTPSManager& other) = delete;
    HTTPSManager& operator=(const HTTPSManager& other) = delete;
    HTTPSManager(HTTPSManager&& other) = delete;
    HTTPSManager& operator=(const HTTPSManager&& other) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static HTTPSManager& getInstance();

    /*!
     * @brief This function to init the connection to url and get data from this
     *
     * @param[in] url is the url to request data.
     */
    void requestData(const std::string& url);

    /*!
     * @brief This function to parser data is get from server after request.
     * It will parser data corresponding the pattern as the field of json.
     *
     * @param[in] pattern is the field of json.
     */
    void parserJsonData(const std::string& pattern);

private:

    // put ctor to private to prevent create a new instance by new operator
    HTTPSManager() = default;

    // This function will be called to write the response data into a string
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

    std::string m_responseData;
    std::mutex m_mtx;
    std::condition_variable cv;
};