#pragma once 

#include "../core/screen/screen.h"
#include "../input/input.h"
#include "match.h"

#include <Window.hpp>


namespace fow {

    class MatchScreen : public Screen {
    public:
        MatchScreen(std::shared_ptr<RCamera2D> camera) : Screen(camera) {}

        void Init() override;
        void Update() override;
        ScreenType Finish() override;

        void CheckInputs();
        void PlaceButtonsFromTiles(std::vector<std::vector<Tile>> tiles);
    private:
        std::unique_ptr<Match> match_;
        Input input;
    };
}