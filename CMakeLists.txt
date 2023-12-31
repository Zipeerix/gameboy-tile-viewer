cmake_minimum_required(VERSION 3.20)
project(gameboy_tile_viewer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(TileViewer)

add_executable(gameboy_tile_viewer
        TileViewer/TileViewer.cpp
        TileViewer/Application.cpp
        TileViewer/Application.hpp
        TileViewer/Utils/Host.cpp
        TileViewer/UserInterface/MainWindow.hpp
        TileViewer/UserInterface/MainWindow.cpp
        TileViewer/UserInterface/MainWindow.ui
        TileViewer/UserInterface/PixelGridScene.cpp
        TileViewer/Core/Tile.cpp
)

target_link_libraries(gameboy_tile_viewer
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

