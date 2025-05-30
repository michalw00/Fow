#pragma once

#include <iterator>
#include <unordered_set>
#include <vector>

namespace fow {

template <typename T>
std::unordered_set<T> SetIntersection(const std::vector<std::unordered_set<T>>& sets) {
  std::unordered_set<T> intersection;

  if (sets.empty()) {
    return intersection;
  }

  std::unordered_set<T> first_set = sets[0];

  for (const T& element : first_set) {
    bool present_in_all = true;
    for (size_t i = 1; i < sets.size(); ++i) {
      if (sets[i].find(element) == sets[i].end()) {
        present_in_all = false;
        break;
      }
    }
    if (present_in_all) {
      intersection.insert(element);
    }
  }

  return intersection;
}

template <typename T>
std::unordered_set<T> SetDifference(const std::vector<std::unordered_set<T>>& sets) {
  if (sets.empty()) {
    return {};
  }

  std::unordered_set<T> difference = sets[0];

  for (size_t i = 1; i < sets.size(); ++i) {
    std::unordered_set<T> temp_difference;
    for (const T& element : difference) {
      if (sets[i].find(element) == sets[i].end()) {
        temp_difference.insert(element);
      }
    }
    difference = temp_difference;
  }
  return difference;
}

template <typename T>
std::unordered_set<T> SetDifference(const std::unordered_set<T>& set1, const std::unordered_set<T>& set2) {
  std::unordered_set<T> difference;

  std::copy_if(set1.begin(), set1.end(), std::inserter(difference, difference.begin()),
      [&](const T& element) { return set2.find(element) == set2.end(); });

  return difference;
}

} // namespace fow