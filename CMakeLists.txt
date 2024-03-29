cmake_minimum_required(VERSION 3.9)

project(ooz
  LANGUAGES C CXX
  VERSION 0.0.1
  DESCRIPTION "OOZ compiler"
)

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(
    -O0
    -g3
    --coverage
    -fprofile-arcs
    -ftest-coverage
  )
  link_libraries(gcov)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  add_definitions(
    -O3
  )
else()
  message(FATAL_ERROR "Unrecognised build type")
endif()

set(STRICT_FLAGS
  "-Werror"
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  "-Wshadow"
  "-Wcast-align"
  "-Wunused"
  "-Wconversion"
  "-Wsign-conversion"
  "-Wduplicated-cond"
  "-Wduplicated-branches"
  "-Wlogical-op"
  "-Wnull-dereference"
  "-Wdouble-promotion"
  "-Wformat=2"
)

include(CTest)
enable_testing()
add_subdirectory(3rdparty/googletest)
add_subdirectory(test)

add_subdirectory(compiler)
add_subdirectory(rt)
