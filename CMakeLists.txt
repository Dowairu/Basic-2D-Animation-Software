
cmake_minimum_required(VERSION 3.12)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(BTECAE_QT VERSION 0.1 LANGUAGES CXX)

set(TargetName BTECAE_QT)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(NGL CONFIG REQUIRED)


set(PROJECT_SOURCES
        src/main.cpp
        src/MainWindow.cpp
        src/main.cpp
        src/NGLScene.cpp
        src/Camera.cpp
        #src/Keyframe.cpp
        src/Shape.cpp
        src/Timeline.cpp
        src/Layer.cpp
        src/NGLSceneMouseControls.cpp
        include/MainWindow.h
        include/NGLScene.h
        include/Camera.h
        include/Shape.h
        include/Timeline.h
        include/Keyframe.h
        include/Layer.h
        include/RGBA.h
        ui/MainWindow.ui

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BTECAE_QT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BTECAE_QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BTECAE_QT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BTECAE_QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BTECAE_QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets NGL)



set_target_properties(BTECAE_QT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BTECAE_QT)
endif()

add_custom_target(${TargetName}CopyShaders ALL
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/shaders
   $<TARGET_FILE_DIR:${TargetName}>/shaders
)
