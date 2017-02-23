if(NOT TARGET flatbuffers)

  # Set options
  SET(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "Enable the build of tests and samples." FORCE)
  SET(FLATBUFFERS_INSTALL OFF CACHE BOOL "Enable the installation of targets." FORCE)

  # Module subdirectory
  add_subdirectory("flatbuffers")

  # Module folder
  set_target_properties(flatbuffers PROPERTIES FOLDER modules/flatbuffers/flatbuffers)
  set_target_properties(flatc PROPERTIES FOLDER modules/flatbuffers/flatc)
  set_target_properties(flathash PROPERTIES FOLDER modules/flatbuffers/flathash)

endif()
