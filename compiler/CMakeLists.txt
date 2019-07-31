add_subdirectory(lib)

find_package(FLEX)
find_package(BISON)

flex_target(lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.ll.c)
bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.yy.c)
add_flex_bison_dependency(lexer parser)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_LIST_DIR}
  ${PROJECT_SOURCE_DIR}/include
)


add_executable(oozc
  ${FLEX_lexer_OUTPUTS}
  ${BISON_parser_OUTPUTS}
)

target_link_libraries(oozc oozclib)
