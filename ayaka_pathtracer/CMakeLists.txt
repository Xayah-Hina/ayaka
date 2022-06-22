# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(AyakaPathTracer)

# -------------------------------------------------------------------------------
# ADD DEPENDENCIES
if (MSVC)
	include(E:/Git_Repos/vcpkg/scripts/buildsystems/vcpkg.cmake)
	find_path(VCPKG_INCLUDE_DIR zlib.h)
	include_directories(${VCPKG_INCLUDE_DIR})
endif ()

if (APPLE)
	include_directories(/opt/homebrew/include)
endif ()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
# -------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)

# -------------------------------------------------------------------------------
add_subdirectory(opencv_viewer)
file(GLOB_RECURSE AYAKA_SRC "src/*.h" "src/*.cpp")
add_executable(ayaka_pathtracer ${AYAKA_SRC} main.cpp)
target_link_libraries(ayaka_pathtracer ViewerOpenCV)
# -------------------------------------------------------------------------------
# -------------------------------------------------------------------------------
# -------------------------------------------------------------------------------