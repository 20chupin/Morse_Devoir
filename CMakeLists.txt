cmake_minimum_required(VERSION 3.0.0)
project(morse VERSION 0.1.0)

FILE(GLOB mainSources *.cpp)
FILE(GLOB srcSources src/*.cpp)

add_executable(morse  
${mainSources}
${srcSources}
)

target_link_libraries(morse ${CMAKE_SOURCE_DIR}/lib/libmorse_lib.a)

target_include_directories(morse PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
