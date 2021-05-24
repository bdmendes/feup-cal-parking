cmake_minimum_required(VERSION 3.19)
project(feup_cal_parking)
include(CTest)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 14)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp-1.1.0)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Tests executables
add_executable(TESTS test/test.cpp test/algorithm/shortestdistance_test.cpp src/model/Graph/Graph.hpp src/model/Graph/Node.hpp src/model/StreetMap/MapPoint.cpp src/model/StreetMap/MapPoint.h src/model/Graph/Edge.hpp test/algorithm/search_test.cpp test/algorithm/tsp_test.cpp)

target_link_libraries(TESTS gtest_main gmock_main)
add_test(NAME TESTS COMMAND TESTS)

# Main executable
add_executable(feup_cal_parking src/main.cpp src/model/Graph/Graph.hpp src/model/Graph/Node.hpp src/model/StreetMap/MapPoint.cpp src/model/StreetMap/MapPoint.h src/model/Graph/Edge.hpp src/algorithms/search.hpp src/model/StreetMap/StreetMap.h src/model/StreetMap/StreetMap.cpp src/algorithms/tsp.hpp lib/MutablePriorityQueue.h src/algorithms/shortestdistance.hpp src/controller/connectivity.hpp src/controller/parkselector.cpp src/controller/parkselector.h)

target_link_libraries(feup_cal_parking graphviewer)

