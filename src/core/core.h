#pragma once

#include <memory>

#include <Window.hpp>

#include "screen/screen.h"
#include "screen/screen_controller.h"

namespace fow {

    class Core {
    public:
        static Core& Get();
        void Start();       
        Core(Core const&) = delete;
        void operator=(Core const&) = delete;
        
    private:
        Core() {};
        void InitWindow(int width, int height, bool fullscreen);
        void Loop();

        RWindow window_;
        std::unique_ptr<ScreenController> screen_controller_;
    };
}