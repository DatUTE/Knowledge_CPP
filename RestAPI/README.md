# Step to run example curl:

1. sudo apt-get update
2. sudo apt-get install libcurl4-openssl-dev
3. sudo apt install nlohmann-json3-dev
4. sudo apt install g++
5. compile: g++ \
    main.cpp \
    HTTPSManager.cpp \
    TaskWorker.cpp \
    -o get_request \
    -lcurl
