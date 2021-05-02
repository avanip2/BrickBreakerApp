#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

class Paddle {
 public:
  Paddle(vec2 set_paddle_top_left, vec2 set_paddle_bottom_right, ci::Color set_color);
  Paddle();

  /**
   * helper method to display the paddle using its attributes in the class
   */
  void DisplayPaddle() const;

  /**
   * helper method to move the paddle when the key events call it
   */
  void MovePaddle();

  //setters and getters
  void SetPaddleTopLeft(vec2 set_paddle_top_left);

  vec2 GetPaddleTopLeft();

  void SetPaddleBottomRight(vec2 set_paddle_bottom_right);

  vec2 GetPaddleBottomRight();

  void SetColor(ci::Color set_color);

  ci::Color GetColor();

  void SetChangeInX(int set_change_in_x);

  int GetChangeInX();

 private:
  //member variables of the paddle class(attributes of a paddle)
  vec2 paddle_top_left_;
  vec2 paddle_bottom_right_;
  ci::Color color_;
  int change_in_x_;
};
}