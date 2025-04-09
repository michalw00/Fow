#pragma once
#include <Texture.hpp>
#include <memory>
#include <unordered_map>

namespace fow {

    struct TextureState {
        TextureState(std::shared_ptr<RTexture> basic = nullptr,
            std::shared_ptr<RTexture> hovered = nullptr,
            std::shared_ptr<RTexture> fow = nullptr)
            : basic(basic), hovered(hovered), fow(fow) {}

        std::shared_ptr<RTexture> basic;
        std::shared_ptr<RTexture> hovered;
        std::shared_ptr<RTexture> fow;
    };

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
                std::make_shared<RTexture>(base_name + hovered_suffix + format_suffix)
                //std::make_shared<RTexture>(base_name + fow_suffix + format_suffix)
            );
            textures_.emplace(key, texture);
            return texture;
        }

    private:
        virtual std::string GetTextureName(KeyType key) const = 0;

        std::string texture_path = "assets/";
        std::string format_suffix = ".png";
        std::string hovered_suffix = "_hovered";
        std::string fow_suffix = "_fow";

        mutable std::unordered_map<KeyType, std::shared_ptr<ValueType>> resources_;
        mutable std::unordered_map<KeyType, TextureState> textures_;
    };

}