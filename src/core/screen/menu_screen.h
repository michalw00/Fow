#pragma once 

#include "screen.h"

namespace fow {

    class MenuScreen : public Screen {
    public:
        void Init() override;
        void Update() override;
        void Draw() override;
        void Unload() override;
        ScreenType Finish() override;
    private:
    };
}