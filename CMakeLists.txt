cmake_minimum_required(VERSION 3.10)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND AND NOT DISABLE_CCACHE)
  message("Using ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else()
  message("Not using ccache")
endif()

project(cppthings VERSION 0.0.1)
set(PROJECT_NAMESPACE CppThings)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_library(${PROJECT_NAME} INTERFACE)

# Begin requirements
# End requirements


target_link_libraries(${PROJECT_NAME}
PUBLIC # Libraries needed to use this library
PRIVATE # Libraries only needed to build this library
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} INTERFACE
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

option(CPPTHINGS_TEST "Enable testing of cppthings")

if (${CPPTHINGS_TEST})
  message("Tests enabled")
  enable_testing()
  find_package(GTest REQUIRED)
  include(GoogleTest)

  file(GLOB_RECURSE test_source test/*.cpp)
  add_executable(${PROJECT_NAME}-test ${test_source})
  target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME} GTest::GTest GTest::Main)
  gtest_discover_tests(${PROJECT_NAME}-test)
else()
  message("Tests disabled")
endif()
