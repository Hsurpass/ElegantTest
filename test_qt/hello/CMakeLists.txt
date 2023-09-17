# cmake -G "Visual Studio 12 2013"  -D ALL_BUILD=OFF -D ZERO_CHECK=OFF -B build
#  cmake --build .\build\ --config Release
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(hello)

set(QTVERSION ${V})
if(NOT DEFINED QTVERSION)
    MESSAGE("VERSION is empty: " ${QTVERSION})
    set(QTVERSION "QT6")
    MESSAGE("VERSION is empty: " ${QTVERSION})
endif()
MESSAGE("VERSION:" ${QTVERSION} "--")

if (${QTVERSION} STREQUAL "QT5")
    # cmake -G "Visual Studio 12 2013" -S . -DV=QT5 -B qt5buildvs2013
    message("${VERSION} STREQUAL QT5")

    message("ENV{QTDIR}:" $ENV{QTDIR})
    message("ENV{QT5DIR}:" "$ENV{QT5DIR}")
    set(QT5DLL "$ENV{QT5DIR}\\bin")
    set(QT5LIB "$ENV{QT5DIR}\\lib")
    message("QT5DLL: " ${QT5DLL})
    message("QT5LIB: " ${QT5LIB})

    # set(QT5_DIR "$ENV{QTDIR}\\lib\\cmake\\Qt5")
    if (MSVC)
        set (CMAKE_PREFIX_PATH "$ENV{QT5DIR}")
    else()
    endif()
    message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

    find_package(Qt5Core)
    find_package(Qt5Xml)
    find_package(Qt5OpenGL)
    find_package(Qt5Widgets)
    find_package(Qt5LinguistTools)
    
    # find_package(QT5 REQUIRED COMPONENTS 
    #     Core
    #     Gui
    # )

    message("Qt5_FOUND: " ${Qt5_FOUND})
    message("Qt5Core_INCLUDE_DIRS: " ${Qt5Core_INCLUDE_DIRS})
    message("Qt5Xml_INCLUDE_DIRS: " ${Qt5Xml_INCLUDE_DIRS})
    message("Qt5Gui_INCLUDE_DIRS: " ${Qt5Gui_INCLUDE_DIRS})
    message("Qt5Widgets_INCLUDE_DIRS: " ${Qt5Widgets_INCLUDE_DIRS})
    message("Qt5OpenGL_INCLUDE_DIRS: " ${Qt5OpenGL_INCLUDE_DIRS})

    message("Qt5Widgets_LIBRARIES: " ${Qt5Widgets_LIBRARIES})
    message("Qt5Core_LIBRARIES:" ${Qt5Core_LIBRARIES})
    message("Qt5Gui_LIBRARIES:" ${Qt5Gui_LIBRARIES})
    message("Qt5Xml_LIBRARIES:" ${Qt5Xml_LIBRARIES})
    message("Qt5OpenGL_LIBRARIES:" ${Qt5OpenGL_LIBRARIES})

    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")

    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    link_directories(${PROJECT_NAME} ${QT5LIB} ${QT5DLL})

    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} )

elseif(${QTVERSION} STREQUAL "QT6")
    message("${VERSION} STREQUAL QT6")
    # cmake -G "MinGW Makefiles" -S . -DV=QT6 -B qt6buildmingw
    # cmake -G "Visual Studio 16 2019" -S . -DV=QT6 -B qt6buildvs2019

    # set(Qt6_DIR "D:\\Qt\\Qt6.2.4\\6.2.4\\mingw_64\\lib\\cmake\\Qt6")
    # set(Qt6_DIR "D:\\Qt\\Qt6.2.4\\6.2.4\\mingw_64")
    if (MSVC)
        message("--------msvc msvc msvc msvc------")
        set (CMAKE_PREFIX_PATH "D:\\Qt\\Qt6.2.4\\6.2.4\\msvc2019_64")
    else()
        set (CMAKE_PREFIX_PATH "D:\\Qt\\Qt6.2.4\\6.2.4\\mingw_64")
    endif()
    message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

    # find_package(Qt6 REQUIRED COMPONENTS 
    #     Core
    #     Gui
    #     Widgets
    #     Xml
    #     OpenGL
    # )
    find_package(Qt6Core)
    find_package(Qt6Xml)
    find_package(Qt6OpenGL)
    find_package(Qt6Widgets)
    find_package(Qt6LinguistTools)

    message("Qt6_FOUND: " ${Qt6_FOUND})
    message("Qt6Core_INCLUDE_DIRS: " ${Qt6Core_INCLUDE_DIRS})
    message("Qt6Xml_INCLUDE_DIRS: " ${Qt6Xml_INCLUDE_DIRS})
    message("Qt6Gui_INCLUDE_DIRS: " ${Qt6Gui_INCLUDE_DIRS})
    message("Qt6Widgets_INCLUDE_DIRS: " ${Qt6Widgets_INCLUDE_DIRS})
    message("Qt6OpenGL_INCLUDE_DIRS: " ${Qt6OpenGL_INCLUDE_DIRS})

    message("Qt6Widgets_LIBRARIES: " ${Qt6Widgets_LIBRARIES})
    message("Qt6Core_LIBRARIES:" ${Qt6Core_LIBRARIES})
    message("Qt6Gui_LIBRARIES:" ${Qt6Gui_LIBRARIES})
    message("Qt6Xml_LIBRARIES:" ${Qt6Xml_LIBRARIES})
    message("Qt6OpenGL_LIBRARIES:" ${Qt6OpenGL_LIBRARIES})

    set(QT6LIB "${CMAKE_PREFIX_PATH}\\lib")
    include_directories(${Qt6Widgets_INCLUDE_DIRS})
    link_directories(${PROJECT_NAME} ${QT6LIB} )

    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} ${Qt6Widgets_LIBRARIES} ${Qt6Core_LIBRARIES} )


else()
    MESSAGE("VERSION:" ${QTVERSION} "--")
endif() 