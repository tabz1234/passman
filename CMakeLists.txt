cmake_minimum_required(VERSION 3.20)


set(ProjectName test)

project(${ProjectName} CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

add_library(project_warnings INTERFACE)

include(cmake/Cache.cmake)

include(cmake/Linker.cmake)
configure_linker(project_options)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/StaticAnalyzers.cmake)

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
  target_precompile_headers(
    project_options
    INTERFACE
    <vector>
    <string>
    <iostream>
    <type_traits>
    <map>
    <list>
    <forward_list>
    <optional>
    <stdexcept>
    <memory>
    <utility>)
endif()

add_executable(${ProjectName}
	./src/main.cpp
	./src/sqlite/DataBase.cpp
	./src/sqlite/DataBaseContext.cpp
	./src/sqlite/Data.cpp
	)

add_subdirectory(./lib/sqlite)

target_link_libraries(${ProjectName} project_options project_warnings)
target_link_libraries(${ProjectName} sqlite)
