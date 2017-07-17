cmake_minimum_required(VERSION 3.4)
project (MAPT-Framework-EventDisplay CXX)


option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" OFF)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

add_definitions("-std=c++11")

include(${Geant4_USE_FILE})

# CADMesh
find_package(cadmesh)
include_directories(${CADMESH_INCLUDE_DIRS})

# declaring files in your project
set (SOURCES
    C_data.cpp
    C_mainwindow.cpp
    C_quader.cpp
    C_view_3D.cpp
    C_view_2D.cpp
    C_view_coordinatesystem.cpp
    C_window_3D.cpp
    C_window_2D.cpp
    main.cpp
)

set (MOC_HEADERS
    C_mainwindow.h
    C_quader.h
    C_view_3D.h
    C_view_2D.h
    C_view_coordinatesystem.h
    C_window_3D.h
    C_window_2D.h
)

set (UIS
)

set (RESOURCES
    resources.qrc
)

# Next lines needed for building all Qt projects
find_package(Qt4 REQUIRED COMPONENTS QTCORE QTGUI QTOPENGL)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_BINARY_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../lib)
include_directories(${PROJECT_SOURCE_DIR}/../lib/base)
include_directories(${PROJECT_SOURCE_DIR}/../lib/geant)

# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
QT4_ADD_RESOURCES(RES_SOURCES ${RESOURCES})
QT4_WRAP_UI(UI_HEADERS ${UIS})
QT4_WRAP_CPP(MOC_SRCS ${MOC_HEADERS})

# compile
add_executable(EventDisplay ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS})
# or use line below instead, if you using Windows ™ Operating System.
#add_executable( PROJECT_NAME WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

# build it (link libraries)
target_link_libraries(EventDisplay ${QT_LIBRARIES} Event MAPT GeantSim Geometry)

install(TARGETS EventDisplay DESTINATION bin)
