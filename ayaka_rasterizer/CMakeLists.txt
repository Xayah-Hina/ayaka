# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(ayaka_rasterizer)
set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
# -------------------------------------------------------------------------------
find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
# -------------------------------------------------------------------------------
# -------------------------------------------------------------------------------
include_directories(
        ${PROJECT_SOURCE_DIR}/core
        ${PROJECT_SOURCE_DIR}/utils
        )
# -------------------------------------------------------------------------------
file(GLOB AYAKA_SRC "core/*.h" "core/*.cpp")
file(GLOB TEST_SRC "test/*.cpp")
file(GLOB SAMPLES "samples/*.cpp")

foreach (file ${SAMPLES})
    get_filename_component(clippedfile ${file} NAME_WE)
    message(${clippedfile})
    add_executable(${clippedfile} ${AYAKA_SRC} ${file})
    target_link_libraries(${clippedfile} ${OpenCV_LIBRARIES})
endforeach (file ${FILES})
# -------------------------------------------------------------------------------
add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")