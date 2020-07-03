cmake_minimum_required(VERSION 3.17)
project(Series_Dashboard)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(CURLPP REQUIRED curlpp)

include_directories(${GTKMM_INCLUDE_DIRS} ${CURLPP_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS} ${CURLPP_INCLUDE_DIRS})

add_executable(Series_Dashboard src/main.cpp)

target_link_libraries(Series_Dashboard ${GTKMM_LIBRARIES} ${CURLPP_LIBRARIES})