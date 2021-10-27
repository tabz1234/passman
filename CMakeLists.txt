#basic configuration :
set (Label passman)
set (Standard 20)
set (Link_libs -lsqlite3 -llua)
#set (compiler gcc)

#cmake code :
cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)

project(${Label})

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD ${Standard})
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB CXX_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} 
	${CXX_SOURCES} 
	)

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES debug release)
elseif(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "Missing Build Type! Run cmake with:\n-DCMAKE_BUILD_TYPE=debug or release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "debug")
target_compile_options(${PROJECT_NAME} PUBLIC  -Wall -Weffc++ -pedantic
-Wextra 
-Wshadow 
-Wunreachable-code 
-Wunused
-Wunused-parameter)
else()
	target_compile_options(${PROJECT_NAME} PUBLIC  -s )
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${Link_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

