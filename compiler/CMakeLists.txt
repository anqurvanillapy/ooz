add_subdirectory(lib)

add_executable(oozc main.c)

target_link_libraries(oozc oozclib)

target_include_directories(oozc PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
