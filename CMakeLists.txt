cmake_minimum_required(VERSION 3.9)

#fixes wierd library shortname isssue
CMAKE_POLICY( SET CMP0060 NEW )

project(FactoryFactory)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(FactoryFactory Main.cpp)

target_link_libraries(FactoryFactory)
