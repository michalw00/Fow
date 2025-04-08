#pragma once

#include "../target.h"
#include "../../../drawable/button/texture_button.h"
#include "../../../drawable/texture_manager.h"
#include <unordered_map>

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
        Unit(int position_width, int position_height, UnitType unit_type) : Target(position_width, position_height), unit_type_(unit_type) {}

        void Attack(std::shared_ptr<Target> other);

        UnitType GetType() const { return unit_type_; }
    private:
        UnitType unit_type_;

        std::shared_ptr<UnitModifiers> unit_modifiers_;

        float movement_points_ = 0;
        float health_points_ = 0;
    };  

    class UnitManager : public TextureManager<UnitType, UnitModifiers>{
    private:
        std::string GetTextureName(UnitType unit_type) const override;
    };

}