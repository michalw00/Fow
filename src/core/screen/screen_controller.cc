#include "screen_controller.h"

#include "menu_screen.h"
#include "../../input/input.h"

namespace fow {

	ScreenController::ScreenController(ScreenType start_screen_type, RWindow& window) : window_(window) {
		current_screen_ = CreateScreen(start_screen_type);
		current_screen_->Init();

		RVector2 camera_offset = { window.GetWidth() / 2.f, window.GetHeight() / 2.f };
		RVector2 camera_target = { 0, 0 };
		camera_ = std::make_shared<RCamera2D>(camera_offset, camera_target);
	}

	void ScreenController::ProcessScreen() {

		Input inputs;
		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
			inputs.DragScreen(camera_.get());
		}
		float mouse_wheel = GetMouseWheelMove();
		if (std::abs(mouse_wheel) > 0.0f) {
			inputs.Zoom(camera_.get(), mouse_wheel * 0.05f, 0.1f, 2.f);
		}

		current_screen_->Update();
		current_screen_->ScaleTextsPositions(window_, 1600, 900);

		window_.BeginDrawing();
		camera_->BeginMode();

		window_.ClearBackground(RColor{});
		current_screen_->Draw();

		camera_->EndMode();
		window_.EndDrawing();
	}

    std::shared_ptr<Screen> ScreenController::CreateScreen(ScreenType screen_type) {
		switch (screen_type) {
			case ScreenType::kMenu: {
				return std::make_shared<MenuScreen>();
				break;
			}
			case ScreenType::kMatch: {
				break;
			}
			default: {
				break;
			}
		}
    }
}