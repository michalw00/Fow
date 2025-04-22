#pragma once 

#include "../core/screen/screen.h"

namespace fow {

    class MenuScreen : public Screen {
    public:
        MenuScreen(std::shared_ptr<RCamera2D> camera) : Screen(camera) {}

        void Init() override;
        void Update() override;
        ScreenType Finish() override;

    private:
        std::shared_ptr<Text> title;
        std::shared_ptr<Button> start_game_button;
        std::shared_ptr<Button> leave_button;
    };
}