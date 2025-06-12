file(GLOB_RECURSE SOURCES *.h *.cpp *.hpp *.c)

add_library(calceph ${SOURCES})
target_include_directories(calceph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})