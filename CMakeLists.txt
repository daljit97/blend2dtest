cmake_minimum_required(VERSION 3.5)

project(Blend2DTest LANGUAGES CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -lrt")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_library(blend2d blend2d REQUIRED)
find_path(blend2d_INCLUDES blend2d.h)

if(NOT blend2d_INCLUDES)
  message(FATAL_ERROR "blend2d library not found")
endif()

if(ANDROID)
    add_library(Blend2DTest SHARED
      main.cpp
      drawingcanvas.cpp
      qml.qrc
    )
else()
    add_executable(Blend2DTest
      main.cpp
      drawingcanvas.cpp
      tabletwindow.cpp
      qml.qrc
    )
endif()

target_compile_definitions(Blend2DTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Blend2DTest
  PRIVATE Qt5::Core Qt5::Quick
  PRIVATE ${blend2d})

target_include_directories(Blend2DTest PRIVATE ${blend2d_INCLUDES})
