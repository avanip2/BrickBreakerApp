#include "display_screen.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;

  AddBricksToDisplay(kMinBrickSize);
  ball_ = Ball(display_bottom_right_position_, vec2{1,1}, 10, ci::Color("red"));
}

void DisplayScreen::Display() const {
  //loop through the rows in the display
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    //loop through bricks in the row
    for (const Brick &brick : brick_rows_[row]) {
      //display each brick
      brick.DisplayBrick();
    }
  }

  //display the ball
  ball_.DisplayBall();
  ci::gl::color(ci::Color("White"));
  ci::gl::drawStrokedRect(ci::Rectf(display_top_left_position_, display_bottom_right_position_));
}

void DisplayScreen::AdvanceFrame() {
  //loop through the rows in the display
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    //loop through the bricks in the row
    for (Brick brick : brick_rows_[row]) {

      //check if the brick's bottom right y position has reached the container's bottom right y position
      if (brick.GetBottomRightPosition().y >= display_bottom_right_position_.y) {
        RemoveBrickFromDisplay(brick);
      }
    }
  }
}

void DisplayScreen::AddBricksToDisplay(size_t y_position) {
  //initialize a vector of bricks to add each brick to and an initial position to update in the loop
  std::vector<Brick> bricks;
  size_t current_brick_position = kMinBrickSize;

  //loop through the number of bricks
  for (size_t brick = 0; brick < kNumberOfBricksPerRow; brick++) {

    //generate random sizes and number of hits for a brick
    size_t brick_size = GenerateRandomNumber(kMinBrickSize, kMaxBrickSize);
    size_t num_hits = GenerateRandomNumber(kMinNumberOfHits, kMaxNumberOfHits);

    //create new brick using randomly generated attributes and the position of each brick
    Brick new_brick(num_hits, vec2{current_brick_position, y_position},
                    vec2{current_brick_position + brick_size, y_position + kMinBrickSize},
                    ci::Color("blue"), brick_size);

    //push brick to bricks vector and update current position for next brick's position
    bricks.push_back(new_brick);
    current_brick_position += brick_size + kBrickMargin;
  }

  //push row of bricks back to the row of bricks vector
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