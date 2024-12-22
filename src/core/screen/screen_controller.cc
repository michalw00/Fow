#include "screen_controller.h"

#include "menu_screen.h"

namespace fow {
	ScreenController::ScreenController(ScreenType start_screen_type) {
		current_screen_ = CreateScreen(start_screen_type);
		current_screen_->Init();
	}

	void ScreenController::DrawScreen(RWindow& window) {
		window.BeginDrawing();
		window.ClearBackground(RColor{255,0,0});

		current_screen_->Draw();
		window.EndDrawing();
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