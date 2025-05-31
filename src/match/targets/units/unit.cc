#include "unit.h"

#include <memory>
#include <string>

#include "../target.h"

namespace fow {

void Unit::Attack(std::shared_ptr<Target> other) {
  other->Defense(this);
}

UnitModifiers::UnitModifiers(UnitType unit_type) {
  switch (unit_type) {
    case UnitType::kAntiTank:
      start_movement_points = 2.0f;
      start_health_points = 100.0f;

      movement_cost_plains = 1.0f;
      movement_cost_hills = 2.0f;
      movement_cost_mountains = 3.0f;
      movement_cost_marsh = 2.5f;
      movement_cost_forest = 1.5f;
      attack_on_bonus_plains = 0.0f;
      attack_on_bonus_hills = 0.1f;
      attack_on_bonus_mountains = 0.2f;
      attack_on_bonus_marsh = -0.1f;
      attack_on_bonus_forest = 0.05f;

      attack_against_bonus_plains = 0.0f;
      attack_against_bonus_hills = -0.1f;
      attack_against_bonus_mountains = -0.2f;
      attack_against_bonus_marsh = 0.1f;
      attack_against_bonus_forest = -0.05f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.15f;
      defense_bonus_mountains = 0.3f;
      defense_bonus_marsh = -0.05f;
      defense_bonus_forest = 0.1f;

      attack_range = 3.0f;
      recon_range = 2.0f;
      bridge_damage = 0.5f;
      road_damage = 0.2f;
      break;

    case UnitType::kArtillery:
      start_movement_points = 1.5f;
      start_health_points = 80.0f;

      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.5f;
      movement_cost_mountains = 2.0f;
      movement_cost_marsh = 2.0f;
      movement_cost_forest = 1.5f;

      attack_on_bonus_plains = 0.1f;
      attack_on_bonus_hills = 0.15f;
      attack_on_bonus_mountains = 0.0f;
      attack_on_bonus_marsh = -0.05f;
      attack_on_bonus_forest = 0.0f;
      attack_against_bonus_plains = -0.1f;
      attack_against_bonus_hills = -0.15f;
      attack_against_bonus_mountains = 0.0f;
      attack_against_bonus_marsh = 0.05f;
      attack_against_bonus_forest = 0.0f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.05f;
      defense_bonus_mountains = 0.0f;
      defense_bonus_marsh = -0.1f;
      defense_bonus_forest = -0.05f;

      attack_range = 5.0f;
      recon_range = 1.0f;
      bridge_damage = 0.1f;
      road_damage = 0.05f;
      break;
    case UnitType::kElectronicWarfare:
      start_movement_points = 5.0f;
      start_health_points = 90.0f;
      movement_cost_plains = 1.0f;
      movement_cost_hills = 2.0f;
      movement_cost_mountains = 2.0f;
      movement_cost_marsh = 2.0f;
      movement_cost_forest = 1.0f;

      attack_on_bonus_plains = 0.0f;
      attack_on_bonus_hills = 0.0f;
      attack_on_bonus_mountains = 0.0f;
      attack_on_bonus_marsh = 0.0f;
      attack_on_bonus_forest = 0.0f;

      attack_against_bonus_plains = 0.0f;
      attack_against_bonus_hills = 0.0f;
      attack_against_bonus_mountains = 0.0f;
      attack_against_bonus_marsh = 0.0f;
      attack_against_bonus_forest = 0.0f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.0f;
      defense_bonus_mountains = 0.0f;
      defense_bonus_marsh = 0.0f;
      defense_bonus_forest = 0.0f;

      attack_range = 0.0f;
      recon_range = 1.0f;
      bridge_damage = 0.0f;
      road_damage = 0.0f;
      break;
    case UnitType::kInfantry:
      start_movement_points = 2.0f;
      start_health_points = 120.0f;

      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.2f;
      movement_cost_mountains = 1.5f;
      movement_cost_marsh = 1.3f;
      movement_cost_forest = 1.1f;

      attack_on_bonus_plains = 0.0f;
      attack_on_bonus_hills = 0.1f;
      attack_on_bonus_mountains = 0.2f;
      attack_on_bonus_marsh = -0.05f;
      attack_on_bonus_forest = 0.1f;

      attack_against_bonus_plains = 0.0f;
      attack_against_bonus_hills = -0.1f;
      attack_against_bonus_mountains = -0.2f;
      attack_against_bonus_marsh = 0.05f;
      attack_against_bonus_forest = -0.1f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.15f;
      defense_bonus_mountains = 0.3f;
      defense_bonus_marsh = 0.0f;
      defense_bonus_forest = 0.2f;

      attack_range = 1.0f;
      recon_range = 2.0f;
      bridge_damage = 0.0f;
      road_damage = 0.0f;
      break;
    case UnitType::kMechanizedInfantry:
      start_movement_points = 4.5f;
      start_health_points = 110.0f;

      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.1f;
      movement_cost_mountains = 2.5f;
      movement_cost_marsh = 1.2f;
      movement_cost_forest = 1.0f;

      attack_on_bonus_plains = 0.0f;
      attack_on_bonus_hills = 0.05f;
      attack_on_bonus_mountains = 0.1f;
      attack_on_bonus_marsh = 0.0f;
      attack_on_bonus_forest = 0.0f;

      attack_against_bonus_plains = 0.0f;
      attack_against_bonus_hills = -0.05f;
      attack_against_bonus_mountains = -0.1f;
      attack_against_bonus_marsh = 0.0f;
      attack_against_bonus_forest = 0.0f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.1f;
      defense_bonus_mountains = 0.2f;
      defense_bonus_marsh = 0.0f;
      defense_bonus_forest = 0.0f;

      attack_range = 2.0f;
      recon_range = 1.0f;
      bridge_damage = 0.1f;
      road_damage = 0.1f;
      break;
    case UnitType::kTank:
      start_movement_points = 4.0f;
      start_health_points = 150.0f;

      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.5f;
      movement_cost_mountains = 999.0f;
      movement_cost_marsh = 2.0f;
      movement_cost_forest = 2.0f;

      attack_on_bonus_plains = 0.1f;
      attack_on_bonus_hills = 0.05f;
      attack_on_bonus_mountains = 0.0f;
      attack_on_bonus_marsh = -0.1f;
      attack_on_bonus_forest = -0.1f;

      attack_against_bonus_plains = -0.1f;
      attack_against_bonus_hills = -0.05f;
      attack_against_bonus_mountains = 0.0f;
      attack_against_bonus_marsh = 0.1f;
      attack_against_bonus_forest = 0.1f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.1f;
      defense_bonus_mountains = 0.0f;
      defense_bonus_marsh = -0.15f;
      defense_bonus_forest = -0.15f;

      attack_range = 2.0f;
      recon_range = 1.0f;
      bridge_damage = 0.3f;
      road_damage = 0.2f;
      break;
    case UnitType::kTBM:
      start_movement_points = 3.0f;
      start_health_points = 70.0f;
      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.2f;
      movement_cost_mountains = 999.0f;
      movement_cost_marsh = 1.5f;
      movement_cost_forest = 1.3f;

      attack_on_bonus_plains = 0.2f;
      attack_on_bonus_hills = 0.1f;
      attack_on_bonus_mountains = 0.0f;
      attack_on_bonus_marsh = -0.05f;
      attack_on_bonus_forest = -0.05f;

      attack_against_bonus_plains = -0.2f;
      attack_against_bonus_hills = -0.1f;
      attack_against_bonus_mountains = 0.0f;
      attack_against_bonus_marsh = 0.05f;
      attack_against_bonus_forest = 0.05f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.05f;
      defense_bonus_mountains = 0.0f;
      defense_bonus_marsh = -0.1f;
      defense_bonus_forest = -0.1f;

      attack_range = 4.0f;
      recon_range = 1.0f;
      bridge_damage = 0.2f;
      road_damage = 0.1f;
      break;
    case UnitType::kUCAV:
      start_movement_points = 2.0f;
      start_health_points = 60.0f;
      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.0f;
      movement_cost_mountains = 1.0f;
      movement_cost_marsh = 1.0f;
      movement_cost_forest = 1.0f;

      attack_on_bonus_plains = 0.1f;
      attack_on_bonus_hills = 0.1f;
      attack_on_bonus_mountains = 0.1f;
      attack_on_bonus_marsh = 0.1f;
      attack_on_bonus_forest = 0.1f;

      attack_against_bonus_plains = -0.1f;
      attack_against_bonus_hills = -0.1f;
      attack_against_bonus_mountains = -0.1f;
      attack_against_bonus_marsh = -0.1f;
      attack_against_bonus_forest = -0.1f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.0f;
      defense_bonus_mountains = 0.0f;
      defense_bonus_marsh = 0.0f;
      defense_bonus_forest = 0.0f;

      attack_range = 6.0f;
      recon_range = 6.0f;
      bridge_damage = 0.0f;
      road_damage = 0.0f;
      break;
    default:
      start_movement_points = 2.0f;
      start_health_points = 60.0f;
      movement_cost_plains = 1.0f;
      movement_cost_hills = 1.0f;
      movement_cost_mountains = 1.0f;
      movement_cost_marsh = 1.0f;
      movement_cost_forest = 1.0f;

      attack_on_bonus_plains = 0.1f;
      attack_on_bonus_hills = 0.1f;
      attack_on_bonus_mountains = 0.1f;
      attack_on_bonus_marsh = 0.1f;
      attack_on_bonus_forest = 0.1f;

      attack_against_bonus_plains = -0.1f;
      attack_against_bonus_hills = -0.1f;
      attack_against_bonus_mountains = -0.1f;
      attack_against_bonus_marsh = -0.1f;
      attack_against_bonus_forest = -0.1f;

      defense_bonus_plains = 0.0f;
      defense_bonus_hills = 0.0f;
      defense_bonus_mountains = 0.0f;
      defense_bonus_marsh = 0.0f;
      defense_bonus_forest = 0.0f;

      attack_range = 6.0f;
      recon_range = 1.0f;
      bridge_damage = 0.0f;
      road_damage = 0.0f;
      break;
  }
}

void Unit::ResetMovementPoints() {
  movement_points_ = unit_modifiers_->start_movement_points;
}

std::string UnitManager::GetName(UnitType unit_type) const {
  switch (unit_type) {
    case UnitType::kAntiTank: return "Anti-Tank";
    case UnitType::kArtillery: return "Artillery";
    case UnitType::kInfantry: return "Infantry";
    case UnitType::kMechanizedInfantry: return "Mechanized Infantry";
    case UnitType::kTank: return "Tank";
    case UnitType::kTBM: return "Tactical Ballistic Missile";
    case UnitType::kUCAV: return "UCAV";
    default: return "";
  }
}

std::string UnitManager::GetTextureName(UnitType unit_type) const {
  switch (unit_type) {
    case UnitType::kAntiTank: return "units/at/at";
    case UnitType::kArtillery: return "units/artillery/artillery";
    case UnitType::kInfantry: return "units/infantry/infantry";
    case UnitType::kMechanizedInfantry: return "units/mechinf/mechinf";
    case UnitType::kTank: return "units/tank/tank";
    case UnitType::kTBM: return "units/tbm/tbm";
    case UnitType::kUCAV: return "units/ucav/ucav";
    default: return "";
  }
}

} // namespace fow