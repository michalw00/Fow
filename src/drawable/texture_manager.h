#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <Texture.hpp>

#include "../structs/texture_states.h"

namespace fow {

template <typename KeyType, typename ValueType>
class TextureManager {
  public:
  virtual ~TextureManager() {};

  std::shared_ptr<ValueType> GetResource(KeyType key) const {
    auto it = resources_.find(key);

    if (it != resources_.end()) {
      return it->second;
    } else {
      return InitResource(key);
    }
  }

  TextureState GetTexture(KeyType key) const {
    auto it = textures_.find(key);

    if (it != textures_.end()) {
      return it->second;
    } else {
      return InitTexture(key);
    }
  }

  virtual std::string GetName(KeyType key) const = 0;

  protected:
  std::shared_ptr<ValueType> InitResource(KeyType key) const {
    std::shared_ptr<ValueType> resource = std::make_shared<ValueType>(key);
    resources_.emplace(key, resource);
    return resource;
  }

  TextureState InitTexture(KeyType key) const {
    auto base_name = texture_path + GetTextureName(key);
    auto texture = TextureState(
        std::make_shared<RTexture>(base_name + format_suffix),
        std::make_shared<RTexture>(base_name + hovered_suffix + format_suffix),
        std::make_shared<RTexture>(base_name + selected_suffix + format_suffix)
    );
    textures_.emplace(key, texture);
    return texture;
  }

  private:
  virtual std::string GetTextureName(KeyType key) const = 0;

  std::string texture_path = "assets/";
  std::string format_suffix = ".png";
  std::string hovered_suffix = "_hovered";
  std::string selected_suffix = "_selected";

  mutable std::unordered_map<KeyType, std::shared_ptr<ValueType>> resources_;
  mutable std::unordered_map<KeyType, TextureState> textures_;
};

} // namespace fow