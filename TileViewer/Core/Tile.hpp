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

#ifndef GAMEBOY_TILE_VIEWER_TILE_HPP
#define GAMEBOY_TILE_VIEWER_TILE_HPP

#include <vector>
#include <array>
#include "Utils/Types.hpp"

namespace GameBoy {
    struct PixelColor {
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;
        std::uint8_t alpha;
    };

    namespace Const {
        namespace Tile {
            constexpr int height = 8;
            constexpr int width  = 8;

            constexpr int sizeInBytes = 16;

            constexpr PixelColor colors[4] = {
                    {0xD0, 0xF8, 0xE0, 0xFF}, // Lightest Green
                    {0x70, 0xC0, 0x88, 0xFF}, // Light Green
                    {0x56, 0x68, 0x34, 0xFF}, // Dark Green
                    {0x20, 0x18, 0x08, 0xFF}, // Darkest Green
            };
        }
    }

    class Tile {
    public:
        explicit Tile(const std::vector<GameBoy::Byte>& bytes);

        PixelColor& operator[](int index);

    private:
        std::array<PixelColor, Const::Tile::height * Const::Tile::width> m_pixels;
    };
}

#endif //GAMEBOY_TILE_VIEWER_TILE_HPP
