#include "screen_controller.h"

#include "../../menu/menu_screen.h"
#include "../../input/input.h"
#include "../../match/match_screen.h"

namespace fow {

	ScreenController::ScreenController(ScreenType start_screen_type, std::unique_ptr<RWindow> window) : window_(std::move(window)) {
		current_screen_ = CreateScreen(start_screen_type);
		current_screen_->Init();

		RVector2 camera_offset = { window_->GetWidth() / 2.f, window_->GetHeight() / 2.f };
		RVector2 camera_target = { 0, 0 };
		camera_ = std::make_shared<RCamera2D>(camera_offset, camera_target);
	}

	void ScreenController::ProcessScreen() {
		
		while (!window_->ShouldClose() && !current_screen_->ShouldClose() ) {
			Input inputs;
			if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
				inputs.DragScreen(camera_.get());
			}
			float mouse_wheel = GetMouseWheelMove();
			if (std::abs(mouse_wheel) > 0.0f) {
				inputs.Zoom(camera_.get(), mouse_wheel * 0.05f, 0.5f, 2.f);
			}
		
			current_screen_->ScalePositions(window_->GetWidth(), window_->GetHeight(), 1600, 900);
			current_screen_->CheckButtons(*camera_);
			
			current_screen_->Update();

			window_->BeginDrawing();

			window_->ClearBackground(RColor{});
			current_screen_->Draw(*camera_);

			window_->EndDrawing();

			if (current_screen_->ShouldFinish()) {
				ScreenType new_screen_type = current_screen_->Finish();
				current_screen_ = CreateScreen(new_screen_type);
				current_screen_->Init();
			}
		}
		window_->Close();
	}

    std::shared_ptr<Screen> ScreenController::CreateScreen(ScreenType screen_type) {
		switch (screen_type) {
			case ScreenType::kMenu: {
				return std::make_shared<MenuScreen>();
				break;
			}
			case ScreenType::kMatch: {
				return std::make_shared<MatchScreen>();
				break;
			}
		}
    }
}