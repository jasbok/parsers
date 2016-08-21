cmake_minimum_required(VERSION 3.5)
project(parsers)

if(${UNIX})
add_definitions(-D_UNIX)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

# c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	message("c++11 Support: TRUE")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	message("c++11 Support: TRUE")
else()
	message(STATUS "${CMAKE_CXX_COMPILER} does not have C++11 support.")
endif()

# LibTidy
find_package(Tidy REQUIRED)
list(APPEND INCLUDE_DIRS ${TIDY_INCLUDE_DIRS})
list(APPEND TARGET_LINK_LIBS ${TIDY_LIBRARIES})

include_directories(${INCLUDE_DIRS})

list(APPEND STATIC_LIBS
    "css"
    "filter"
    "std"
    "tidy++"
)

add_subdirectory(catch)
add_subdirectory(cmake)
add_subdirectory(src)

FILE(GLOB_RECURSE H "*.h")
FILE(GLOB_RECURSE HPP "*.hpp")
add_custom_target(headers SOURCES ${H} ${HPP})
