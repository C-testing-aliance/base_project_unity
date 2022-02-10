###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
# Languages that are used in the project
enable_language(C)
###############################################################################
# Main project name
project(cred_storage)
###############################################################################
add_library(${PROJECT_NAME} EXCLUDE_FROM_ALL)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/cred_storage.c)
target_link_libraries(${PROJECT_NAME} PRIVATE fs)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
###############################################################################

# Generate test runner file.
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_runner.c
    COMMAND ruby ${CMAKE_SOURCE_DIR}/libs/thirdparty/Unity/auto/generate_test_runner.rb
    ${PROJECT_SOURCE_DIR}/test/cred_storage_test.c
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_runner.c
    DEPENDS ${PROJECT_SOURCE_DIR}/test/cred_storage_test.c
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/mocks)
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/mocks/Mockfs.c
    COMMAND ruby ${CMAKE_SOURCE_DIR}/libs/thirdparty/CMock/CMock/lib/cmock.rb
    ${PROJECT_SOURCE_DIR}/test/fs.h
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS ${PROJECT_SOURCE_DIR}/test/fs.h
)

add_executable(${PROJECT_NAME}_test)
target_sources(${PROJECT_NAME}_test PRIVATE
	${PROJECT_SOURCE_DIR}/test/cred_storage_test.c
	${PROJECT_BINARY_DIR}/mocks/Mockfs.c
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_runner.c
)
target_link_libraries(${PROJECT_NAME}_test PRIVATE unity cmock)
target_include_directories(${PROJECT_NAME}_test PRIVATE 
	${PROJECT_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/test
    ${PROJECT_BINARY_DIR}/mocks
)

add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)