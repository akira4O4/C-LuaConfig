cmake_minimum_required(VERSION 3.10)  # 设置CMake最低版本

project(cpplua)               
set(CMAKE_CXX_STANDARD 14)           
set(BIN_NAME "main")

find_package(Lua 5.3 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})
include_directories("src")

add_executable(${BIN_NAME} main.cc)

target_link_libraries(${BIN_NAME} ${LUA_LIBRARIES})