cmake_minimum_required(VERSION 3.0.0)

project(
    R136 
    VERSION 3.1.0)

find_library(CURSES_LIBRARY 
    NAMES pdcurses ncursesw ncurses 
    REQUIRED)

include_directories(include)

add_executable(
    ${PROJECT_NAME} 
    main.cpp 
    src/console.cpp 
    src/init.cpp 
    src/intro.cpp 
    src/loadsave.cpp 
    src/random.cpp 
    src/status.cpp 
    src/use.cpp
    $<TARGET_OBJECTS:utf8>)

add_subdirectory(utf8)

target_compile_features(${PROJECT_NAME}
    PUBLIC
    cxx_std_14
)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
