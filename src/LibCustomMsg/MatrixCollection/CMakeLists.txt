# set target name
set(LIBRARY_TARGET_NAME MatrixCollection)

find_package(iDynTree REQUIRED)

set(${LIBRARY_TARGET_NAME}_HDR
  include/YarpMatLogger/MatrixCollection/Helper.h
  )

set(${LIBRARY_TARGET_NAME}_SRC
  src/Helper.cpp
  )

# add an executable to the project using the specified source files.
add_library(${LIBRARY_TARGET_NAME} SHARED ${${LIBRARY_TARGET_NAME}_HDR} ${${LIBRARY_TARGET_NAME}_SRC})

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES
  VERSION ${${PROJECT_NAME}_VERSION}
  PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")

add_library(${PROJECT_NAME}::${LIBRARY_TARGET_NAME} ALIAS ${LIBRARY_TARGET_NAME})

# add include directories to the build.
target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC
  "$<BUILD_INTERFACE:${include_dirs};${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC ${YARP_LIBRARIES} ${iDynTree_LIBRARIES} YarpMatLogger::MatrixCollectionMsg)

install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        COMPONENT ${LIBRARY_TARGET_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/YarpMatLogger/${LIBRARY_TARGET_NAME}" COMPONENT dev)

message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")
