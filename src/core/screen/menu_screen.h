#pragma once 

#include "screen.h"

#include <Window.hpp>

namespace fow {

    class MenuScreen : public Screen {
    public:
        void Init() override;
        void Update() override;
        ScreenType Finish() override;
    private:
    };
}