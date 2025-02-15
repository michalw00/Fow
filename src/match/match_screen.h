#pragma once 

#include "../core/screen/screen.h"
#include "match.h"

#include <Window.hpp>

namespace fow {

    class MatchScreen : public Screen {
    public:
        void Init() override;
        void Update() override;
        ScreenType Finish() override;
    private:
        Match match_;
    };
}