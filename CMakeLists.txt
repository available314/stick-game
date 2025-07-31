cmake_minimum_required(VERSION 3.16)

project(sticks_game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        gamewindow.cpp
        gamewindow.h
        gamewindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(sticks_game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        PlayWindow.h
        PlayWindow.cpp
        GameType.h
        StandardStrategy.h StandardMove.h RowMove.h RowGrundyStrategy.h RowGraphStrategy.h PlayWindow.h iPlayer.h iBotStrategy.h iCheckMove.h human.h gamewindow.h GameType.h Game.h bot.h
        bot.cpp Game.cpp gamewindow.cpp human.cpp iBotStrategy.cpp iPlayer.cpp main.cpp PlayWindow.cpp RowGraphStrategy.cpp RowGrundyStrategy.cpp RowMove.cpp StandardMove.cpp StandardStrategy.cpp
        NormalModeStrategy.h
        NormalModeStrategy.cpp
        NormalModeMove.cpp
        NormalModeMove.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET sticks_game APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(sticks_game SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(sticks_game
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(sticks_game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.sticks_game)
endif()
set_target_properties(sticks_game PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS sticks_game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sticks_game)
endif()
