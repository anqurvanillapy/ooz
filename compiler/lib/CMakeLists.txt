file(GLOB_RECURSE SRC_FILES *.c)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(oozclib STATIC
  ${SRC_FILES}
  ${HEADER_FILES}
)

target_include_directories(oozclib PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
