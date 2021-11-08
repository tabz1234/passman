# basic configuration :
set(Label passman)
set(Standard 20)
set(Link_libs -lpthread -lsqlite3 -llua)

set(DEFAULT_ADDITIONAL_DEBUG_OPTIONS -O0 -Wall -Wextra -Weffc++ -pedantic )

set(DEFAULT_ADDITIONAL_RELEASE_OPTIONS )

# cmake code :
cmake_minimum_required(VERSION 3.21)

project(${Label})

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD ${Standard})
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB C_OR_CPP_SOURCES "src/*.c*")

add_executable(${PROJECT_NAME} ${C_OR_CPP_SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "debug")
enable_testing()
  target_compile_options(${PROJECT_NAME}
                         PUBLIC ${DEFAULT_ADDITIONAL_DEBUG_OPTIONS})
else()
  target_compile_options(${PROJECT_NAME}
                         PUBLIC ${DEFAULT_ADDITIONAL_RELEASE_OPTIONS})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${Link_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src /usr/include)
