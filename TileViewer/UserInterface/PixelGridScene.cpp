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

#include "PixelGridScene.hpp"

UserInterface::Widget::PixelGridScene::PixelGridScene(const std::vector<std::vector<QPixmap>>& pixmapArray, int sizeX, int sizeY) {
    setSceneRect(0, 0, sizeX, sizeY);
    int yOffset = 0;

    for (const auto& row : pixmapArray) {
        int xOffset = 0;

        for (const auto& pixmap : row) {
            QGraphicsPixmapItem* pixmapItem = addPixmap(pixmap);
            pixmapItem->setPos(xOffset, yOffset);

            xOffset += pixmap.width();
        }

        yOffset += pixmapArray.empty() ? 0 : pixmapArray[0].empty() ? 0 : row[0].height();
    }
}
