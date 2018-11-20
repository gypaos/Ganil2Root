cmake_minimum_required (VERSION 2.8)
include(CheckCXXCompilerFlag)
project(Ganil2Root CXX)
set(CMAKE_BUILD_TYPE Release)

# Setting the policy to match Cmake version
cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
# Finding NPLib
message("Looking for nplib: ")
find_package(NPLib)
include(${NPLib_USE_FILE})
message("  found: ${NPLIB}")
message("  include directory: ${NPLib_INCLUDE_DIRS}")
message("  detector list (empty if all): ${NPLib_DETECTOR_LIST}")


# include the G2R standard CMake preamble 
include("ressources/CMake/CMake_Preamble.cmake")
# Major change in the Core/Physics (affecting the detector/analysis/simulation)
set(Ganil2Root_VERSION_MAJOR 3)
# Minor change in the Core/Physics (not affecting any other part)
set(Ganil2Root_VERSION_MINOR 0)
# Change any of the detector in NPA
set(Ganil2Root_VERSION_PATCH 0)

set(CMAKE_BINARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/include )
add_definitions(-DNET_LIB=1)
# Add include directories to all target
# Finding GRU 
message(" using GRU from : $ENV{GRUDIR}")
link_directories( $ENV{GRUDIR}/MFMlib)
link_directories( $ENV{GRUDIR}/lib)
# Include directories
include_directories($ENV{GRUDIR}/include $ENV{GRUDIR}/MFMlib)
message(" GRU lib : $ENV{GRUDIR}/lib and $ENV{GRUDIR}/MFMlib")
message(" GRU include : $ENV{GRUDIR}/include and $ENV{GRUDIR}/MFMlib")


message("include : ${INCLUDE_DIRECTORIES}")
# General directory
include_directories("Core")

# Core 
add_subdirectory("Core")

# Core 
add_subdirectory("Detectors/Must2")
add_subdirectory("Detectors/Exl")
# add_subdirectory("Detectors/PPT")
add_subdirectory("Detectors/CATS")
add_subdirectory("Detectors/Chio")
add_subdirectory("Detectors/Numexo2")
add_subdirectory("Detectors/ICNumexo")
add_subdirectory("Detectors/DCNumexo")

