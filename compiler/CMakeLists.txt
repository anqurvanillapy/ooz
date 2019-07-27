add_subdirectory(lib)

add_executable(oozc main.c)

target_link_libraries(oozc oozclib)
