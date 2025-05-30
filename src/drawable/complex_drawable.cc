#include "complex_drawable.h"

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "drawable.h"
#include "text.h"

namespace fow {

ComplexDrawable::ComplexDrawable(std::initializer_list<ComplexDrawablePart> parts) {
  for (const auto& part : parts) {
    parts_[part.name] = part.drawable;
  }
}

void ComplexDrawable::EditText(std::string&& name, std::string&& new_text) {
  std::shared_ptr<Text> text = std::dynamic_pointer_cast<Text>(parts_.at(name));

  if (!text) {
    throw std::runtime_error("EditText: part \"" + name + "\" is not a Text object");
  }

  text->ChangeText(std::move(new_text));
}

std::vector<std::shared_ptr<Drawable>>& ComplexDrawable::GetDrawables() {
  drawables_.clear();
  for (auto& part : parts_) {
    drawables_.push_back(part.second);
  }
  return drawables_;
}

} // namespace fow