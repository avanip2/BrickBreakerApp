#include "display_screen.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;

  AddBricksToDisplay(kMinBrickSize);
}

void DisplayScreen::Display() const {
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    for (Brick brick : brick_rows_[row]) {
      brick.DisplayBrick();
    }
  }

  ci::gl::color(ci::Color("White"));
  ci::gl::drawStrokedRect(ci::Rectf(display_top_left_position_, display_bottom_right_position_));
}

void DisplayScreen::AdvanceFrame() {
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    for (Brick brick : brick_rows_[row]) {
      if (brick.GetBottomRightPosition().y >= display_bottom_right_position_.y) {
        RemoveBrickFromDisplay(brick);
      }
    }
  }
}

void DisplayScreen::AddBricksToDisplay(size_t y_position) {
  std::vector<Brick> bricks;
  size_t current_brick_position = kMinBrickSize;
  for (size_t brick = 0; brick < kNumberOfBricksPerRow; brick++) {
    size_t brick_size = GenerateRandomNumber(kMinBrickSize, kMaxBrickSize);
    size_t num_hits = GenerateRandomNumber(kMinNumberOfHits, kMaxNumberOfHits);
    Brick new_brick(num_hits, vec2{current_brick_position, y_position},
                    vec2{current_brick_position + brick_size, y_position + kMinBrickSize},
                    ci::Color("blue"), brick_size);
    bricks.push_back(new_brick);
    current_brick_position += brick_size + kBrickMargin;
  }
  brick_rows_.push_back(bricks);
}

void DisplayScreen::RemoveBrickFromDisplay(Brick &brick_to_remove) {
  brick_to_remove.SetColor(ci::Color("black"));
}

size_t DisplayScreen::GenerateRandomNumber(size_t min, size_t max) {
  size_t randomly_generated_number = ((rand() % (max - min + 1)) + min);
  return randomly_generated_number;
}

} //namespace brickbreaker