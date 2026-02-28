cmake_minimum_required(VERSION 3.20)

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
    set_target_properties(${DOXYGEN} PROPERTIES FOLDER "doxygen")
  endif()
endif()

# CMake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler features
include(SetCompilerFeatures)
include(SetCompilerWarnings)
include(SetPlatformFeatures)
include(SystemInformation)

# External packages
if (NOT CYGWIN)
  find_package(Java REQUIRED)
endif()

# Modules
add_subdirectory("modules")

# Link libraries
list(APPEND LINKLIBS capnp)
list(APPEND LINKLIBS libprotobuf)
list(APPEND LINKLIBS cppcommon)

# System directories
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/modules")
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/modules/protobuf/third_party/abseil-cpp")

# Library
file(GLOB_RECURSE LIB_HEADER_FILES "include/*.h" "source/*.h")
file(GLOB_RECURSE LIB_INLINE_FILES "include/*.inl" "source/*.inl")
file(GLOB_RECURSE LIB_SOURCE_FILES "include/*.cpp" "source/*.cpp")
add_library(cppserialization ${LIB_HEADER_FILES} ${LIB_INLINE_FILES} ${LIB_SOURCE_FILES})
set_target_properties(cppserialization PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "libraries")
target_include_directories(cppserialization PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/proto" PUBLIC ${capnproto} PUBLIC ${flatbuf} PUBLIC ${protobuf} PUBLIC ${rapidjson} PUBLIC ${zpp_bits})
target_link_libraries(cppserialization ${LINKLIBS})
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
        COMMAND flatc --cpp --scoped-enums -o ${FLATBUFFERS_OUTPUT_DIR} ${FLATBUFFERS_INPUT_FILE} COMMENT "Generating ${FLATBUFFERS_OUTPUT_FILE}..." VERBATIM
    )
    add_custom_target(${FLATBUFFERS_TARGET} DEPENDS ${FLATBUFFERS_OUTPUT_FILE})
    set_target_properties(${FLATBUFFERS_TARGET} PROPERTIES FOLDER "proto")
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
        COMMAND protoc --proto_path=${PROTOBUF_INPUT_DIR} --cpp_out=${PROTOBUF_OUTPUT_DIR} ${PROTOBUF_INPUT_FILE} COMMENT "Generating ${PROTOBUF_OUTPUT_FILE}..." VERBATIM
    )
    add_custom_target(${PROTOBUF_TARGET} DEPENDS ${PROTOBUF_OUTPUT_FILE})
    set_target_properties(${PROTOBUF_TARGET} PROPERTIES FOLDER "proto")
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
    if(MSYS OR DEFINED ENV{MSYSTEM})
      set(CAPNP_SOURCES "${CAPNPC_OUTPUT_DIR}/${CAPNP_SOURCE}")
    else()
      capnp_generate_cpp(CAPNP_HEADERS CAPNP_SOURCES ${CAPNP_INPUT_FILE})
    endif()
    list(APPEND PROTO_FILES ${CAPNP_HEADERS} ${CAPNP_SOURCES})
  endforeach()

  # Proto SBE models
  file(GLOB SBE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/proto" "proto/*.sbe.xml")
  foreach(SBE_FILE ${SBE_FILES})
    string(REGEX REPLACE "(.*)\\.sbe.xml" "\\1.sbe.sbeir" SBE_HEADER ${SBE_FILE})
    set(SBE_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
    set(SBE_INPUT_FILE "${SBE_INPUT_DIR}/${SBE_FILE}")
    set(SBE_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
    set(SBE_OUTPUT_FILE "${SBE_OUTPUT_DIR}/${SBE_HEADER}")
    set(SBE_TARGET "${SBE_FILE}_TARGET")
    if (Java_FOUND)
      add_custom_command(
          OUTPUT ${SBE_OUTPUT_FILE} DEPENDS ${SBE_INPUT_FILE}
          COMMAND ${Java_JAVA_EXECUTABLE} -Dsbe.generate.ir=true -Dsbe.target.language=Cpp -Dsbe.target.namespace=sbe -Dsbe.output.dir=${SBE_OUTPUT_DIR} -Dsbe.errorLog=yes --add-opens java.base/jdk.internal.misc=ALL-UNNAMED -jar ${CMAKE_CURRENT_SOURCE_DIR}/modules/sbe/sbe-all-1.37.1.jar ${SBE_INPUT_FILE} COMMENT "Generating ${SBE_OUTPUT_FILE}..." VERBATIM
      )
    endif()
    add_custom_target(${SBE_TARGET} DEPENDS ${SBE_OUTPUT_FILE})
    set_target_properties(${SBE_TARGET} PROPERTIES FOLDER "proto")
    list(APPEND PROTO_DEPENDENCIES ${SBE_TARGET})
    list(APPEND PROTO_FILES ${SBE_OUTPUT_FILE})
  endforeach()

  # Proto FBE models
  file(GLOB FBE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/proto/fbe" "proto/fbe/*.cpp")
  foreach(FBE_FILE ${FBE_FILES})
    set(FBE_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto/fbe")
    set(FBE_SOURCE_FILE "${FBE_PROTO_DIR}/${FBE_FILE}")
    list(APPEND PROTO_FILES ${FBE_SOURCE_FILE})
  endforeach()

  # Proto library
  add_library(proto ${PROTO_FILES})
  add_dependencies(proto ${PROTO_DEPENDENCIES})
  if(MSVC)
    # C4125: decimal digit terminates octal escape sequence
    # C4127: conditional expression is constant
    # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
    # C4245: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
    # C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
    # C4251: 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
    # C5054: operator 'operator-name': deprecated between enumerations of different types
    set_target_properties(proto PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} /wd4125 /wd4127 /wd4244 /wd4245 /wd4251 /wd4267 /wd5054" FOLDER "proto")
  else()
    set_target_properties(proto PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS} -Wno-deprecated-declarations -Wno-pedantic -Wno-array-bounds -Wno-shadow" FOLDER "proto")
  endif()
  target_link_libraries(proto ${LINKLIBS})
  list(APPEND LINKLIBS proto)

  # Examples
  file(GLOB EXAMPLE_HEADER_FILES "examples/*.h")
  file(GLOB EXAMPLE_INLINE_FILES "examples/*.inl")
  file(GLOB EXAMPLE_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/examples" "examples/*.cpp")
  foreach(EXAMPLE_SOURCE_FILE ${EXAMPLE_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" EXAMPLE_NAME ${EXAMPLE_SOURCE_FILE})
    set(EXAMPLE_TARGET "cppserialization-example-${EXAMPLE_NAME}")
    add_executable(${EXAMPLE_TARGET} ${EXAMPLE_HEADER_FILES} ${EXAMPLE_INLINE_FILES} "examples/${EXAMPLE_SOURCE_FILE}")
    set_target_properties(${EXAMPLE_TARGET} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "examples")
    target_link_libraries(${EXAMPLE_TARGET} ${LINKLIBS})
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
    add_executable(${BENCHMARK_TARGET} ${BENCHMARK_HEADER_FILES} ${BENCHMARK_INLINE_FILES} "performance/${BENCHMARK_SOURCE_FILE}")
    set_target_properties(${BENCHMARK_TARGET} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "performance")
    target_link_libraries(${BENCHMARK_TARGET} ${LINKLIBS} cppbenchmark)
    list(APPEND INSTALL_TARGETS ${BENCHMARK_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${BENCHMARK_TARGET})
  endforeach()

  # Tests
  file(GLOB TESTS_HEADER_FILES "tests/*.h")
  file(GLOB TESTS_INLINE_FILES "tests/*.inl")
  file(GLOB TESTS_SOURCE_FILES "tests/*.cpp")
  add_executable(cppserialization-tests ${TESTS_HEADER_FILES} ${TESTS_INLINE_FILES} ${TESTS_SOURCE_FILES})
  set_target_properties(cppserialization-tests PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "tests")
  target_include_directories(cppserialization-tests PRIVATE Catch2)
  target_link_libraries(cppserialization-tests ${LINKLIBS} Catch2)
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
