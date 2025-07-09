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
      start_movement_points = 3.f;
      start_health_points = 100.f;
      bridge_damage = 0.1f;
      attack_range = 2;
      recon_range = 2;
      break;
    case UnitType::kArtillery:
      start_movement_points = 3.f;
      start_health_points = 70.f;
      bridge_damage = 0.2f;
      min_attack_range = 4;
      attack_range = 12;
      recon_range = 1;
      range_deviation = 2;
      direction_deviation = 1;
      hit_chances = { 
        0.02, 0.04, 0.08, 0.04, 0.02, 
        0.06, 0.12, 0.24, 0.12, 0.06,
        0.02, 0.04, 0.08, 0.04, 0.02
      };
      diag_hit_chances = {
        0.02, 0.08, 0.08, 0.02, 
         0.06, 0.12, 0.24, 0.12, 0.06,
        0.02, 0.08, 0.08, 0.02 };
      break;
    case UnitType::kEW:
      start_movement_points = 3.f;
      start_health_points = 85.f;
      attack_range = 1;
      recon_range = 2;
      break;
    case UnitType::kInfantry:
      start_movement_points = 3.0f;
      start_health_points = 100.0f;
      attack_range = 1;
      recon_range = 2;
      break;
    case UnitType::kMechanizedInfantry:
      start_movement_points = 8.f;
      start_health_points = 120.0f;
      attack_range = 1;
      recon_range = 2;
      is_vehicle = true;
      break;
    case UnitType::kTank:
      start_movement_points = 6.0f;
      start_health_points = 150.0f;
      attack_range = 2;
      recon_range = 1;
      bridge_damage = 0.2f;
      is_vehicle = true;
      break;
    case UnitType::kTBM:
      start_movement_points = 5.f;
      start_health_points = 70.0f;
      min_attack_range = 6;
      attack_range = 16;
      recon_range = 1;
      bridge_damage = 0.5f;
      is_vehicle = true;
      range_deviation = 1;
      direction_deviation = 0;
      hit_chances = { 0.15, 0.7, 0.15 };
      diag_hit_chances = hit_chances;
      break;
    case UnitType::kUCAV:
      start_movement_points = 3.f;
      start_health_points = 70.0f;
      min_attack_range = 1;
      attack_range = 8;
      recon_range = 8;
      bridge_damage = 0.2f;
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
    case UnitType::kEW: return "EW";
    case UnitType::kInfantry: return "Infantry";
    case UnitType::kMechanizedInfantry: return "Mech Inf";
    case UnitType::kTank: return "Tank";
    case UnitType::kTBM: return "MRL";
    case UnitType::kUCAV: return "UCAV";
    default: return "";
  }
}

std::string UnitManager::GetTextureName(UnitType unit_type) const {
  switch (unit_type) {
    case UnitType::kAntiTank: return "units/at/at";
    case UnitType::kArtillery: return "units/artillery/artillery";
    case UnitType::kEW: return "units/ew/ew";
    case UnitType::kInfantry: return "units/infantry/infantry";
    case UnitType::kMechanizedInfantry: return "units/mechinf/mechinf";
    case UnitType::kTank: return "units/tank/tank";
    case UnitType::kTBM: return "units/tbm/tbm";
    case UnitType::kUCAV: return "units/ucav/ucav";
    default: return "";
  }
}

} // namespace fow