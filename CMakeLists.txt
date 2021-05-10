cmake_minimum_required(VERSION 3.19)
project(feup_cal_parking)

set(CMAKE_CXX_STANDARD 14)

add_executable(feup_cal_parking src/main.cpp src/model/Graph/Graph.h src/model/Graph/Node.h src/model/MapPoint/MapPoint.cpp src/model/MapPoint/MapPoint.h src/model/Graph/Edge.h)