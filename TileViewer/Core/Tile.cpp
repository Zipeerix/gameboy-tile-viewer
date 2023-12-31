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

#include "Tile.hpp"

constexpr bool isBitSet(int value, int bitIndex) {
    return value & (1 << bitIndex);
}

GameBoy::Tile::Tile(const std::vector<GameBoy::Byte>& bytes) {
    for (int y = 0; y < Const::Tile::height; y++) {
        auto byteIndex = y * 2;
        Byte lowByte = bytes[byteIndex];
        Byte highByte = bytes[byteIndex + 1];

        for (int x = 0; x < Const::Tile::width; x++) {
            int highBit = (highByte & (0b10000000 >> x)) > 0 ? 2 : 0;
            int lowBit = (lowByte & (0b10000000 >> x)) > 0 ? 1 : 0;
            m_pixels[(y * Const::Tile::width) + x] = Const::Tile::colors[highBit + lowBit];
        }
    }
}


GameBoy::PixelColor& GameBoy::Tile::operator[](int index) {
    return m_pixels[index];
}
