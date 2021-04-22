#pragma once

#include "cinder/gl/gl.h"
#include "brick.h"

using glm::vec2;

namespace brickbreaker {

/**
 * class to display parts of the game on the screen
 */
class DisplayScreen {

 public:

  DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position);

  /**
   * draw all elements on the screen
   */
  void Display() const;

  /**
   * advance the frame for collisions with ball(unimplemented till week 2)
   */
  void AdvanceFrame();

  /**
   * helper method to calculate a random number
   * @param min lower bound
   * @param max upper bound
   * @return the random number
   */
  size_t GenerateRandomNumber(size_t min, size_t max);
 private:
  vec2 display_top_left_position_;
  vec2 display_bottom_right_position_;

  std::vector<std::vector<Brick>> brick_rows_;

  constexpr static size_t kNumberOfBricksPerRow = 5;
  constexpr static size_t kMinNumberOfHits = 1;
  constexpr static size_t kMaxNumberOfHits = 10;
  constexpr static size_t kBrickSize = 50;
  constexpr static size_t kMinColor = 0;
  constexpr static size_t kMaxColor = 255;

  /**
   * helper method to create and add bricks to the display
   */
  void AddBricksToDisplay(size_t y_position);

  void RemoveBrickFromDisplay(Brick &brick_to_remove);
};
}