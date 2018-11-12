cmake_minimum_required(VERSION 2.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME "ARouter")
project(${PROJECT_NAME})


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#Find correct boost
#set(Boost_NO_BOOST_CMAKE ON)
#set(Boost_NO_SYSTEM_PATH ON)
#set(BOOST_ROOT $ENV{BOOST_ROOT})
#set(BOOST_LIBRARYDIR $ENV{BOOST_LIB})
#set(Boost_LIBRARY_DIRS $ENV{BOOST_LIB})
#set(Boost_INCLUDE_DIR $ENV{BOOST_INC})
#set(BOOST_INCLUDEDIR $ENV{BOOST_INC})
#set(BOOST_MIN_VERSION "1.60.0")

find_package(Boost 1.6 COMPONENTS system graph)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src
    ${BOOST_INCLUDEDIR}
                    )
                #$ENV{LEMON_INC}
                #link_directories(${BOOST_LIBRARYDIR})
                
file(GLOB SOURCES src/main/*.cpp
                  src/global/*.h    src/global/*.cpp
                  src/db/*.h        src/db/*.cpp
                  src/db/drDB/*.h   src/db/drDB/*.cpp
                  src/db/macroDB/*.h src/db/macroDB/*.cpp
                  src/db/techDB/*.h src/db/techDB/*.cpp
                  src/util/*.h      src/util/*.cpp 
                  src/parser/*.h    src/parser/*.cpp
                  src/gr/*.h        src/gr/*.cpp
                  src/dr/*.h        src/dr/*.cpp
                  src/grdr/*.h      src/grdr/*.cpp
                  src/extract/*.h   src/extract/*.cpp
                  src/parser/lefdef/*.h src/parser/lefdef/*.cpp src/parser/lefdef/*.cc
                  src/writer/gdsii/*.h src/writer/gdsii/*.cpp)

# def lef libraries
file(GLOB LEFDEF_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)
include_directories(include)

#Print out the used build type
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Using build type DEBUG")
    #ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Using build type RELEASE")
    #ENDIF(CMAKE_BUILD_TYPE MATCHES Release)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Profile)
    message(STATUS "Using build type PROFILE")
    #ENDIF(CMAKE_BUILD_TYPE MATCHES Profile)
ELSE()
    message(STATUS "Using build type DEFAULT")
ENDIF()
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -march=native -fopenmp ")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -march=native -fopenmp -fext-numeric-literals")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-inline ")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -frename-registers -fprofile-use -fprofile-correction") 
set(CMAKE_CXX_FLAGS_PROFILE "-Ofast -pg -Winline")
set(CMAKE_EXE_LINKER_FLAGS "-pthread")


message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

add_executable(ARouter ${SOURCES})

#link static libraries
target_link_libraries(ARouter 
                        ${LEFDEF_LIB})

message(status "** link lefdef libs: ${LEFDEF_LIB}")
