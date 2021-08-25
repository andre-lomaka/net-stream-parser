cmake_minimum_required(VERSION 3.16.3)

project(net-stream-parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.71.0 REQUIRED COMPONENTS system thread regex)

add_executable(net-stream-parser
               net-stream-parser/main.cpp
               net-stream-parser/DeviceData.cpp
               net-stream-parser/Server.cpp
               net-stream-parser/Session.cpp
               net-stream-parser/StreamParser.cpp
               net-stream-parser/util.cpp)

target_include_directories(net-stream-parser PUBLIC
       ${Boost_INCLUDE_DIRS}
)

target_link_libraries(net-stream-parser PUBLIC
       Boost::system
       Boost::thread
       Boost::regex
)
