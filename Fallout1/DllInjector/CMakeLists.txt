cmake_minimum_required(VERSION 3.5)

project(LibraryToInject VERSION 0.0.1 LANGUAGES CXX)

add_library(LibraryToInject SHARED LibraryToInject.cpp)
