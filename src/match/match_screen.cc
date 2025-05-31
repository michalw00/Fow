#include "match_screen.h"

#include <cstdlib>
#include <format>
#include <initializer_list>
#include <memory>
#include <string>

#include <Color.hpp>
#include <Rectangle.hpp>
#include <Text.hpp>
#include <Vector2.hpp>
#include <raylib.h>

#include "../core/screen/screen.h"
#include "../drawable/button/text_button.h"
#include "../drawable/button/texture_button.h"
#include "../drawable/complex_drawable.h"
#include "../drawable/rectangle.h"
#include "../drawable/text.h"
#include "../drawable/texture_manager.h"
#include "../structs/vector2i.h"
#include "match.h"
#include "player.h"
#include "targets/units/unit.h"

namespace fow {

void MatchScreen::Init() {
  InitMatch();
  InitSelectedUnitHud();

  RVector2 prev_probabilities_position = { basic_width_ - 160.f, basic_height_ - 100.f };
  RText prev_probabilities_text("PREV MAP", 45.f);
  auto InvertMaps = [&]() {
    auto& player = match_->GetCurrentPlayer();
    player.InvertShowPrevMap();
  };
  prev_probabilities_button_ = std::make_shared<TextButton>(prev_probabilities_position, InvertMaps, prev_probabilities_text, true);
  RVector2 end_turn_position = { basic_width_ - 160.f, basic_height_ - 50.f };
  RText end_turn_text("END TURN", 45.f);
  end_turn_button_ = std::make_shared<TextButton>(end_turn_position, [&]() { match_->EndTurn(); }, end_turn_text, true);
}

void MatchScreen::InitMatch() {
  match_ = std::make_unique<Match>();
  match_->InitMap(18, 32);
  match_->InitPlayers(basic_width_, basic_height_, *camera_.get());
}

void MatchScreen::InitSelectedUnitHud() {
  RVector2 origin(basic_width_ / 2.f, basic_height_ - 120.f);

  std::string unit_type_name = "UNIT_TYPE";
  std::shared_ptr<Text> unit_type_text = std::make_shared<Text>(origin, RText("", 40.f));
  ComplexDrawablePart unit_type(unit_type_name, unit_type_text);

  std::string hp_name = "HP";
  std::shared_ptr<Text> hp_text = std::make_shared<Text>(origin + RVector2(0.f, 40.f), RText("", 25.f), true);
  ComplexDrawablePart hp(hp_name, hp_text);

  std::string mp_name = "MP";
  std::shared_ptr<Text> mp_text = std::make_shared<Text>(origin + RVector2(0.f, 80.f), RText("", 25.f), true);
  ComplexDrawablePart mp(mp_name, mp_text);

  std::initializer_list<ComplexDrawablePart> parts = { unit_type, hp, mp };
  selected_unit_hud_ = std::make_unique<ComplexDrawable>(parts);
}

void MatchScreen::Update() {
  auto& player = match_->GetCurrentPlayer();
  player.Update(*match_->GetMap().get(), match_->GetOtherPlayers());

  camera_ = player.GetCamera();
  PlacePlayerButtons(player);
  auto& unit = player.GetSelectedUnit();

  if (unit) {
    ShowSelectedUnitHud(unit, match_->GetUnitManager());
  }

  if (player.GetShowPrevMap()) {
    auto layer = std::make_shared<Rectangle>(RVector2(0, 0), RVector2(10000.f, 10000), RColor::Gray().Alpha(0.2f));
    PlaceDrawable(layer, true);
  }

  PlaceDrawable(end_turn_button_, true);
  PlaceDrawable(prev_probabilities_button_, true);

  CheckInputs();
}

ScreenType MatchScreen::Finish() {
  return ScreenType::kMenu;
}

void MatchScreen::CheckInputs() {
  if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
    input.DragScreen(camera_.get());
  }
  if (float mouse_wheel = GetMouseWheelMove(); std::abs(mouse_wheel) > 0.0f) {
    input.Zoom(camera_.get(), mouse_wheel * 0.05f, 0.5f, 4.f);

  }
  if (IsKeyPressed(KEY_ENTER)) {
    match_->EndTurn();
  }
}

