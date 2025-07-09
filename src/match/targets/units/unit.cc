#include "unit.h"

#include <memory>
#include <string>
#include <utility>

#include "../../map/map.h"
#include "../../map/tile.h"
#include "../target.h"

namespace fow {

void Unit::Attack(std::shared_ptr<Target> other, const std::unique_ptr<Map>& map) {
  // auto other_unit = std::dynamic_pointer_cast<Unit>(other); // Uncomment when bridge would be added
  /*if (!other_unit) {
    return;
  }*/
  auto other_unit = std::static_pointer_cast<Unit>(other);
  
  const auto& modifiers = unit_modifiers_;
  const auto& other_modifiers = other_unit->unit_modifiers_;
  const auto& tiles = map->GetTiles();
  const Tile& tile = tiles[position_.x][position_.y];
  const Tile& other_tile = tiles[other_unit->position_.x][other_unit->position_.y];

  const float base_damage = 100.f;
  const float initiative_bonus = 0.2f;
  const float min_damage = 0.1f;
  float attacker_power = initiative_bonus + tile.GetTerrain()->GetModifiers().attack_bonus;
  if (other_modifiers->is_vehicle) {
    attacker_power += modifiers->hard_attack;
  } else {
    attacker_power += modifiers->soft_attack;
  }
  float defender_power = other_tile.GetTerrain()->GetModifiers().defense_bonus;
  if (modifiers->is_vehicle) {
    defender_power += other_modifiers->hard_defense;
  } else {
    defender_power += other_modifiers->soft_defense;
  }
  float provided_damage = base_damage * (attacker_power - defender_power);
  provided_damage = std::max(min_damage, provided_damage);
  other_unit->health_points_ -= provided_damage;
  if (modifiers->attack_range >= 5) {
    return; // Can't counterattack
  }

  attacker_power = other_tile.GetTerrain()->GetModifiers().attack_bonus;
  if (other_modifiers->is_vehicle) {
    attacker_power += other_modifiers->hard_defense; // Not attack because it is close range combat
  } else {
    attacker_power += other_modifiers->soft_defense; // Same
  }
  defender_power = tile.GetTerrain()->GetModifiers().defense_bonus;
  if (modifiers->is_vehicle) {
    defender_power += modifiers->hard_defense;
  } else {
    defender_power += modifiers->soft_defense;
  }

  provided_damage = base_damage * (attacker_power - defender_power);
  provided_damage = std::max(min_damage, provided_damage);
  health_points_ -= provided_damage;
}

UnitModifiers::UnitModifiers(UnitType unit_type) {
  switch (unit_type) {
    case UnitType::kAntiTank:
      start_movement_points = 3.f;
      start_health_points = 100.f;
      bridge_damage = 0.1f;
      soft_attack = 0.2f;
      hard_attack = 1.f;
      soft_defense = soft_attack;
      hard_defense = hard_attack;
      attack_range = 2;
      recon_range = 2;
      break;
    case UnitType::kArtillery:
      start_movement_points = 3.f;
      start_health_points = 70.f;
      bridge_damage = 0.2f;
      soft_attack = 0.5f;
      hard_attack = 0.5f;
      soft_defense = 0.2f;
      hard_defense = 0.f;
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
      soft_attack = 0.2f;
      hard_attack = 0.1f;
      soft_defense = soft_attack;
      hard_defense = hard_attack;
      attack_range = 1;
      recon_range = 2;
      break;
    case UnitType::kInfantry:
      start_movement_points = 3.0f;
      start_health_points = 100.0f;
      soft_attack = 0.3f;
      hard_attack = 0.2f;
      soft_defense = soft_attack;
      hard_defense = hard_attack;
      attack_range = 1;
      recon_range = 2;
      break;
    case UnitType::kMechanizedInfantry:
      start_movement_points = 8.f;
      start_health_points = 120.0f;
      soft_attack = 0.5f;
      hard_attack = 0.4f;
      soft_defense = soft_attack;
      hard_defense = hard_attack;
      attack_range = 1;
      recon_range = 2;
      is_vehicle = true;
      break;
    case UnitType::kTank:
      start_movement_points = 6.0f;
      start_health_points = 150.0f;
      bridge_damage = 0.2f;
      soft_attack = 0.8f;
      hard_attack = 0.8f;
      soft_defense = soft_attack;
      hard_defense = hard_attack;
      attack_range = 2;
      recon_range = 1;
      is_vehicle = true;
      break;
    case UnitType::kTBM:
      start_movement_points = 5.f;
      start_health_points = 70.0f;
      min_attack_range = 6;
      attack_range = 16;
      recon_range = 1;
      bridge_damage = 0.5f;
      soft_attack = 0.9f;
      hard_attack = 0.9f;
      soft_defense = 0.3f;
      hard_defense = 0.2f;
      is_vehicle = true;
      range_deviation = 1;
      direction_deviation = 0;
      hit_chances = { 0.15, 0.7, 0.15 };
      diag_hit_chances = hit_chances;
      break;
    case UnitType::kUCAV:
      start_movement_points = 3.f;
      start_health_points = 70.0f;
      bridge_damage = 0.2f;
      soft_attack = 0.7f;
      hard_attack = 0.4f;
      soft_defense = 0.2f;
      hard_defense = 0.1f;
      min_attack_range = 1;
      attack_range = 8;
      recon_range = 8;
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