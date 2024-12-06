#include "HTTPSManager.h"

HTTPSManager& HTTPSManager::getInstance()
{
    static HTTPSManager instance;
    return instance;
}

size_t HTTPSManager::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) 
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}


void HTTPSManager::requestData(const std::string& url) 
{
    std::cout << "start request data....\n";
    CURL* curl;
    CURLcode res;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if (curl) 
    {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the write callback to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m_responseData);

        // Perform the GET request
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) 
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 
        else 
        {
            // Output the response
            std::cout << "curl_easy_perform() success\n";
            std::cout << "response data from server: " << m_responseData << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    } 
    else 
    {
        std::cerr << "Failed to initialize curl!" << std::endl;
    }

    // Global cleanup
    curl_global_cleanup();
    std::cout << "finish request data....\n";
}

void HTTPSManager::parserJsonData(const std::string& pattern)
{
    std::unique_lock<std::mutex> lock(m_mtx);

    cv.wait_for(lock, std::chrono::milliseconds(50), [&]()
    {
        std::cout << "wait for ...\n";
        return !m_responseData.empty();
    });

    if (m_responseData.empty()) 
    {
        std::cerr << "Received empty data, unable to parse." << std::endl;
        return;
    }

    try 
    {
        // Parse the string into a JSON object
        json json_data = json::parse(m_responseData);

        if(json_data.contains(pattern))
        {
            std::cout << pattern << ": " << json_data.at(pattern).dump(4) << std::endl;
        }
        else
        {
            std::cerr << "json data doesn't contains the field: " << pattern << std::endl; 
        }
    }
    catch (const json::parse_error& e) 
    {
        std::cerr << "Error decoding JSON: " << e.what() << std::endl;
    }
}