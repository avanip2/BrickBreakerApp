#include "brick.h"
#include "cinder/gl/gl.h"

namespace brickbreaker {
Brick::Brick(size_t set_num_hits, vec2 set_top_left_position, vec2 set_bottom_right_position, ci::Color set_color) {
  num_hits_ = set_num_hits;
  top_left_position_ = set_top_left_position;
  bottom_right_position_ = set_bottom_right_position;
  color_ = set_color;
}

void Brick::DisplayBrick() const {
  ci::gl::color(color_);
  ci::gl::drawSolidRect(ci::Rectf(top_left_position_, bottom_right_position_));
}

} //namespace brickbreaker