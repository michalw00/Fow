#include "menu_screen.h"

#include <iostream>

namespace fow {
    void MenuScreen::Init() {
        AddText("Title", RText("FOW", 100.0f));
        camera_ = std::make_shared<RCamera2D>();
    }
    void MenuScreen::Draw() {
        Update();
        for (auto drawable_text : drawable_texts_) {
            RText& text = drawable_text.first;
            RVector2& position = drawable_text.second;

            text.Draw(position);
        } 
    }
    void MenuScreen::Update() {
        drawable_texts_.clear();

        RVector2 title_position = { 0,0 };
        PlaceText("Title", title_position);
    }
    void MenuScreen::Unload() {

    }
    ScreenType MenuScreen::Finish() {
        return ScreenType::kMenu;
    }
}