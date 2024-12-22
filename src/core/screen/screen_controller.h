#pragma once 

#include "screen.h"

#include <memory>

#include "Window.hpp"

namespace fow {

    class ScreenController {
    public:
        ScreenController(ScreenType start_screen_type);

        void DrawScreen(RWindow& window);
    private:

        std::shared_ptr<Screen> CreateScreen(ScreenType screen_type);

        std::shared_ptr<Screen> current_screen_;
    };
}