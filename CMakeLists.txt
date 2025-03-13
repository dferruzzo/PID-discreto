cmake_minimum_required(VERSION 3.10)

project(cpp-codespace-project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/utils/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

enable_testing()
add_subdirectory(tests)