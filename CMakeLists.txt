cmake_minimum_required(VERSION 3.15)
project(Effective_STL)

set(CMAKE_CXX_STANDARD 11)

include_directories(src src/Knowledge_Surrounding)
add_executable(effective_stl src/Knowledge_Surrounding/MethodObjectPointLearn.cpp src/EffectiveStl.cpp src/StlElementIsPoint.cpp src/EffectiveStlRule.cpp )