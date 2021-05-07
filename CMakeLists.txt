cmake_minimum_required(VERSION 3.19)
project(feup_cal_parking)
include(CTest)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 14)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

file(GLOB CAL_PARKING CONFIGURE_DEPENDS "test/*.cpp")

add_executable(TESTS test/test.cpp ${TESTS_FILES})
add_executable(feup_cal_parking src/main.cpp src/model/Graph/Graph.h src/model/Graph/Node.h src/model/MapPoint/MapPoint.cpp src/model/MapPoint/MapPoint.h src/model/Graph/Edge.h test/test.cpp)

target_link_libraries(TESTS gtest_main gmock_main)