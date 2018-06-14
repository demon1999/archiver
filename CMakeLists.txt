cmake_minimum_required(VERSION 2.8)

project(archiver)

include_directories(${archiver_SOURCE_DIR})

add_executable(archiver
        file_lib.h
        #bit_queue.h
        bit_queue.cpp
        #dictionary.h
        dictionary.cpp
        #encoder.h
        encoder.cpp
        #decoder.h
        decoder.cpp
        main.cpp)
#        archiver_test.cpp
#        gtest/gtest-all.cc
#        gtest/gtest.h
#        gtest/gtest_main.cc)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(archiver -lgmp -lgmpxx -lpthread)