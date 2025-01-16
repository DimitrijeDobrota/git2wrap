cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    git2wrap
    VERSION 0.1.18
    DESCRIPTION "C++ 20 wrapper for libgit2"
    HOMEPAGE_URL "https://git.dimitrijedobrota.com/git2wrap.git"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    git2wrap_git2wrap
    source/blob.cpp
    source/branch.cpp
    source/buf.cpp
    source/commit.cpp
    source/diff.cpp
    source/libgit2.cpp
    source/object.cpp
    source/oid.cpp
    source/reference.cpp
    source/repository.cpp
    source/revwalk.cpp
    source/signature.cpp
    source/tag.cpp
    source/tree.cpp
)
add_library(git2wrap::git2wrap ALIAS git2wrap_git2wrap)

target_link_libraries(git2wrap_git2wrap PRIVATE git2)

include(GenerateExportHeader)
generate_export_header(
    git2wrap_git2wrap
    BASE_NAME git2wrap
    EXPORT_FILE_NAME export/git2wrap/git2wrap_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(git2wrap_git2wrap PUBLIC GIT2WRAP_STATIC_DEFINE)
endif()

set_target_properties(
    git2wrap_git2wrap PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME git2wrap
    OUTPUT_NAME git2wrap
)

target_include_directories(
    git2wrap_git2wrap ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    git2wrap_git2wrap SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(git2wrap_git2wrap PUBLIC cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${git2wrap_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT git2wrap_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of git2wrap"
  )
endif()

include(cmake/dev-mode.cmake)
