#pragma once

#include "../target.h"
#include "../../../drawable/button/texture_button.h"
#include "../../../drawable/texture_manager.h"

namespace fow {

    enum class UnitType {
        kAntiTank,
        kArtillery,
        kElectronicWarfare,
        kInfantry,
        kMechanizedInfantry,
        kTank,
        kTBM,
        kUCAV
    };

    struct UnitModifiers {
        UnitModifiers(UnitType unit_type);

        float start_movement_points;
        float start_health_points;

        float movement_cost_plains;
        float movement_cost_hills;
        float movement_cost_mountains;
        float movement_cost_marsh;
        float movement_cost_forest;

        float attack_on_bonus_plains;
        float attack_on_bonus_hills;
        float attack_on_bonus_mountains;
        float attack_on_bonus_marsh;
        float attack_on_bonus_forest;

        float attack_against_bonus_plains;
        float attack_against_bonus_hills;
        float attack_against_bonus_mountains;
        float attack_against_bonus_marsh;
        float attack_against_bonus_forest;

        float defense_bonus_plains;
        float defense_bonus_hills;
        float defense_bonus_mountains;
        float defense_bonus_marsh;
        float defense_bonus_forest;

        float attack_range;
        float sight_range;

        float bridge_damage;
        float road_damage;
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
    private:
        
        UnitType unit_type_;

        std::shared_ptr<UnitModifiers> unit_modifiers_;

        float movement_points_;
        float health_points_;
    };  

    class UnitManager : public TextureManager<UnitType, UnitModifiers>{
    public: 
        std::string GetName(UnitType unit_type) const override;
    private:
        std::string GetTextureName(UnitType unit_type) const override;
    };

}