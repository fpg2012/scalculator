cmake_minimum_required(VERSION 3.5)

project(scalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

set(TS_FILES zh_CN.ts)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
        historyitemdata.h
        constitemdata.h
        backend.h backend.cpp
        mydelegate.cpp mydelegate.h
        constantdialog.cpp constantdialog.h constantdialog.ui
        constdelegate.h constdelegate.cpp
        unitconvertdialog.h unitconvertdialog.cpp unitconvertdialog.ui
        unitmanager.h unitmanager.cpp
        unit.h
        unitcategory.h
        unitdelegate.h unitdelegate.cpp
	${CMAKE_SOURCE_DIR}/sevaluator/sevaluator.h
        resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(scalculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(scalculator SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(scalculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_custom_target(
	sevaluator_lib
	COMMAND make
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/sevaluator
	)
include_directories(sevaluator)

target_link_libraries(scalculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
	${CMAKE_SOURCE_DIR}/sevaluator/libsevaluator.a
	gmp
	mpfr
        Threads::Threads
	)

add_dependencies(scalculator sevaluator_lib)

set_target_properties(scalculator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(scalculator)
endif()


install(TARGETS scalculator DESTINATION bin)
install(FILES misc/scalculator.svg DESTINATION share/icons/hicolor/scalable/apps)
install(FILES misc/scalculator.desktop DESTINATION share/applications)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Packing)
