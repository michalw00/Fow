#pragma once

#include <functional>

#include <Text.hpp>
#include <Vector2.hpp>

#include "button.h"

namespace fow {
struct TextStates {
  TextStates(const RText& text, int hovered_size_increase = 3, int hovered_alpha_decrease = 30);

  RText basic;
  RText hovered;
};

class TextButton : public Button {
  public:
  TextButton(RVector2 position, std::function<void()> action_lmb, const RText& text, bool centered = true, std::function<void()> action_rmb = []() {});

  void Draw() const override;
  void Scale(RVector2 scale) override;
  private:
  TextStates text_;
};

} // namespace fow