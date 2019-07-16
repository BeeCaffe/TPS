cmake_minimum_required(VERSION 3.14)
project(TPS)

set(CMAKE_CXX_STANDARD 14)
FIND_PACKAGE(OpenCV 3 REQUIRED)
SET(
        EXTERNAL_LIBS
        ${OpenCV_LIBS}
)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
ADD_SUBDIRECTORY(src/tps)
ADD_SUBDIRECTORY(src/test)
add_executable(TPS main.cpp src/tps/Tps.cpp src/tps/Tps.h src/utils/utils.cpp src/utils/utils.h)
TARGET_LINK_LIBRARIES(TPS ${EXTERNAL_LIBS})