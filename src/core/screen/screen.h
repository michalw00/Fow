#pragma once

#include <memory>
#include <vector>

#include <Camera2D.hpp>

#include "../../drawable/button/button.h"
#include "../../drawable/drawable.h"

namespace fow {

enum class ScreenType {
  kMenu,
  kMatch
};

class Screen {
public:
  Screen(std::shared_ptr<RCamera2D> camera) : camera_(camera) {}
  virtual ~Screen() {};

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual ScreenType Finish() = 0;

  void Clear();
  void Draw() const;
  void CheckButtons();
  void ScalePositions(float window_width, float window_height, bool inverse = false);

  bool ShouldClose() const { return should_close_; }
  bool ShouldFinish() const { return should_finish_; }
protected:
  void PlaceDrawable(std::shared_ptr<Drawable> drawable, bool is_static = false);

  std::shared_ptr<RCamera2D> camera_;

  bool should_close_ = false;
  bool should_finish_ = false;

  float basic_width_ = 1600.f;
  float basic_height_ = 900.f;

private:  
  std::vector<std::shared_ptr<Drawable>> drawables_;
  std::vector<std::shared_ptr<Button>> buttons_;

  std::vector<std::shared_ptr<Drawable>> drawables_static_;
  std::vector<std::shared_ptr<Button>> buttons_static_;
};

} // namespace fow
