cmake_minimum_required(VERSION 3.19)
project(feup_cal_parking)

set(CMAKE_CXX_STANDARD 14)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

add_executable(feup_cal_parking src/main.cpp src/model/Graph/Graph.h src/model/Graph/Node.h src/model/MapPoint/MapPoint.cpp src/model/MapPoint/MapPoint.h src/model/Graph/Edge.h src/algorithms/search.h src/model/StreetMap/StreetMap.h src/view/GraphviewerGUI.cpp src/view/GraphviewerGUI.h src/model/StreetMap/StreetMap.cpp)

target_link_libraries(feup_cal_parking graphviewer)