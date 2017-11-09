#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(MAPT-Framework-Library CXX)

SET (LIBRARY_NAME Fibers)

SET (LIBRARY_HDRS
    MFibersDetector.h
    MFibersGeomPar.h
    MFibersUnpacker.h
    MFibersRaw.h
    MFibersCalibrator.h
    MFibersCalibratorPar.h
    MFibersCal.h
    MFibersDigitizer.h
    MFibersDigitizerPar.h
    MFibersCalSim.h
)

SET(LIBRARY_SRCS
    MFibersDetector.cc
    MFibersGeomPar.cc
    MFibersUnpacker.cc
    MFibersRaw.cc
    MFibersCalibrator.cc
    MFibersCalibratorPar.cc
    MFibersCal.cc
    MFibersDigitizer.cc
    MFibersDigitizerPar.cc
    MFibersCalSim.cc
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR})

ROOT_GENERATE_DICTIONARY(G__${LIBRARY_NAME}
    ${LIBRARY_HDRS}
    LINKDEF Linkdef.h
)

# ROOT_GENERATE_ROOTMAP(${LIBRARY_NAME} LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/Linkdef.h)

add_library(${LIBRARY_NAME} SHARED
    ${LIBRARY_SRCS}
    G__${LIBRARY_NAME}.cxx
)

target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

install(TARGETS ${LIBRARY_NAME} DESTINATION lib)
install(FILES ${LIBRARY_HDRS} DESTINATION include)

# Install the export set for use with the install-tree
install(TARGETS Fibers
	EXPORT ${CMAKE_PROJECT_NAME}Targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	COMPONENT shlib COMPONENT dev)
