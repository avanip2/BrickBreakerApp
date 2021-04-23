#pragma once

#include <cinder/Timer.h>
#include "cinder/gl/gl.h"
#include "brick.h"
#include "ball.h"

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
   * advance the frame for collisions with ball
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
  //member variables of display
  vec2 display_top_left_position_;
  vec2 display_bottom_right_position_;
  cinder::Timer timer_;
  std::vector<std::vector<Brick>> brick_rows_;
  Ball ball_;

  //constants for drawing and randomizing objects in the display
  constexpr static size_t kNumberOfBricksPerRow = 8;
  constexpr static size_t kMinNumberOfHits = 1;
  constexpr static size_t kMaxNumberOfHits = 10;
  constexpr static size_t kMinBrickSize = 50;
  constexpr static size_t kMaxBrickSize = 100;
  constexpr static size_t kBrickMargin = 10;

  /**
   * helper method to create and add bricks to the display
   */
  void AddBricksToDisplay(size_t y_position);

  /**
   * helper method to remove bricks from the display(unimplemented)
   * @param brick_to_remove brick to remove
   */
  void RemoveBrickFromDisplay(Brick &brick_to_remove);
};
} //namespace brickbreaker