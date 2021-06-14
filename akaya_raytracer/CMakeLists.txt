# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(ayaka_raytracer)
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
# -------------------------------------------------------------------------------
file(GLOB AYAKA_SRC "core/*.h" "core/*.cpp")
add_executable(ayaka_raytracer ${AYAKA_SRC} main.cpp)
target_include_directories(ayaka_raytracer
	PRIVATE
	${PROJECT_SOURCE_DIR}/core
	${ASSIMP_DIR}/include
)
target_link_libraries(ayaka_raytracer ${OpenCV_LIBRARIES})
# -------------------------------------------------------------------------------
add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")