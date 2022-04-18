cmake_minimum_required(VERSION 3.5)

project(NDITracking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT_FILE ROOT_FILE <NDI-master 路径>) # 修改NDI-master的路径

INCLUDE_DIRECTORIES(${ROOT_FILE}/library/include )
set(NDI_LIB ${ROOT_FILE}/build/linux/libndicapi.so)

find_package(ndicapi REQUIRED)
INCLUDE_DIRECTORIES(${ndicapi_INCLUDE_DIRS})

add_executable(NDITracking mytracking.cpp )
target_link_libraries(NDITracking ${NDI_LIB} ${ndicapi_LIBRARIES})

