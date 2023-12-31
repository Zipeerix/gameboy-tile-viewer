/***********************************************************************************************************************
*
*   Copyright 2023 CockatooBoy (TileViewer)
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
***********************************************************************************************************************/

#ifndef USERINTERFACE_MAINWINDOW_HPP
#define USERINTERFACE_MAINWINDOW_HPP

#include <QGraphicsView>
#include <QMainWindow>
#include <string>
#include "Utils/Types.hpp"
#include "UserInterface/PixelGridScene.hpp"

namespace UserInterface {
    namespace Const {
        constexpr int tileScaleFactor = 5;
        constexpr int tilesPerRow     = 10;

        constexpr int bytesPerColor = 4;

        namespace ColorIndex {
            constexpr int Red   = 0;
            constexpr int Green = 1;
            constexpr int Blue  = 2;
            constexpr int Alpha = 3;
        }
    }

    namespace Ui {
        class MainWindow;
    }

    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

    private slots:
        void on_actionOpen_triggered();
        void on_exportButton_clicked();
        void on_spinBox_valueChanged(int value);

    private:
        Ui::MainWindow* ui;
        Widget::PixelGridScene* m_graphicsScene;

        std::vector<GameBoy::Byte> m_romBytes;
        int m_offset = 0;

        void loadRomFile(const QString& path);

        void drawTiles();
    };
}

#endif // USERINTERFACE_MAINWINDOW_HPP
