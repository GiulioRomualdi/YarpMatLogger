# set target name
set(LIBRARY_TARGET_NAME MessageHandler)

# matlogger2 is required
find_package(matlogger2 REQUIRED)

set(${LIBRARY_TARGET_NAME}_HDR
  include/YarpMatLogger/MessageHandler/MessageHandler.h
  include/YarpMatLogger/MessageHandler/VectorHandler.h
  include/YarpMatLogger/MessageHandler/TimeHandler.h
  include/YarpMatLogger/MessageHandler/MatrixCollectionHandler.h
  )

set(${LIBRARY_TARGET_NAME}_SRC
  src/VectorHandler.cpp
  src/MatrixCollectionHandler.cpp
  src/TimeHandler.cpp
  )


# add an executable to the project using the specified source files.
add_library(${LIBRARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION}
  PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")

add_library(${PROJECT_NAME}::${LIBRARY_TARGET_NAME} ALIAS ${LIBRARY_TARGET_NAME})

# add include directories to the build.
target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(${LIBRARY_TARGET_NAME} ${YARP_LIBRARIES}
   matlogger2::matlogger2
   YarpMatLogger::MatrixCollection)

install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        COMPONENT ${LIBRARY_TARGET_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/YarpMatLogger/${LIBRARY_TARGET_NAME}" COMPONENT dev)

message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")
