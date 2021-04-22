#include "brick.h"
#include "cinder/gl/gl.h"

namespace brickbreaker {

using glm::vec2;

Brick::Brick(size_t set_num_hits, vec2 set_top_left_position, vec2 set_bottom_right_position, ci::Color set_color) {
  num_hits_ = set_num_hits;
  top_left_position_ = set_top_left_position;
  bottom_right_position_ = set_bottom_right_position;
  color_ = set_color;
}

void Brick::DisplayBrick() const {
  ci::gl::color(color_);
  ci::gl::drawSolidRect(ci::Rectf(top_left_position_, bottom_right_position_));
  std::string num_hits_label = std::to_string(num_hits_);
  ci::gl::drawStringCentered(num_hits_label, vec2{top_left_position_.x, bottom_right_position_.y});
}

void Brick::SetColor(ci::Color set_color) {
  color_ = set_color;
}

ci::Color Brick::GetColor() {
  return color_;
}

void Brick::SetBottomRightPosition(vec2 set_bottom_right_position) {
  bottom_right_position_ = set_bottom_right_position;
}

vec2 Brick::GetBottomRightPosition() {
  return bottom_right_position_;
}

void Brick::SetTopLeftPosition(vec2 set_top_left_position) {
  top_left_position_ = set_top_left_position;
}

vec2 Brick::GetTopLeftPosition() {
  return top_left_position_;
}

void Brick::SetNumHits(size_t set_num_hits) {
  num_hits_ = set_num_hits;
}

size_t Brick::GetNumHits() {
  return num_hits_;
}
} //namespace brickbreaker