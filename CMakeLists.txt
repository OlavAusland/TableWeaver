cmake_minimum_required(VERSION 3.18)

add_library(TableWeaver SHARED)
add_library(TableWeaver::TableWeaver ALIAS TableWeaver)

target_sources(TableWeaver PRIVATE TableWeaver.c)
