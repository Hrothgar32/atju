cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

project(atju VERSION 1.0)
find_package(Threads REQUIRED)

include_directories(./asio-1.18.1/include)

include_directories(headers)
add_library(drawer SHARED drawer.cpp rbtree.cpp node.cpp)
target_link_libraries(drawer libSDL_bgi.so)
add_library(server SHARED server.cpp rbtree.cpp task.cpp node.cpp)
target_link_libraries(server drawer ${CMAKE_THREAD_LIBS_INIT})
add_executable(atju main.cpp rbtree.cpp)
target_link_libraries(atju drawer server ${CMAKE_THREAD_LIBS_INIT})
add_executable(client client.cpp)
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})
