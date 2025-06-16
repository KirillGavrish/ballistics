project(test_ballistics)

find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES ./*test_*.cpp)

foreach (TEST_FILE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    set(EXECUTABLE_NAME run_${TEST_FILE_NAME})

    add_executable(${EXECUTABLE_NAME} ${TEST_FILE} Paths.cpp)

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ballistics gtest gtest_main)
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach ()