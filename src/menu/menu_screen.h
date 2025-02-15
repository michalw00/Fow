#pragma once 

#include "../core/screen/screen.h"

namespace fow {

    class MenuScreen : public Screen {
    public:
        void Init() override;
        void Update() override;
        ScreenType Finish() override;
    private:
    };
}