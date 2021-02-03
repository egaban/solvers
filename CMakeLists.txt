project(SCIP_CPP_WRAPPER)

cmake_minimum_required(VERSION 3.13)

add_library(scip_cpp
  src/Constraint.cpp
  src/Exception.cpp
  src/Model.cpp
  src/Variable.cpp
)

find_package(scip REQUIRED
  HINTS
    /usr/local/scipoptsuite-6.0.2/build
)

target_include_directories(scip_cpp
  PUBLIC
    include/
    ${SCIP_INCLUDE_DIRS}
)

target_link_libraries(scip_cpp ${SCIP_LIBRARIES})

add_executable(knapsack tests/knapsack.cpp)
target_link_libraries(knapsack scip_cpp)
