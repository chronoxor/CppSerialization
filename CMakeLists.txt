cmake_minimum_required(VERSION 2.8)

# Global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Project name
project(cppserialization)

# Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN "doxygen")
  if(NOT TARGET ${DOXYGEN})
    add_custom_command(OUTPUT "Doxyfile" COMMAND ${DOXYGEN_EXECUTABLE} "Doxyfile" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/documents")
    add_custom_target(${DOXYGEN} DEPENDS "Doxyfile")
    set_target_properties(${DOXYGEN} PROPERTIES FOLDER doxygen)
  endif()
endif()

# CMake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler features
include(SetCompilerFeatures)
include(SetCompilerWarnings)
include(SetPlatformFeatures)

# Modules
add_subdirectory("modules")

# External packages
find_package(Threads REQUIRED)

# Link libraries
list(APPEND LINKLIBS Threads::Threads)
list(APPEND LINKLIBS cppcommon)

# Library
file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
add_library(cppserialization ${SOURCE_FILES})
target_include_directories(cppserialization PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/modules/flatbuffers/include" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/modules/rapidjson/include")
target_link_libraries(cppserialization ${LINKLIBS})
set_target_properties(cppserialization PROPERTIES FOLDER libraries)
list(APPEND INSTALL_TARGETS cppserialization)
list(APPEND LINKLIBS cppserialization)

# Additional module components: examples, performance benchmarks, tests, tools and install
if(NOT CPPSERIALIZATION_MODULE)

  # Domain models
  file(GLOB FLATBUFFER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/domain" "domain/*.fbs")
  foreach(FLATBUFFER_FILE ${FLATBUFFER_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1_generated.h" FLATBUFFER_HEADER ${FLATBUFFER_FILE})
    set(FLATBUFFER_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/domain")
    set(FLATBUFFER_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/domain/${FLATBUFFER_FILE}")
    add_custom_command(OUTPUT ${FLATBUFFER_HEADER} COMMAND $<TARGET_FILE:flatc> --cpp --scoped-enums -o ${FLATBUFFER_OUTPUT} ${FLATBUFFER_INPUT} DEPENDS flatc)
  endforeach()

  # Examples
  file(GLOB EXAMPLE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/examples" "examples/*.cpp")
  foreach(EXAMPLE_FILE ${EXAMPLE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" EXAMPLE_NAME ${EXAMPLE_FILE})
    set(EXAMPLE_TARGET "cppserialization-example-${EXAMPLE_NAME}")
    set_source_files_properties(examples/${EXAMPLE_FILE} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
    add_executable(${EXAMPLE_TARGET} examples/${EXAMPLE_FILE})
    target_link_libraries(${EXAMPLE_TARGET} ${LINKLIBS})
    set_target_properties(${EXAMPLE_TARGET} PROPERTIES FOLDER examples)
    list(APPEND INSTALL_TARGETS ${EXAMPLE_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${EXAMPLE_TARGET})
  endforeach()

  # Performance benchmarks
  file(GLOB BENCHMARK_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/performance" "performance/*.cpp")
  foreach(BENCHMARK_FILE ${BENCHMARK_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" BENCHMARK_NAME ${BENCHMARK_FILE})
    set(BENCHMARK_TARGET "cppserialization-performance-${BENCHMARK_NAME}")
    set_source_files_properties(performance/${BENCHMARK_FILE} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
    add_executable(${BENCHMARK_TARGET} performance/${BENCHMARK_FILE})
    target_link_libraries(${BENCHMARK_TARGET} ${LINKLIBS} cppbenchmark)
    set_target_properties(${BENCHMARK_TARGET} PROPERTIES FOLDER performance)
    list(APPEND INSTALL_TARGETS ${BENCHMARK_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${BENCHMARK_TARGET})
  endforeach()

  # Tests
  file(GLOB TESTS_SOURCE_FILES "tests/*.cpp")
  set_source_files_properties(${TESTS_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
  add_executable(cppserialization-tests ${CATCH} ${TESTS_SOURCE_FILES})
  target_include_directories(cppserialization-tests PRIVATE "modules/catch/single_include")
  target_link_libraries(cppserialization-tests ${LINKLIBS})
  set_target_properties(cppserialization-tests PROPERTIES FOLDER tests)
  list(APPEND INSTALL_TARGETS cppserialization-tests)
  list(APPEND INSTALL_TARGETS_PDB cppserialization-tests)

  # CTest
  enable_testing()
  add_test(cppserialization-tests cppserialization-tests)

  # Install
  install(TARGETS ${INSTALL_TARGETS}
    RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE DESTINATION "${PROJECT_SOURCE_DIR}/bin")

  # Install *.pdb files
  if(MSVC)
    foreach(INSTALL_TARGET_PDB ${INSTALL_TARGETS_PDB})
      install(FILES $<TARGET_PDB_FILE:${INSTALL_TARGET_PDB}> DESTINATION "${PROJECT_SOURCE_DIR}/bin")
    endforeach()
  endif()

endif()
