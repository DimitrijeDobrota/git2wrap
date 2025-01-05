cmake_minimum_required(VERSION 3.14)

project(git2wrapTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(git2wrap REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(git2wrap_test source/git2wrap_test.cpp)
target_link_libraries(git2wrap_test PRIVATE git2wrap::git2wrap)
target_compile_features(git2wrap_test PRIVATE cxx_std_20)

add_test(NAME git2wrap_test COMMAND git2wrap_test)

# ---- End-of-file commands ----

add_folders(Test)
