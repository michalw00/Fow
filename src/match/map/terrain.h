#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <Texture.hpp>

#include "../../drawable/button/texture_button.h"

namespace fow {

    enum class TerrainType {
        kPlains,
        kHills,
        kMountains,
        kMarsh,
        kForest,
        kWater
    };

    struct TerrainModifiers {
        float movement_cost;
        float conceal;
        bool is_water = false;
    };

    class Terrain {
    public:      
        Terrain(TerrainType terrain_type, TerrainModifiers modifiers);  

        TerrainType GetType() const { return terrain_type_; }
    private:   
        TerrainType terrain_type_;
        TerrainModifiers modifiers_;  
    };

    class TerrainManager {
    public:
        std::shared_ptr<Terrain> GetTerrain(TerrainType terrain_type);
        TextureStates GetTexture(TerrainType terrain_type);
    private:

        std::string texture_path = "assets/";
        std::string format_suffix = ".png";
        std::string hovered_suffix = "_hovered";
        std::string fow_suffix = "_fow";

        std::shared_ptr<Terrain> InitTerrain(TerrainType terrain_type);
        TextureStates InitTexture(TerrainType terrain_type);

        std::unordered_map <TerrainType, std::shared_ptr<Terrain>> terrains_;
        std::unordered_map <TerrainType, TextureStates> textures_;
    };
}