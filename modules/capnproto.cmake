if(NOT capnproto)

  # Restore origin compile flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_ORIGIN}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_ORIGIN}")

  # Set options
  SET(WITH_FIBERS OFF CACHE STRING "Whether or not to build libkj-async with fibers." FORCE)
  SET(WITH_OPENSSL OFF CACHE STRING "Whether or not to build libkj-tls by linking against openssl." FORCE)
  SET(BUILD_TESTING OFF CACHE BOOL "Build unit tests and enable CTest 'check' target." FORCE)

  # Module subdirectory
  add_subdirectory("capnproto")

  # Module folder
  set_target_properties(capnp PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnp-json PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnp-rpc PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnp-websocket PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnp_tool PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnpc PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnpc_capnp PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(capnpc_cpp PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(kj PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(kj-async PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(kj-http PROPERTIES FOLDER "modules/capnproto")
  set_target_properties(kj-test PROPERTIES FOLDER "modules/capnproto")

  # Module definition
  set(capnproto "${CMAKE_CURRENT_SOURCE_DIR}/capnproto/c++/src" PARENT_SCOPE)

  # Restore custom compile flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_CUSTOM}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_CUSTOM}")

endif()
