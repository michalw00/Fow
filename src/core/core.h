#pragma once

#include <memory>

#include <Window.hpp>
#include <raylib.h>

#include "screen/screen_controller.h"

namespace fow {

class Core {
  public:
  static Core& Get();
  void Start();
  Core(Core const&) = delete;
  void operator=(Core const&) = delete;

  private:
  Core() {};

  TraceLogLevel log_level_ = TraceLogLevel::LOG_ALL;
  std::unique_ptr<RWindow> InitWindow(int width, int height, bool fullscreen);

  std::unique_ptr<ScreenController> screen_controller_;
};

} // namespace fow