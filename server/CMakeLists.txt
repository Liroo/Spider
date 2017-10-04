cmake_minimum_required(VERSION 3.9.3)
set(CMAKE_BUILD_TYPE Release)
project(server)

set 			(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

#######################
# Resolve dependencies
#######################

find_package(Boost REQUIRED COMPONENTS)

message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

set			(SRC          main.cpp)

set			(CORE_SRC     core.cpp)


PREPEND(RELEASE_SRC "src" ${SRC})
PREPEND(RELEASE_CORE_SRC "../msu/src" ${CORE_SRC})

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../shared)

add_executable(server ${RELEASE_SRC} ${RELEASE_CORE_SRC})

target_link_libraries(server ${BOOST_LIBRARIES})

#######################
# Flags
#######################

if (UNIX)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -g -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -W -Wall")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()
if (WIN32)
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
# Todo OSX
if (OSX)
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
