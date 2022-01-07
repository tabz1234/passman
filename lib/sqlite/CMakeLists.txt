cmake_minimum_required(VERSION 3.21)
project(sqlite)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE REQUIRED IMPORTED_TARGET sqlite3)

add_library(sqlite INTERFACE IMPORTED GLOBAL)

target_link_libraries(sqlite INTERFACE
	PkgConfig::SQLITE
)
