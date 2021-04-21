#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {
class Brick {
 public:
  Brick(size_t set_num_hits, vec2 set_top_left_position, vec2 set_bottom_right_position, ci::Color set_color);
  void DisplayBrick() const;
 private:
  size_t num_hits_;
  vec2 top_left_position_;
  vec2 bottom_right_position_;
  ci::Color color_;
};
} //namespace brickbreaker