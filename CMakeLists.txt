cmake_minimum_required(VERSION 3.17)
project(Series_Dashboard VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(CURLPP REQUIRED curlpp)
pkg_check_modules(JSON REQUIRED nlohmann_json)

include_directories(${GTKMM_INCLUDE_DIRS} ${CURLPP_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS} ${CURLPP_LIBRARY_DIRS} ${JSON_LIBRARY_DIRS})

add_executable(Series_Dashboard src/main.cpp src/Dashboard.cpp src/Dashboard.h src/Entry.cpp src/Entry.h src/Config.cpp src/Config.h src/ApiData.cpp src/ApiData.h src/PreferencesWindow.cpp src/PreferencesWindow.h src/AddNewWindow.cpp src/AddNewWindow.h)

target_link_libraries(Series_Dashboard ${GTKMM_LIBRARIES} ${CURLPP_LIBRARIES} ${JSON_LIBRARIES})