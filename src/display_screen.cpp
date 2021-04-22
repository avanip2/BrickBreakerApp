#include "display_screen.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;
}

void DisplayScreen::AddBricksToDisplay(size_t y_position) {
  for (size_t brick = 0; brick < kNumberOfBricksPerRow; brick++) {
    size_t x_position = GenerateRandomNumber(display_top_left_position_.x, display_bottom_right_position_.x);
    size_t num_hits = GenerateRandomNumber(kMinNumberOfHits, kMaxNumberOfHits);
    Brick new_brick(num_hits, vec2{x_position, y_position},
                    vec2{x_position + kBrickSize, y_position + kBrickSize},
                    ci::Color(GenerateRandomNumber(kMinColor, kMaxColor), GenerateRandomNumber(kMinColor, kMaxColor),
                              GenerateRandomNumber(kMinColor, kMaxColor));
    bricks_.push_back(new_brick);
  }
}

size_t DisplayScreen::GenerateRandomNumber(size_t min, size_t max) {
  size_t randomly_generated_number = ((rand() & (max - min + 1)) + min);
  return randomly_generated_number;
}

} //namespace brickbreaker