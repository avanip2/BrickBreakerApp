#pragma once

#include "cinder/gl/gl.h"
#include "cinder/audio/OutputNode.h"
#include "brick.h"
#include "ball.h"
#include "paddle.h"

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
 * determine if a collision with the entered brick and ball has occurred and update velocities and hits
 * @param ball display ball
 * @param brick specific brick in the row
 */
  void UpdateForBrickCollision(Ball &ball, Brick &brick);

  /**
   * determine if a collision between the ball and the wall has occurred
   * @param ball display ball
   */
  void UpdateForBallCollisionWithWall(Ball &ball);

  /**
   * determine if a collision between the ball and the paddle has occurred
   * @param ball the ball in the display
   * @param paddle the paddle in the display
   */
  void UpdateForPaddleCollision(Ball &ball, Paddle &paddle);

  Paddle paddle_;

  Ball ball_;

  size_t GetNumLives() const;

  bool is_brick_collision_;

  bool is_paddle_collision_;

 private:
  //member variables of display
  vec2 display_top_left_position_;
  vec2 display_bottom_right_position_;
  std::vector<std::vector<Brick>> brick_rows_;
  size_t num_lives_;
  bool has_game_ended_;
  int calls_to_advance_;

  //constants for drawing and randomizing objects in the display
  constexpr static size_t kNumberOfBricksPerRow = 9;
  constexpr static size_t kMinNumberOfHits = 1;
  constexpr static size_t kMaxNumberOfHits = 10;
  constexpr static size_t kMinBrickSize = 50;
  constexpr static size_t kMaxBrickSize = 100;
  constexpr static size_t kBrickMargin = 2;
  constexpr static size_t kBallSize = 10;
  constexpr static size_t kPaddleLocation = 400;
  constexpr static size_t kPaddleSize = 20;
  constexpr static size_t kPaddleLength = 150;

  /**
 * helper method to create and add bricks to the display
 */
  void AddBricksToDisplay(size_t y_position);

  void UpdateBrickPositions();

};
} //namespace brickbreaker