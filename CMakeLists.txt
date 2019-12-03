cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(capstone)

find_package(OpenCV REQUIRED)
#[[
message(STATUS "OpenCV library status:")
message(STATUS "    config:  ${OpenCV_DIR}")
message(STATUS "    version:  ${OpenCV_VERSION}")
message(STATUS "    libraries:  ${OpenCV_LIBS}")
message(STATUS "    include path:  ${OpenCV_INCUDE_DIRS}")
]]
add_executable(capstone src/main.cpp)

target_link_libraries(capstone LINK_PRIVATE ${OpenCV_LIBS})