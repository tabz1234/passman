#basic configuration :
set (Label exec)
set (Standard 20)
set (Link_libs -lsqlite3 -llua)
set (compiler gcc)#clang have linkage hell

#cmake code :
cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)

if(${compiler} MATCHES  clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)
elseif(${compiler} MATCHES gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_C_COMPILER /usr/bin/gcc)
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

project(${Label} LANGUAGES CXX )

set(CMAKE_CXX_STANDARD ${Standard})
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)




file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} 
	${SOURCES}
	)

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
elseif(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "Missing Build Type! Run cmake with:\n-DCMAKE_BUILD_TYPE=Debug or Release")
endif()




if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	if(${compiler} MATCHES gcc)
target_compile_options(${PROJECT_NAME} PUBLIC  -fPIC -ansi -Wall -Weffc++ -pedantic
-Wextra -Wcast-align
-Wcast-qual -Wconversion
-Wdisabled-optimization
-Wfloat-equal -Wformat=2
-Wformat-nonliteral -Wformat-security
-Wformat-y2k
-Wimport  -Winit-self  -Winline
-Winvalid-pch 
-Wlong-long
-Wmissing-field-initializers -Wmissing-format-attribute
-Wmissing-include-dirs -Wmissing-noreturn 
-Wpacked   -Wpointer-arith 
-Wredundant-decls 
-Wshadow -Wstack-protector 
-Wstrict-aliasing=2 -Wswitch-default
-Wswitch-enum
-Wunreachable-code -Wunused
-Wunused-parameter
-Wvariadic-macros
-Wwrite-strings)
elseif(${compiler} MATCHES clang)
	target_compile_options(${PROJECT_NAME} PUBLIC -Weverything -stdlib=libc++ -fPIC )
endif()

else()
if(${compiler} MATCHES gcc)
	target_compile_options(${PROJECT_NAME} PUBLIC  -fPIC  -s )
elseif(${compiler} MATCHES clang)
	target_compile_options(${PROJECT_NAME} PUBLIC -stdlib=libc++ -fPIC  )
endif()

endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${Link_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)


ADD_CUSTOM_TARGET(run
	COMMAND make -j2 && ./${PROJECT_NAME} && echo "\n"
)

#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#add_custom_command(TARGET ${PROJECT_NAME}
#        POST_BUILD
#	COMMAND cp ${CMAKE_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_SOURCE_DIR})
#endif()



