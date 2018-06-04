cmake_minimum_required(VERSION 3.10)
project(combinatorial-objects)
set(CMAKE_CXX_STANDARD 14)

set(name gray_code)
set(incpath ../combinatorial_object)
set(sources ${name}.cpp runner.cpp ${incpath}/combinatorial_object.cpp)
set(headers ${name}.h ${incpath}/combinatorial_object.h)

include_directories(${incpath})
add_custom_target(${name} DEPENDS ${sources} ${headers} COMMAND g++ -I${incpath} --std=c++14 -Wall ${sources} -o ${name})
add_executable(combinatorial-objects ${sources} ${headers})