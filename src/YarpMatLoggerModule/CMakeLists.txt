# set target name
set(EXE_TARGET_NAME ${PROJECT_NAME})

# set cpp files
set(${EXE_TARGET_NAME}_SRC
  src/main.cpp
  src/YarpMatLoggerModule.cpp
  )

# set h files
set(${EXE_TARGET_NAME}_HDR
  include/YarpMatLoggerModule.h
  )

set(${EXE_TARGET_NAME}_THRIFT_HDR
  thrifts/YarpMatLoggerCommands.thrift
  )

# add include directories to the build.
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

# Application target calls
yarp_add_idl(${EXE_TARGET_NAME}_THRIFT_GEN_FILES ${${EXE_TARGET_NAME}_THRIFT_HDR})

# add an executable to the project using the specified source files.
add_executable(${EXE_TARGET_NAME} ${${EXE_TARGET_NAME}_SRC} ${${EXE_TARGET_NAME}_HDR} ${${EXE_TARGET_NAME}_THRIFT_GEN_FILES})

target_link_libraries(${EXE_TARGET_NAME}
  ${YARP_LIBRARIES}
  YarpMatLogger::MessageHandler
  UtilityLibrary)

install(TARGETS ${EXE_TARGET_NAME} DESTINATION bin)

add_subdirectory(app)
