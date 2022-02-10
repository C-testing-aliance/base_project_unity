# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
# Languages that are used in the project
enable_language(C)
###############################################################################
# Main project name
project(cmock)
###############################################################################
add_library(${PROJECT_NAME} STATIC EXCLUDE_FROM_ALL)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/CMock/src/cmock.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/CMock/src)
target_link_libraries(${PROJECT_NAME} PRIVATE unity)
###############################################################################