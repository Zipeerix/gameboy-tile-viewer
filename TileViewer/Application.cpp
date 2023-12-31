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

#include "UserInterface/MainWindow.hpp"
#include "Application.hpp"

Application::Application(int argc, char** argv) :
        m_argc(argc),
        m_argv(argv)
{
    std::vector<std::string> args(argv + 1, argv + argc);

    std::for_each(args.cbegin(), args.cend(), [&](const auto& arg) {
        // Note: If any args are added they should be handled here
    });
}

int Application::run() {
    QApplication app(m_argc, m_argv);

    UserInterface::MainWindow window;
    window.show();

    const auto result = app.exec();

    return result;
}
