#include "complex_drawable.h"

#include <iostream>

#include "text.h"

namespace fow {
	ComplexDrawable::ComplexDrawable(std::initializer_list<ComplexDrawablePart> parts) {
		for (const auto& part : parts) {
			parts_[part.name] = part.drawable;
		}
	}

	void ComplexDrawable::EditText(std::string&& name, std::string&& new_text) {
		try {
			std::shared_ptr<Text> text = std::dynamic_pointer_cast<Text>(parts_.at(name));
			if (!text) {
				throw std::runtime_error("EditText: part \"" + name + "\" is not a Text object");
			}
			text->ChangeText(std::move(new_text));
		}
		catch (const std::out_of_range& e) {
			std::cerr << "EditText: part \"" << name << "\" not found (std::out_of_range)\n";
		}
		catch (const std::exception& e) {
			std::cerr << "EditText error: " << e.what() << "\n";
		}
	}

	std::vector<std::shared_ptr<Drawable>>& ComplexDrawable::GetDrawables() {
		drawables_.clear();
		for (auto& part : parts_) {
			drawables_.push_back(part.second);
		}
		return drawables_;
	}
}