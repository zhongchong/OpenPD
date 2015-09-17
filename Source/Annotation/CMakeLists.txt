# -----------------------------------------------------------------------
#   Destription: Annotation Project CMake file
#   Author: Zhong Chong
#   Date: 2015-9-14
# -----------------------------------------------------------------------

SET(SRC_LIST ImageAnnotate.cpp main.cpp)
INCLUDE_DIRECTORIES(/usr/local/include/opencv /usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

ADD_EXECUTABLE(Annotation ${SRC_LIST})
SET(CMAKE_CXX_FLAGS "-std=c++11")

SET(EXECUATABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
TARGET_LINK_LIBRARIES(Annotation libopencv_core.so libopencv_highgui.so
    libopencv_imgproc.so libopencv_imgcodecs.so)
