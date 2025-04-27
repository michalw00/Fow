#pragma once

namespace fow {

struct TextureState {
    TextureState(std::shared_ptr<RTexture> basic = nullptr,
        std::shared_ptr<RTexture> hovered = nullptr,
        std::shared_ptr<RTexture> selected = nullptr)
        : basic(basic), hovered(hovered), selected(selected) {
        basic->SetFilter(TextureFilter::TEXTURE_FILTER_ANISOTROPIC_16X);
        hovered->SetFilter(TextureFilter::TEXTURE_FILTER_ANISOTROPIC_16X);
        selected->SetFilter(TextureFilter::TEXTURE_FILTER_ANISOTROPIC_16X);
    }

    std::shared_ptr<RTexture> basic;
    std::shared_ptr<RTexture> hovered;
    std::shared_ptr<RTexture> selected;
};

}