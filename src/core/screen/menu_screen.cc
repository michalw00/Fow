#include "menu_screen.h"

#include <memory>

#include <Camera2D.hpp>
#include <Text.hpp>
#include <Vector2.hpp>

#include "screen.h"

namespace fow {

    void MenuScreen::Init() {
        AddText("Title", RText("FOW", 120.0f));
        AddText("Start game", RText("Start game", 50.f));
        AddText("Leave", RText("Leave", 50.f));
        AddText("w8", RText("w8 for commit", 40.f));

        RVector2 title_position = { 0, -300 };
        PlaceText(texts_["Title"], title_position, true);
        RVector2 start_game_position = { 0, 0 };
        PlaceButton(texts_["Start game"], start_game_position, true, [this]() {
            RVector2 w8_position = { 0, -100 };
            PlaceText(texts_["w8"], w8_position, true);
        });
        RVector2 leave_position = { 0, 100 };
        PlaceButton(texts_["Leave"], leave_position, true, [this]() {should_close_ = true; });
    }

    void MenuScreen::Update() {

    }

    ScreenType MenuScreen::Finish() {
        return ScreenType::kMenu;
    }
}