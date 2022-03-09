cmake_minimum_required(VERSION 3.5)

project(FranceTV VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.3\\msvc2019_64")
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019_64")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt5 COMPONENTS Widgets Core WebView WebEngineWidgets WebEngineCore Network LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core WebView WebEngineWidgets WebEngineCore Network LinguistTools REQUIRED)

set(TS_FILES FranceTV_fr_FR.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        framelesswindow/framelesswindow.cpp
        framelesswindow/framelesswindow.h
        framelesswindow/framelesswindow.ui
        framelesswindow/windowdragger.cpp
        framelesswindow/windowdragger.h
        DarkStyle.cpp
        DarkStyle.h
        darkstyle.qrc
        framelesswindow.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FranceTV
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(FranceTV SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(FranceTV
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(FranceTV PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(FranceTV PRIVATE Qt${QT_VERSION_MAJOR}::WebView)
target_link_libraries(FranceTV PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
target_link_libraries(FranceTV PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineCore)
target_link_libraries(FranceTV PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(FranceTV PRIVATE Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(FranceTV PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FranceTV)
endif()
