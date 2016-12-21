cmake_minimum_required(VERSION 3.0)

set(CMAKE_OSX_SYSROOT "")

set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tool_root /home/hitmoon/arm-linux-androideabi-4.8)
set(CMAKE_SYSROOT ${tool_root}/sysroot)

set(CMAKE_C_COMPILER ${tool_root}/bin/arm-linux-androideabi-clang)
set(CMAKE_CXX_COMPILER ${tool_root}/bin/arm-linux-androideabi-clang++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


project(radioadapter)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCE_FILES main.c adapter.h adapter.c)
add_library(radioadapter SHARED ${SOURCE_FILES})


target_link_libraries(radioadapter "${PROJECT_SOURCE_DIR}/libs/liblog.so" "${PROJECT_SOURCE_DIR}/libs/libril.so")

set_target_properties(radioadapter PROPERTIES OUTPUT_NAME "wrapper_ril")

SET_TARGET_PROPERTIES(radioadapter PROPERTIES #表示生成的执行文件所在路径
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out")

SET_TARGET_PROPERTIES(radioadapter PROPERTIES #表示生成的执行文件所在路径
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out")

