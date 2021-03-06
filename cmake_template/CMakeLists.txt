cmake_minimum_required(VERSION 3.10)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND AND NOT DISABLE_CCACHE)
  message("Using ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else()
  message("Not using ccache")
endif()

project(@@ VERSION @@)
set(PROJECT_NAMESPACE @@)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

# Begin requirements
# @@
# End requirements


target_link_libraries(${PROJECT_NAME}
PUBLIC # Libraries needed to use this library
# @@
PRIVATE # Libraries only needed to build this library
# @@
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(EXPORT ${PROJECT_NAME}_targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAMESPACE}/cmake)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}_targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAMESPACE}/cmake"
)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAMESOACE}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION include)

add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
