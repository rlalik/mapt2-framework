#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_NAME FibersStack)

SET (LIBRARY_HDRS
    MFibersStackDetector.h
    MFibersStackGeomPar.h
    MFibersStackUnpacker.h
    MFibersStackRaw.h
    MFibersStackCalibrator.h
    MFibersStackCalibratorPar.h
    MFibersStackCal.h
    MFibersStackDigitizer.h
    MFibersStackDigitizerPar.h
    MFibersStackCalSim.h
)

SET(LIBRARY_SRCS
    MFibersStackDetector.cc
    MFibersStackGeomPar.cc
    MFibersStackUnpacker.cc
    MFibersStackRaw.cc
    MFibersStackCalibrator.cc
    MFibersStackCalibratorPar.cc
    MFibersStackCal.cc
    MFibersStackDigitizer.cc
    MFibersStackDigitizerPar.cc
    MFibersStackCalSim.cc
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR})

ROOT_GENERATE_DICTIONARY(G__${LIBRARY_NAME}_cc
    ${LIBRARY_HDRS}
    LINKDEF Linkdef.h
)

# ROOT_GENERATE_ROOTMAP(${LIBRARY_NAME} LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/Linkdef.h)

add_library(${LIBRARY_NAME} SHARED
    ${LIBRARY_SRCS}
    G__${LIBRARY_NAME}_cc
)

target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES} MAPT)

install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${LIBRARY_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the export set for use with the install-tree
install(TARGETS ${LIBRRAY_NAME}
	EXPORT ${CMAKE_PROJECT_NAME}Targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	COMPONENT shlib COMPONENT dev)
