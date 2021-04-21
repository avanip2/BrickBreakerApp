#pragma once

#include "cinder/gl/gl.h"
#include "brick.h"

using glm::vec2;

namespace brickbreaker {

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

  std::vector<Brick> bricks_;

  constexpr static size_t kNumberOfBricksPerRow = 5;

  /**
   * helper method to create and add bricks to the display
   */
  void AddBricksToDisplay();
};
}