#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../../drawable/texture_manager.h"
#include "../../../structs/vector2i.h"
#include "../target.h"

namespace fow {

enum class UnitType {
  kAntiTank,
  kArtillery,
  kEW,
  kInfantry,
  kMechanizedInfantry,
  kTank,
  kTBM,
  kUCAV
};

enum class UnitAction {
  kMove,
  kRecon,
  kAttack,
  kReinforce
};

struct UnitModifiers {
  UnitModifiers(UnitType unit_type);

  float start_movement_points = 0.f;
  float start_health_points = 0.f;
  float bridge_damage = 0.f;
  int min_attack_range = 0;
  int attack_range = 0;
  int recon_range = 0;
  bool is_vehicle = false;
  int range_deviation = 0;
  int direction_deviation = 0;
  std::vector<double> hit_chances;
  std::vector<double> diag_hit_chances;
};

class Unit : public Target {
  public:
  Unit(Vector2I position, UnitType unit_type, std::shared_ptr<UnitModifiers> unit_modifiers)
    : Target(position), unit_type_(unit_type), unit_modifiers_(unit_modifiers),
    movement_points_(unit_modifiers->start_movement_points), health_points_(unit_modifiers->start_health_points) {}

  void Attack(std::shared_ptr<Target> other);
  void ResetMovementPoints();
  void SubstractMovementPoints(float movement_points) { movement_points_ -= movement_points; };
  float GetMovementPoints() const { return movement_points_; }
  float GetHealthPoints() const { return health_points_; }

  UnitType GetType() const { return unit_type_; }
  const std::shared_ptr<UnitModifiers> GetUnitModifiers() const { return unit_modifiers_; }
  private:
  UnitType unit_type_;
  std::shared_ptr<UnitModifiers> unit_modifiers_;

  float movement_points_;
  float health_points_;
};

class UnitManager : public TextureManager<UnitType, UnitModifiers> {
  public:
  std::string GetName(UnitType unit_type) const override;
  private:
  std::string GetTextureName(UnitType unit_type) const override;
};

} // namespace fow