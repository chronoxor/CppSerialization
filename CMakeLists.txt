cmake_minimum_required(VERSION 3.6)

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
include(SystemInformation)

# Modules
add_subdirectory("modules")

# Link libraries
list(APPEND LINKLIBS capnp)
list(APPEND LINKLIBS libprotobuf)
list(APPEND LINKLIBS cppcommon)

# System directories
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Library
file(GLOB_RECURSE LIB_HEADER_FILES "include/*.h")
file(GLOB_RECURSE LIB_INLINE_FILES "include/*.inl")
file(GLOB_RECURSE LIB_SOURCE_FILES "source/*.cpp")
set_source_files_properties(${LIB_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
add_library(cppserialization ${LIB_HEADER_FILES} ${LIB_INLINE_FILES} ${LIB_SOURCE_FILES})
target_include_directories(cppserialization PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/proto" PUBLIC ${capnproto} PUBLIC ${flatbuf} PUBLIC ${protobuf} PUBLIC ${rapidjson})
target_link_libraries(cppserialization ${LINKLIBS})
set_target_properties(cppserialization PROPERTIES FOLDER libraries)
list(APPEND INSTALL_TARGETS cppserialization)
list(APPEND LINKLIBS cppserialization)

# Additional module components: benchmarks, examples, plugins, tests, tools and install
if(NOT CPPSERIALIZATION_MODULE)

  # Proto Flatbuffers models
  file(GLOB FLATBUFFERS_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/proto" "proto/*.fbs")
  foreach(FLATBUFFERS_FILE ${FLATBUFFERS_FILES})
    string(REGEX REPLACE "(.*)\\.fbs" "\\1_generated.h" FLATBUFFERS_HEADER ${FLATBUFFERS_FILE})
    set(FLATBUFFERS_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
    set(FLATBUFFERS_INPUT_FILE "${FLATBUFFERS_INPUT_DIR}/${FLATBUFFERS_FILE}")
    set(FLATBUFFERS_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto/flatbuffers")
    set(FLATBUFFERS_OUTPUT_FILE "${FLATBUFFERS_OUTPUT_DIR}/${FLATBUFFERS_HEADER}")
    set(FLATBUFFERS_TARGET "${FLATBUFFERS_FILE}_TARGET")
    add_custom_command(
        OUTPUT ${FLATBUFFERS_OUTPUT_FILE} DEPENDS ${FLATBUFFERS_INPUT_FILE}
        COMMAND $<TARGET_FILE:flatc> --cpp --scoped-enums -o ${FLATBUFFERS_OUTPUT_DIR} ${FLATBUFFERS_INPUT_FILE} COMMENT "Generating ${FLATBUFFERS_OUTPUT_FILE}..." VERBATIM
    )
    add_custom_target(${FLATBUFFERS_TARGET} DEPENDS ${FLATBUFFERS_OUTPUT_FILE})
    set_target_properties(${FLATBUFFERS_TARGET} PROPERTIES FOLDER proto)
    list(APPEND PROTO_DEPENDENCIES ${FLATBUFFERS_TARGET})
    list(APPEND PROTO_FILES ${FLATBUFFERS_OUTPUT_FILE})
  endforeach()

  # Proto Protobuf models
  file(GLOB PROTOBUF_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/proto" "proto/*.proto")
  foreach(PROTOBUF_FILE ${PROTOBUF_FILES})
    string(REGEX REPLACE "(.*)\\.proto" "\\1.pb.cc" PROTOBUF_SOURCE ${PROTOBUF_FILE})
    set(PROTOBUF_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
    set(PROTOBUF_INPUT_FILE "${PROTOBUF_INPUT_DIR}/${PROTOBUF_FILE}")
    set(PROTOBUF_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto/protobuf")
    set(PROTOBUF_OUTPUT_FILE "${PROTOBUF_OUTPUT_DIR}/${PROTOBUF_SOURCE}")
    set(PROTOBUF_TARGET "${PROTOBUF_FILE}_TARGET")
    add_custom_command(
        OUTPUT ${PROTOBUF_OUTPUT_FILE} DEPENDS ${PROTOBUF_INPUT_FILE}
        COMMAND $<TARGET_FILE:protoc> --proto_path=${PROTOBUF_INPUT_DIR} --cpp_out=${PROTOBUF_OUTPUT_DIR} ${PROTOBUF_INPUT_FILE} COMMENT "Generating ${PROTOBUF_OUTPUT_FILE}..." VERBATIM
    )
    add_custom_target(${PROTOBUF_TARGET} DEPENDS ${PROTOBUF_OUTPUT_FILE})
    set_target_properties(${PROTOBUF_TARGET} PROPERTIES FOLDER proto)
    list(APPEND PROTO_DEPENDENCIES ${PROTOBUF_TARGET})
    list(APPEND PROTO_FILES ${PROTOBUF_OUTPUT_FILE})
  endforeach()

  # Proto Cap'n'Proto models
  file(GLOB CAPNP_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/proto" "proto/*.capnp")
  foreach(CAPNP_FILE ${CAPNP_FILES})
    string(REGEX REPLACE "(.*)\\.capnp" "\\1.capnp.c++" CAPNP_SOURCE ${CAPNP_FILE})
    set(CAPNP_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
    set(CAPNP_INPUT_FILE "${CAPNP_INPUT_DIR}/${CAPNP_FILE}")
    set(CAPNPC_SRC_PREFIX "${CAPNP_INPUT_DIR}")
    set(CAPNPC_OUTPUT_DIR "${CAPNP_INPUT_DIR}/capnproto")
    if(MSYS)
      set(CAPNP_SOURCES "${CAPNPC_OUTPUT_DIR}/${CAPNP_SOURCE}")
      message("MSYS!")
    else()
      capnp_generate_cpp(CAPNP_HEADERS CAPNP_SOURCES ${CAPNP_INPUT_FILE})
      message("VS!")
    endif()
    list(APPEND PROTO_FILES ${CAPNP_HEADERS} ${CAPNP_SOURCES})
  endforeach()

  # Proto FBE models
  file(GLOB FBE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/proto/fbe" "proto/fbe/*.cpp")
  foreach(FBE_FILE ${FBE_FILES})
    set(FBE_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto/fbe")
    set(FBE_SOURCE_FILE "${FBE_PROTO_DIR}/${FBE_FILE}")
    list(APPEND PROTO_FILES ${FBE_SOURCE_FILE})
  endforeach()

  # Proto library
  if(MSVC)
    # C4125: decimal digit terminates octal escape sequence
    # C4127: conditional expression is constant
    # C4244: conversion' conversion from 'type1' to 'type2', possible loss of data
    # C4245: conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
    # C4267: var' : conversion from 'size_t' to 'type', possible loss of data
    set_source_files_properties(${PROTO_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4125 /wd4127 /wd4244 /wd4245 /wd4267")
  else()
    set_source_files_properties(${PROTO_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} -Wno-pedantic -Wno-array-bounds")
  endif()
  add_library(proto ${PROTO_FILES})
  target_link_libraries(proto ${LINKLIBS})
  add_dependencies(proto ${PROTO_DEPENDENCIES})
  set_target_properties(proto PROPERTIES FOLDER proto)
  list(APPEND LINKLIBS proto)

  # Examples
  file(GLOB EXAMPLE_HEADER_FILES "examples/*.h")
  file(GLOB EXAMPLE_INLINE_FILES "examples/*.inl")
  file(GLOB EXAMPLE_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/examples" "examples/*.cpp")
  foreach(EXAMPLE_SOURCE_FILE ${EXAMPLE_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" EXAMPLE_NAME ${EXAMPLE_SOURCE_FILE})
    set(EXAMPLE_TARGET "cppserialization-example-${EXAMPLE_NAME}")
    set_source_files_properties(examples/${EXAMPLE_SOURCE_FILE} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
    add_executable(${EXAMPLE_TARGET} ${EXAMPLE_HEADER_FILES} ${EXAMPLE_INLINE_FILES} examples/${EXAMPLE_SOURCE_FILE})
    target_link_libraries(${EXAMPLE_TARGET} ${LINKLIBS})
    set_target_properties(${EXAMPLE_TARGET} PROPERTIES FOLDER examples)
    list(APPEND INSTALL_TARGETS ${EXAMPLE_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${EXAMPLE_TARGET})
  endforeach()

  # Benchmarks
  file(GLOB BENCHMARK_HEADER_FILES "performance/*.h")
  file(GLOB BENCHMARK_INLINE_FILES "performance/*.inl")
  file(GLOB BENCHMARK_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/performance" "performance/*.cpp")
  foreach(BENCHMARK_SOURCE_FILE ${BENCHMARK_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" BENCHMARK_NAME ${BENCHMARK_SOURCE_FILE})
    set(BENCHMARK_TARGET "cppserialization-performance-${BENCHMARK_NAME}")
    set_source_files_properties(performance/${BENCHMARK_SOURCE_FILE} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
    add_executable(${BENCHMARK_TARGET} ${BENCHMARK_HEADER_FILES} ${BENCHMARK_INLINE_FILES} performance/${BENCHMARK_SOURCE_FILE})
    target_link_libraries(${BENCHMARK_TARGET} ${LINKLIBS} cppbenchmark)
    set_target_properties(${BENCHMARK_TARGET} PROPERTIES FOLDER performance)
    list(APPEND INSTALL_TARGETS ${BENCHMARK_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${BENCHMARK_TARGET})
  endforeach()

  # Tests
  file(GLOB TESTS_HEADER_FILES "tests/*.h")
  file(GLOB TESTS_INLINE_FILES "tests/*.inl")
  file(GLOB TESTS_SOURCE_FILES "tests/*.cpp")
  set_source_files_properties(${TESTS_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
  add_executable(cppserialization-tests ${TESTS_HEADER_FILES} ${TESTS_INLINE_FILES} ${TESTS_SOURCE_FILES} ${Catch2})
  target_include_directories(cppserialization-tests PRIVATE ${Catch2})
  target_link_libraries(cppserialization-tests ${LINKLIBS})
  set_target_properties(cppserialization-tests PROPERTIES FOLDER tests)
  list(APPEND INSTALL_TARGETS cppserialization-tests)
  list(APPEND INSTALL_TARGETS_PDB cppserialization-tests)

  # CTest
  enable_testing()
  add_test(cppserialization-tests cppserialization-tests --durations yes --order lex)

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
