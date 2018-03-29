if(NOT TARGET flatbuffers)

  # Restore origin compile flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_ORIGIN}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_ORIGIN}")

  # Set options
  SET(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "Enable the build of tests and samples." FORCE)
  SET(FLATBUFFERS_INSTALL OFF CACHE BOOL "Enable the installation of targets." FORCE)

  # Module subdirectory
  add_subdirectory("flatbuffers")

  # Module folder
  set_target_properties(flatbuffers PROPERTIES FOLDER modules/flatbuffers/flatbuffers)
  set_target_properties(flatc PROPERTIES FOLDER modules/flatbuffers/flatc)
  set_target_properties(flathash PROPERTIES FOLDER modules/flatbuffers/flathash)

  # Restore custom compile flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_CUSTOM}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_CUSTOM}")

endif()
