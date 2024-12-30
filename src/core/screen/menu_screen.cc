#include "menu_screen.h"

#include <memory>

#include <Camera2D.hpp>
#include <Text.hpp>
#include <Vector2.hpp>

#include "screen.h"

namespace fow {

    void MenuScreen::Init() {
        AddText("Title", RText("FOW", 100.0f));
        AddText("Leave", RText("Leave", 50.f));
    }

    void MenuScreen::Draw() {
        for (auto drawable_text : drawable_texts_) {
            RText& text = drawable_text.text;

            RVector2& position = drawable_text.position;

            text.Draw(position);
        }
    }

    void MenuScreen::Update() {
        drawable_texts_.clear();

        RVector2 title_position = { 0, -200 };
        PlaceText("Title", title_position, true);
        RVector2 leave_position = { 0, 100 }; 
        PlaceText("Leave", leave_position, true);
    }

    void MenuScreen::Unload() {

    }

    ScreenType MenuScreen::Finish() {
        return ScreenType::kMenu;
    }
}