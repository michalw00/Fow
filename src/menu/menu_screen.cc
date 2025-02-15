#include "menu_screen.h"

#include <memory>

#include <Text.hpp>
#include <Vector2.hpp>

#include "../drawable/button/text_button.h"

namespace fow {

    void MenuScreen::Init() {
        AddRText("Title", RText("FOW", 120.0f));
        AddRText("Start game", RText("Start game", 50.f));
        AddRText("Leave", RText("Leave", 50.f));
        AddRText("w8", RText("w8 for commit", 40.f));

        RVector2 title_position = { 0, -300 };
        std::shared_ptr<Text> title = std::make_shared<Text>(title_position, rtexts_["Title"]);
        PlaceText(title);

        RVector2 start_game_position = { 0, 0 };
        std::shared_ptr<Button> start_game_button = std::make_shared<TextButton>(
            start_game_position, [this]() { should_finish_ = true; }, rtexts_["Start game"]
        );
        PlaceButton(start_game_button);

        RVector2 leave_position = { 0, 100 };
        std::shared_ptr<Button> leave_button = std::make_shared<TextButton>(
            leave_position, [this]() { should_close_ = true; }, rtexts_["Leave"]
        );
        PlaceButton(leave_button);
    }

    void MenuScreen::Update() {

    }

    ScreenType MenuScreen::Finish() {
        return ScreenType::kMatch;
    }
}