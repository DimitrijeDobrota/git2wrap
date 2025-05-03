cmake_minimum_required(VERSION 3.14)

project(git2wrapTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

function(add_test NAME)
  add_executable("${NAME}" "source/${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE based::based)
  target_link_libraries("${NAME}" PRIVATE Catch2::Catch2WithMain)
  target_compile_features("${NAME}" PRIVATE cxx_std_20)
  catch_discover_tests("${NAME}")
endfunction()

add_test(git2wrap_test)

# ---- End-of-file commands ----

add_folders(Test)
