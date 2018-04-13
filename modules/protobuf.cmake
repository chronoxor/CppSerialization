if(NOT TARGET protobuf)

  # Restore origin compile flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_ORIGIN}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_ORIGIN}")

  # Set options
  SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
  SET(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
  SET(protobuf_BUILD_PROTOC_BINARIES ON CACHE BOOL "Build libprotoc and protoc compiler" FORCE)
  SET(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "Build Shared Libraries" FORCE)
  SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries" FORCE)
  SET(protobuf_WITH_ZLIB OFF CACHE BOOL "Build with zlib support" FORCE)  

  # Module subdirectory
  add_subdirectory("protobuf/cmake")

  # Module folder
  set_target_properties(libprotobuf PROPERTIES FOLDER modules/protobuf)
  set_target_properties(libprotobuf-lite PROPERTIES FOLDER modules/protobuf)
  set_target_properties(libprotoc PROPERTIES FOLDER modules/protobuf)
  set_target_properties(protoc PROPERTIES FOLDER modules/protobuf)
  set_target_properties(js_embed PROPERTIES FOLDER modules/protobuf)

  # Module definition
  set(protobuf "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/src" PARENT_SCOPE)

  # Restore custom compile flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_CUSTOM}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_CUSTOM}")

endif()
