cmake_minimum_required(VERSION 3.10)

project(pid-discreto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Adicione flags de compilação específicas para build Debug/Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(include src)

file(GLOB SOURCES
    "src/*.cpp" 
    "src/utils/*.cpp"
    "src/project/*.cpp"
    )

add_executable(${PROJECT_NAME} ${SOURCES})