void MatchScreen::PlacePlayerButtons(Player& player) {
  PlaceRenderMap(player);
  PlaceUnits(player);
  PlaceProbabilityMap(player);
}

void MatchScreen::PlaceRenderMap(Player& player) {
  auto& buttons = player.GetRenderMap();
  for (auto& row : buttons) {
    for (auto& button : row) {
      PlaceDrawable(button);
    }
  }
}

void MatchScreen::PlaceUnits(Player& player) {
  auto& buttons = player.GetRenderMap();
  auto& units = player.GetUnits();
  const auto& unit_manager = match_->GetUnitManager();
  for (auto& unit : units) {
    Vector2I unit_position = unit->GetPosition();
    RRectangle area = buttons[unit_position.x][unit_position.y]->GetArea();
    RVector2 size = { area.GetSize() };
    size.x *= 0.95f;
    RVector2 ratio = { 1.0, 1.5 };
    size /= ratio;
    RVector2 position = area.GetPosition();
    position += (area.GetSize() - size) / 2.f;
    auto lmb_action = [&player, &unit]() {
      if (!player.GetSelectedUnit() && !player.GetShowPrevMap()) {
        player.SetSelectedUnit(unit);
        player.ClearSelectedTile();
      } else {
        player.SetSelectedUnit(nullptr);
      }
    };
    std::shared_ptr<TextureButton> button = std::make_shared<TextureButton>(position, size, lmb_action, unit_manager.GetTexture(unit->GetType()));

    button->SetIsSelected(player.GetSelectedUnit() == unit);

    PlaceDrawable(button);
  }
}

void MatchScreen::PlaceProbabilityMap(Player& player) {
  auto& buttons = player.GetRenderMap();

  auto& probability_map = player.GetProbabilitiesMap();

  for (int i = 0; i < probability_map.size(); ++i) {
    for (int j = 0; j < probability_map[0].size(); ++j) {
      Vector2I tile_position = { i, j };
      RRectangle area = buttons[i][j]->GetArea();
      RVector2 size = { area.GetSize() };
      RVector2 position = area.GetPosition();
      position += size / 2.f;
      float probability = probability_map[i][j];
      std::string text_string = "";
      if (probability > -0.01f) {
        text_string = std::format("{:.1f}", probability * 100) + '%';
      }
      float r = 255.f;
      if (probability < 0.5f) {
        r *= probability + 0.45f;
      }
      float g = 255.f;
      if (probability > 0.5f) {
        g *= 1 - probability;
      }
      float b = 0.f;
      RColor color(r, g, b);
      RText rtext(text_string, size.GetX() * 0.3f, color);

      std::shared_ptr<Text> text = std::make_shared<Text>(position, rtext);
      PlaceDrawable(text);
    }
  }
}

void MatchScreen::ShowSelectedUnitHud(const std::shared_ptr<Unit>& unit, const UnitManager& unit_manager) {
  UnitType unit_type = unit->GetType();
  auto unit_modifiers = unit_manager.GetResource(unit_type);
  selected_unit_hud_->EditText("UNIT_TYPE", unit_manager.GetName(unit_type));

  std::string current_hp = std::format("{:.1f}", unit->GetHealthPoints());
  std::string max_hp = std::format("{:.1f}", unit_modifiers->start_health_points);
  selected_unit_hud_->EditText("HP", "HP: " + current_hp + " / " + max_hp);

  std::string current_mp = std::format("{:.1f}", unit->GetMovementPoints());
  std::string max_mp = std::format("{:.1f}", unit_modifiers->start_movement_points);
  selected_unit_hud_->EditText("MP", "MP: " + current_mp + " / " + max_mp);

  auto& hud_drawables = selected_unit_hud_->GetDrawables();
  for (auto& hud_drawable : hud_drawables) {
    PlaceDrawable(hud_drawable, true);
  }
}

} // namespace fow