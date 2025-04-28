#pragma once 

#include <Window.hpp>

#include "../core/screen/screen.h"
#include "../input/input.h"
#include "match.h"
#include "../drawable/complex_drawable.h"
#include "../drawable/button/text_button.h"

namespace fow {

    class MatchScreen : public Screen {
    public:
        MatchScreen(std::shared_ptr<RCamera2D> camera) : Screen(camera) {}

        void Init() override;
        void Update() override;
        ScreenType Finish() override;

        void CheckInputs();     
    private:
        void PlacePlayerButtons(Player& player);
        void PlaceRenderMap(Player& player);
        void PlaceUnits(Player& player);
        void PlaceProbabilityMap(Player& player);

        void ShowSelectedUnitHud(const std::shared_ptr<Unit>& unit, const UnitManager& unit_manager);

        void InitMatch();
        void InitSelectedUnitHud();  

        std::unique_ptr<ComplexDrawable> selected_unit_hud_;
        std::shared_ptr<TextButton> end_turn_button;

        std::unique_ptr<Match> match_;
        Input input;
    };
}