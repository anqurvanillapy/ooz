file(GLOB_RECURSE SRC_FILES *.c)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(oozrt STATIC
  ${SRC_FILES}
  ${HEADER_FILES}
)

target_include_directories(oozrt PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(oozrt PRIVATE ${STRICT_FLAGS})
