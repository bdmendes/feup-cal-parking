cmake_minimum_required(VERSION 3.19)
project(feup_cal_parking)
include(CTest)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 14)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Tests executables
add_executable(TESTS test/test.cpp test/algorithm/mtest.cpp src/model/Graph/Graph.h src/model/Graph/Node.h src/model/MapPoint/MapPoint.cpp src/model/MapPoint/MapPoint.h src/model/Graph/Edge.h)
target_link_libraries(TESTS gtest_main gmock_main)
add_test(NAME TESTS COMMAND TESTS)

# Main executable
add_executable(feup_cal_parking src/main.cpp src/model/Graph/Graph.h src/model/Graph/Node.h src/model/MapPoint/MapPoint.cpp src/model/MapPoint/MapPoint.h src/model/Graph/Edge.h src/algorithms/search.h src/model/StreetMap/StreetMap.h src/view/GraphviewerGUI.cpp src/view/GraphviewerGUI.h src/model/StreetMap/StreetMap.cpp src/model/DriverWay/DriverWay.cpp src/model/DriverWay/DriverWay.h src/model/MapPoint/Park.cpp src/model/MapPoint/Park.h)

target_link_libraries(feup_cal_parking graphviewer)

