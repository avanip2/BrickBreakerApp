#include "display_screen.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;

  AddBricksToDisplay(kBrickSize);
  CheckOverlappingBricks();
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
  for (size_t brick = 0; brick < kNumberOfBricksPerRow; brick++) {
    size_t x_position = GenerateRandomNumber(display_top_left_position_.x, display_bottom_right_position_.x - kBrickSize);
    size_t num_hits = GenerateRandomNumber(kMinNumberOfHits, kMaxNumberOfHits);
    Brick new_brick(num_hits, vec2{x_position, y_position},
                    vec2{x_position + kBrickSize, y_position + kBrickSize},
                    ci::Color("blue"));
    bricks.push_back(new_brick);
    brick_rows_.push_back(bricks);
  }
}

void DisplayScreen::RemoveBrickFromDisplay(Brick &brick_to_remove) {
  brick_to_remove.SetColor(ci::Color("black"));
}

size_t DisplayScreen::GenerateRandomNumber(size_t min, size_t max) {
  size_t randomly_generated_number = ((rand() % (max - min + 1)) + min);
  return randomly_generated_number;
}

void DisplayScreen::CheckOverlappingBricks() {
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    for (size_t brick = 0; brick < brick_rows_[row].size() - 1; brick++) {
      if (brick_rows_[row][brick].GetTopLeftPosition().x == brick_rows_[row][brick + 1].GetTopLeftPosition().x) {
        size_t new_x_position = GenerateRandomNumber(display_top_left_position_.x, display_bottom_right_position_.x - kBrickSize);
        brick_rows_[row][brick].SetTopLeftPosition(vec2{new_x_position, brick_rows_[row][brick].GetTopLeftPosition().y});
        brick_rows_[row][brick].SetBottomRightPosition(vec2{new_x_position + kBrickSize, brick_rows_[row][brick].GetTopLeftPosition().y + kBrickSize});
      }
    }
  }
}

} //namespace brickbreaker