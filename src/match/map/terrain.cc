#include "terrain.h"

namespace fow {
    Terrain::Terrain(TerrainType terrain_type, TerrainModifiers modifiers) : terrain_type_(terrain_type), modifiers_(modifiers) {}

    std::shared_ptr<Terrain> TerrainManager::InitTerrain(TerrainType terrain_type) {       
        TerrainModifiers modifiers{};
        
        switch (terrain_type) {
            case fow::TerrainType::kPlains: {         
                break;
            }
            case fow::TerrainType::kHills: {
                break;
            }
            case fow::TerrainType::kMountains: {
                break;
            }
            case fow::TerrainType::kMarsh: {
                break;
            }
            case fow::TerrainType::kForest: {
                break;
            }
            case fow::TerrainType::kWater:{
                modifiers.is_water = true;
                break;
            }
        }
        
        std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>(terrain_type, modifiers);

        terrains_.emplace(terrain_type, terrain);
        return terrain;
    }

    TextureStates TerrainManager::InitTexture(TerrainType terrain_type) {
        std::string file_name;

        switch (terrain_type) {
            case fow::TerrainType::kPlains: {
                file_name = "plain";
                break;
            }
            case fow::TerrainType::kHills: {
                file_name = "hills";
                break;
            }
            case fow::TerrainType::kMountains: {
                file_name = "mountains";
                break;
            }
            case fow::TerrainType::kMarsh: {
                file_name = "marsh";
                break;
            }
            case fow::TerrainType::kForest: {
                file_name = "forest";
                break;
            }
            case fow::TerrainType::kWater: {
                file_name = "water";
                break;
            }
        }
        TextureStates texture;

        std::string basic_file_name = texture_path + file_name;
        texture.basic = std::make_shared<RTexture>(basic_file_name + format_suffix);
        texture.hovered = std::make_shared<RTexture>(basic_file_name + hovered_suffix + format_suffix);
        // texture.fow = std::make_shared<RTexture>(basic_file_name + fow_suffix + format_suffix);

        textures_.emplace(terrain_type, texture);
        return texture;
    }

    std::shared_ptr<Terrain> TerrainManager::GetTerrain(TerrainType terrain_type) {

        auto it = terrains_.find(terrain_type);

        if (it != terrains_.end()) {
            return it->second;
        } else {
            return InitTerrain(terrain_type);
        }
    }

    TextureStates TerrainManager::GetTexture(TerrainType terrain_type) {
        auto it = textures_.find(terrain_type);

        if (it != textures_.end()) {
            return it->second;
        } else {
            return InitTexture(terrain_type);
        }
    }
}