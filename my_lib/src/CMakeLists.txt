file(GLOB_RECURSE SOURCES Ballistics/*.h Ballistics/*.c Ballistics/*.hpp Ballistics/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
message(${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC eigen sofa GeographicLib calceph)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

