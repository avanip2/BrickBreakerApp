#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

/**
 * class to represent one brick
 */
class Brick {
 public:
  Brick(size_t set_num_hits, vec2 set_top_left_position, vec2 set_bottom_right_position, ci::Color set_color);

  /**
   * method to draw a brick
   */
  void DisplayBrick() const;

  //setters and getters
  void SetNumHits(size_t set_num_hits);
  size_t GetNumHits();
  void SetTopLeftPosition(vec2 set_top_left_position);
  vec2 GetTopLeftPosition();
  void SetBottomRightPosition(vec2 set_bottom_right_position);
  vec2 GetBottomRightPosition();
  void SetColor(ci::Color set_color);
  ci::Color GetColor();
 private:
  size_t num_hits_;
  vec2 top_left_position_;
  vec2 bottom_right_position_;
  ci::Color color_;
  constexpr static size_t kStringMargin = 25;
};
} //namespace brickbreaker