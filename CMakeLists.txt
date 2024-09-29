cmake_minimum_required(VERSION 3.18)

add_library(TableWeaver STATIC)
add_library(TableWeaver::TableWeaver ALIAS TableWeaver)

target_include_directories(TableWeaver PUBLIC src)
target_sources(TableWeaver PRIVATE src/TableWeaver.c)
