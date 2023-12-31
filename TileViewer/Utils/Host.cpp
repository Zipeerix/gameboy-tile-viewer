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

#include <stdexcept>
#include <iterator>
#include <fstream>
#include "Host.hpp"

std::expected<std::vector<std::uint8_t>, Utils::ErrorString> Utils::loadExternalFileToVector(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.good()) {
        return std::unexpected("unable to open file at: " + path);
    }

    file.unsetf(std::ios::skipws);

    file.seekg(0, std::ios::end);
    const std::size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<std::uint8_t> bytes;
    bytes.reserve(file_size);

    try {
        bytes.insert(bytes.begin(), std::istream_iterator<std::uint8_t>(file), std::istream_iterator<std::uint8_t>());
    } catch (const std::exception& e) {
        return std::unexpected("unable to read file at: " + path);
    }

    file.close();

    return bytes;
}
