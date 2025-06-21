#pragma once 

#include <memory>

#include "../core/screen/screen.h"
#include "../drawable/button/text_button.h"
#include "../drawable/complex_drawable.h"
#include "../input/input.h"
#include "match.h"
#include "player.h"
#include "targets/units/unit.h"
#include <Camera2D.hpp>

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
  void PlacePossibleTiles(Player& player);

  void ShowSelectedUnitHud(const std::shared_ptr<Unit>& unit, const UnitManager& unit_manager);

  void InitMatch();
  void InitPanelHud();
  void InitSelectedUnitHud();

  std::unique_ptr<ComplexDrawable> selected_unit_hud_;
  std::unique_ptr<ComplexDrawable> panel_hud_;

  std::unique_ptr<Match> match_;
  Input input;

  bool show_prev_map_ = false;
  bool show_fow = true;
  bool show_zero = false;
};

} // namespace fow