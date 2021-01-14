cmake_minimum_required(VERSION 3.10)

project(wolfgang_chat VERSION 1.0.0)

include_directories(/home/duco/development/cpp/packages/d/asio-1.18/asio-1.18.1/include)

add_executable(wolfgang_chat main.cpp)

# -pThreads required for ASIO
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(wolfgang_chat PRIVATE Threads::Threads)

# Libary
target_link_libraries(wolfgang_chat PUBLIC MathFunc)

# Define c++ version 17
target_compile_features(wolfgang_chat PRIVATE cxx_std_17)

# Link MathFunc library
add_subdirectory(MathFunc)
target_include_directories(wolfgang_chat PUBLIC
                          "${PROJECT_SOURCE_DIR}/MathFunc"
                          )
