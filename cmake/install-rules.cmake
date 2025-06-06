if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/git2wrap-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package git2wrap)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT git2wrap_Development
)

install(
    TARGETS git2wrap_git2wrap
    EXPORT git2wrapTargets
    RUNTIME #
    COMPONENT git2wrap_Runtime
    LIBRARY #
    COMPONENT git2wrap_Runtime
    NAMELINK_COMPONENT git2wrap_Development
    ARCHIVE #
    COMPONENT git2wrap_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    git2wrap_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE git2wrap_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(git2wrap_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${git2wrap_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT git2wrap_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${git2wrap_INSTALL_CMAKEDIR}"
    COMPONENT git2wrap_Development
)

install(
    EXPORT git2wrapTargets
    NAMESPACE git2wrap::
    DESTINATION "${git2wrap_INSTALL_CMAKEDIR}"
    COMPONENT git2wrap_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
