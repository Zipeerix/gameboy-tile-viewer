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

#include <QFileDialog>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGenericMatrix>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include "Core/Tile.hpp"
#include "Utils/Host.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

UserInterface::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

UserInterface::MainWindow::~MainWindow() {
    delete ui;
}

void UserInterface::MainWindow::on_spinBox_valueChanged(int value) {
    m_offset = value;
    drawTiles();
}

void UserInterface::MainWindow::on_actionOpen_triggered() {
    QFileDialog romLoadDialog(this);
    romLoadDialog.setFileMode(QFileDialog::ExistingFile);
    romLoadDialog.setNameFilter("Gameboy ROM (*.gb)");
    if (romLoadDialog.exec()) {
        const auto inputFile = romLoadDialog.selectedFiles().back();
        loadRomFile(inputFile);
    }
}

void UserInterface::MainWindow::on_exportButton_clicked() {
    const auto outputPath =  QFileDialog::getSaveFileName(this, tr("Save Tilemap"), "", tr("Image File (*.png)"));
    if (!outputPath.isEmpty()) {
        QImage exportImage(m_graphicsScene->width(), m_graphicsScene->height(), QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&exportImage);
        m_graphicsScene->render(&painter);
        painter.end();

        exportImage.save(outputPath);
    }
}

void UserInterface::MainWindow::loadRomFile(const QString& path) {
    const auto fileLoadResult = Utils::loadExternalFileToVector(path.toStdString());
    if (!fileLoadResult.has_value()) {
        QMessageBox::critical(this, "Error", "Unable to load ROM from path: " + path);
        return;
    }

    m_romBytes  = fileLoadResult.value();

    setWindowTitle("Gameboy Tile Viewer : " + path);
    drawTiles();
}

void UserInterface::MainWindow::drawTiles() {
    const auto tileCount = (m_romBytes.size() - m_offset) / GameBoy::Const::Tile::sizeInBytes;

    std::vector<GameBoy::Tile> tiles{};
    tiles.reserve(tileCount);

    for (auto i = m_offset; i < m_romBytes.size(); i += GameBoy::Const::Tile::sizeInBytes) {
        const auto startIterator = m_romBytes.begin() + m_offset + i;
        const auto endIterator   = startIterator + GameBoy::Const::Tile::sizeInBytes;

        std::vector<GameBoy::Byte> tileBytes = std::vector<GameBoy::Byte>(startIterator, endIterator);

        tiles.emplace_back(tileBytes);
    }

    std::vector<QPixmap> tilePixmaps;

    for (auto& tile : tiles) {
        constexpr int tileColorDataByteCount = GameBoy::Const::Tile::width * GameBoy::Const::Tile::width * Const::bytesPerColor;
        std::array<GameBoy::Byte, tileColorDataByteCount> data{0};

        for (int i = 0; i < tileColorDataByteCount; i += Const::bytesPerColor) {
            const GameBoy::PixelColor& color = tile[i / Const::bytesPerColor];
            data[i + Const::ColorIndex::Red]   = color.red;
            data[i + Const::ColorIndex::Green] = color.green;
            data[i + Const::ColorIndex::Blue]  = color.blue;
            data[i + Const::ColorIndex::Alpha] = color.alpha;
        }

        QImage image(data.data(), GameBoy::Const::Tile::width, GameBoy::Const::Tile::height, QImage::Format_ARGB32_Premultiplied);
        image = image.scaled(GameBoy::Const::Tile::width * Const::tileScaleFactor, GameBoy::Const::Tile::height * Const::tileScaleFactor);

        tilePixmaps.push_back(QPixmap::fromImage(image));
    }

    std::vector<std::vector<QPixmap>> tilePixmaps2D;

    int rows = tiles.size() / GameBoy::Const::Tile::sizeInBytes;
    for (int i = 0; i < rows * GameBoy::Const::Tile::sizeInBytes; i += GameBoy::Const::Tile::sizeInBytes) {
        const auto startIterator = tilePixmaps.begin() + i;
        const auto endIterator   = startIterator + GameBoy::Const::Tile::sizeInBytes;

        std::vector<QPixmap> rowPixMaps = std::vector<QPixmap>(startIterator, endIterator);

        tilePixmaps2D.push_back(rowPixMaps);
    }

    int sizeX = GameBoy::Const::Tile::sizeInBytes * GameBoy::Const::Tile::width * Const::tileScaleFactor;
    int sizeY = rows * GameBoy::Const::Tile::height * Const::tileScaleFactor;

    m_graphicsScene = new Widget::PixelGridScene(tilePixmaps2D, sizeX, sizeY);
    m_graphicsScene->setSceneRect(0, 0, sizeX, sizeY);

    ui->graphicsView->setScene(m_graphicsScene);
}
