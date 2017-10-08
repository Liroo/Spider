cmake_minimum_required(VERSION 3.9.3)
set(CMAKE_BUILD_TYPE Release)
project(cpp_spider_server)

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

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)

find_package(Boost REQUIRED COMPONENTS system regex date_time thread serialization)

message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

set(OPENSSL_USE_STATIC_LIBS ON)

find_package(OpenSSL REQUIRED)

message(status "** OpenSSL Include: ${OPENSSL_INCLUDE_DIR}")
message(status "** OpenSSL Libraries: ${OPENSSL_LIBRARIES}")

set			(SRC          mainTestsServer.cpp)
set			(TEST          testssl.cpp)

set			(MSU_SRC      core.cpp
                      network.cpp
                      session.cpp
                      plugin/key.cpp
                      plugin/timestamp.cpp
                      plugin/mouse.cpp
                      plugin/process.cpp
                      plugin/addrMac.cpp
        )


PREPEND(RELEASE_SRC "server/src" ${SRC})
PREPEND(RELEASE_MSU_SRC "msu/src" ${MSU_SRC})
PREPEND(TEST "msu/src" ${TEST})

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(msu/include)

#${RELEASE_SRC} ${RELEASE_MSU_SRC}

add_executable(cpp_spider_server ${RELEASE_SRC} ${RELEASE_MSU_SRC})

target_link_libraries(cpp_spider_server crypto ${Boost_LIBRARY_DIRS} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

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
