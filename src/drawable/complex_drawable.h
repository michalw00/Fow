#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "drawable.h"

namespace fow {

struct ComplexDrawablePart {
  std::string name;
  std::shared_ptr<Drawable> drawable;
};

class ComplexDrawable {
  public:
  ComplexDrawable(std::initializer_list<ComplexDrawablePart> parts);
  void EditText(std::string&& name, std::string&& new_text);

  std::vector<std::shared_ptr<Drawable>>& GetDrawables();
  private:
  std::unordered_map<std::string, std::shared_ptr<Drawable>> parts_;
  std::vector <std::shared_ptr<Drawable>> drawables_;
};

} // namespace fow