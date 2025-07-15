#include "window.h"

#include <memory>
#include <optional>
#include <vector>

#include <Color.hpp>
#include <Text.hpp>
#include <Vector2.hpp>

#include "../drawable/button/text_button.h"
#include "../drawable/drawable.h"
#include "../drawable/rectangle.h"
#include "../drawable/text.h"

namespace fow {

Window::Window(RVector2 pos, RVector2 size) {
	InitWindow(pos, size, std::nullopt);
}

Window::Window(RVector2 position, RVector2 size, const RText& text) {
	InitWindow(position, size, text);
}

void Window::InitWindow(RVector2 pos, RVector2 size,
	const std::optional<RText>& text) {
	RColor background_color = RColor::Black().Alpha(0.875f);
	std::shared_ptr<Rectangle> background = std::make_shared<Rectangle>(pos, size, background_color);
	drawables_.push_back(background);

	if (text) {
		std::shared_ptr<Text> window_text =
			std::make_shared<Text>(pos + size / 2.f, *text, true);
		drawables_.push_back(window_text);
	}

	RVector2 close_pos = pos + RVector2(size.GetX() - 30.f, 5.f);
	RText close_text("x", 40.f);
	close_button_ = std::make_shared<TextButton>(close_pos, [this]() { should_close_ = true; }, close_text, false);
	drawables_.push_back(close_button_);
}

std::vector<std::shared_ptr<Drawable>>& Window::GetDrawables() {
	return drawables_;
}

} // namespace fow