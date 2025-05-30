#include "menu_screen.h"

#include <memory>

#include <Text.hpp>
#include <Vector2.hpp>

#include "../core/screen/screen.h"
#include "../drawable/button/text_button.h"
#include "../drawable/text.h"

namespace fow {

void MenuScreen::Init() {
  RVector2 title_position = { 0, -300 };
  title = std::make_shared<Text>(title_position, RText("FOW", 120.0f));

  RVector2 start_game_position = { 0, 0 };
  start_game_button = std::make_shared<TextButton>(
      start_game_position, [this]() { should_finish_ = true; }, RText("Start game", 50.f)
  );

  RVector2 leave_position = { 0, 100 };
  leave_button = std::make_shared<TextButton>(
      leave_position, [this]() { should_close_ = true; }, RText("Leave", 50.f)
  );
}

void MenuScreen::Update() {
  PlaceDrawable(title);
  PlaceDrawable(start_game_button);
  PlaceDrawable(leave_button);
}

ScreenType MenuScreen::Finish() {
  return ScreenType::kMatch;
}

} // namespace fow