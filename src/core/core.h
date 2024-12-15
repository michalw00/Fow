#pragma once

#include <Window.hpp>

#include "screen/screen.h"

namespace fow {

    class Core {
    public:
        static Core& Get();
        void Start();       
        Core(Core const&) = delete;
        void operator=(Core const&) = delete;
        
    private:
        Core();
        void InitWindow();
        void Loop();


        ScreenType current_screen_;
        RWindow window_;
    };
}