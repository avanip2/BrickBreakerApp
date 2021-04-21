#include "display_screen.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;
}

size_t DisplayScreen::GenerateRandomNumber(size_t min, size_t max) {
  size_t randomly_generated_number = ((rand() & (max - min + 1)) + min);
  return randomly_generated_number;
}
} //namespace brickbreaker