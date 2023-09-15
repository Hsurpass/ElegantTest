# cmake -G "Visual Studio 12 2013"  -D ALL_BUILD=OFF -D ZERO_CHECK=OFF -B build
#  cmake --build .\build\ --config Release
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(hello)


message("ENV{QTDIR}:" $ENV{QTDIR})
message("ENV{QT5DIR}:" "$ENV{QT5DIR}")
# message("ENV{QTCMAKE}:" $ENV{QTCMAKE})
set(QT5DLL "$ENV{QT5DIR}\\bin")
set(QT5LIB "$ENV{QT5DIR}\\lib")
message("QT5DLL: " ${QT5DLL})
message("QT5LIB: " ${QT5LIB})

set(QT5_DIR "$ENV{QTDIR}\\lib\\cmake\\Qt5")
set (CMAKE_PREFIX_PATH "$ENV{QT5DIR}")
message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

find_package(Qt5Core)
find_package(Qt5Xml)
find_package(Qt5OpenGL)
find_package(Qt5Widgets)
find_package(Qt5LinguistTools)
find_package(QT5
    # COMPONENTS 
    # Core
    # Gui
)

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

message("------------QT_WIDGETS_LIB: " ${${Qt5Core_LIBRARIES}})

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")

include_directories(${Qt5Widgets_INCLUDE_DIRS})
link_directories(${PROJECT_NAME} ${QT5LIB} ${QT5DLL})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} )