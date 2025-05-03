include(CMakeFindDependencyMacro)
find_dependency(libgit2)

if(libgit2_FOUND)
  include("${CMAKE_CURRENT_LIST_DIR}/git2wrapTargets.cmake")
endif()
