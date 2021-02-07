cmake_minimum_required(VERSION 3.0.0)

include_directories(include)

add_library(utf8 
    OBJECT src/utf8.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC include)

target_compile_features(utf8 
    PUBLIC c_std_11)  
