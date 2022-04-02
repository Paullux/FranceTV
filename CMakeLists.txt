cmake_minimum_required(VERSION 3.5)



if(WIN32)
    project(francetv VERSION 0.1)
else()
    project(francetv LANGUAGES CXX VERSION 0.1)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(APPLE)
set(CMAKE_MACOSX_BUNDLE ON)
endif()

if (UNIX)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
endif()

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.4\\msvc2019_64")
elseif(UNIX AND NOT APPLE)
    #set(CMAKE_PREFIX_PATH "/home/paul/Qt/5.15.2/gcc_64/lib/cmake")
else()
    set(CMAKE_PREFIX_PATH "/Users/paulw/Qt/5.15.2/clang_64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")
endif()

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

find_package(QT NAMES Qt6 COMPONENTS Widgets Core Svg Gui WebView WebEngineWidgets WebEngineCore WebEngineQuick Network REQUIRED)
find_package(Qt6 COMPONENTS Widgets Core Svg Gui WebView WebEngineWidgets WebEngineCore WebEngineQuick Network REQUIRED)

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
        FranceTV.rc
        FranceTV.desktop
        images/france-tv.ico
        images/france-tv.png
        images/france-tv.svg
        qt6.conf
        )

#if (WIN32)
#    qt6_add_resources(FranceTV.rc)
#endif()

if(WIN32)
    SET(GUI_TYPE WIN32)
else()
    SET(GUI_TYPE )
endif()

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(FranceTV
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#    )

#    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#else()
    if(ANDROID)
        add_library(FranceTV SHARED
            ${PROJECT_SOURCES}
        )
    elseif(WIN32)
        add_executable(FranceTV
            ${GUI_TYPE}
            ${PROJECT_SOURCES}
            ${APP_ICON_RESOURCE_WINDOWS}
        )
    else()
        add_executable(FranceTV main.cpp
                ${GUI_TYPE}
                ${PROJECT_SOURCES}
                )
    endif()

#    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#endif()

target_link_libraries(FranceTV PRIVATE Qt6::Core)
target_link_libraries(FranceTV PRIVATE Qt6::Svg)
target_link_libraries(FranceTV PRIVATE Qt6::Gui)
target_link_libraries(FranceTV PRIVATE Qt6::Widgets)
target_link_libraries(FranceTV PRIVATE Qt6::WebView)
target_link_libraries(FranceTV PRIVATE Qt6::WebEngineWidgets)
target_link_libraries(FranceTV PRIVATE Qt6::WebEngineCore)
target_link_libraries(FranceTV PRIVATE Qt6::WebEngineQuick)
target_link_libraries(FranceTV PRIVATE Qt6::Network)

if(APPLE)
    set_target_properties(FranceTV PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )
endif()

#if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FranceTV)
#endif()

if (UNIX AND NOT APPLE)
    install(TARGETS FranceTV
            RUNTIME DESTINATION bin)
    install(FILES qt6.conf DESTINATION "bin/")
    install(FILES FranceTV.desktop DESTINATION "share/applications")
    install(FILES images/france-tv.svg DESTINATION "share/icons/hicolor/scalable/apps/")
    install(FILES images/france-tv.png DESTINATION "share/icons/hicolor/256x256/apps/")
    install(FILES images/france-tv.ico DESTINATION "share/icons/hicolor/256x256/apps/")
endif()
