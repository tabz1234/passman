cmake_minimum_required(VERSION 3.18)


set(ProjectName passman)

project(${ProjectName} LANGUAGES CXX)
include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
set(CMAKE_CXX_EXTENSIONS OFF)

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

option(ENABLE_PCH "Enable Precompiled Headers" ON)
if(ENABLE_PCH)
  target_precompile_headers(
    project_options
    INTERFACE
    <vector>
    <string>
    <chrono>
    <queue>
    <iostream>
    <cstdlib>
    <thread>
    <type_traits>
    <unordered_map>
    <optional>
    <memory>
    <utility>)
endif()

add_executable(${ProjectName}
	./src/passman/main.cpp
	./src/passman/CredentialsSource.cpp
	./src/passman/println.cpp
	./src/passman/cmdline/parse_arguments.cpp
	./src/passman/fs/touch_appdata_dir.cpp
	./src/passman/fs/get_home_path.cpp
	./src/passman/fs/cd_to_appdata_dir.cpp
	./src/passman/fs/is_empty.cpp

	./src/sqlite/DataBase.cpp
	./src/sqlite/impl/DataBaseContext.cpp
	./src/sqlite/error/to_str.cpp

	./src/util/TerminalPrinter.cpp

	)

add_subdirectory(./lib/sqlite)

target_link_libraries(${ProjectName} -lpthread)
target_link_libraries(${ProjectName} project_options project_warnings)
target_link_libraries(${ProjectName} sqlite)
