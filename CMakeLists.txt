cmake_minimum_required(VERSION 3.15.0)

project(
  R136 
  VERSION 3.3.1)

set(CURSES_NEED_NCURSES 1)
set(CURSES_NEED_WIDE 1)

add_compile_definitions(_XOPEN_SOURCE_EXTENDED CURSES_WIDE)

find_package(Curses)

if (NOT CURSES_FOUND)
  find_path(PDC_INCLUDES curses.h)
  find_library(PDC_LIBS pdcurses REQUIRED)
  add_compile_definitions(PDC_WIDE)
elseif (CURSES_HAVE_NCURSES_H)
  add_compile_definitions(HAVE_NCURSES_H)
elseif(CURSES_HAVE_NCURSES_NCURSES_H)
  add_compile_definitions(HAVE_NCURSES_NCURSES_H)
elseif(CURSES_HAVE_NCURSES_CURSES_H)
  add_compile_definitions(HAVE_NCURSES_CURSES_H)
endif()

include_directories(include)

add_executable(
  ${PROJECT_NAME} 
  main.cpp 
)

add_subdirectory(src)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11 cxx_std_14)

if (CURSES_FOUND)
  target_include_directories(${PROJECT_NAME} PRIVATE ${CURSES_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
else()
  target_include_directories(${PROJECT_NAME} PRIVATE ${PDC_INCLUDES})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PDC_LIBS})
endif() 