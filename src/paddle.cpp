#include "paddle.h"

namespace brickbreaker {

using glm::vec2;

Paddle::Paddle(vec2 set_paddle_top_left, vec2 set_paddle_bottom_right, ci::Color set_color) {
  paddle_top_left_ = set_paddle_top_left;
  paddle_bottom_right_ = set_paddle_bottom_right;
  color_ = set_color;
}

Paddle::Paddle() {}

void Paddle::DisplayPaddle() const {
  ci::gl::color(color_);
  ci::gl::drawSolidRect(ci::Rectf(paddle_top_left_, paddle_bottom_right_));
}

void Paddle::SetPaddleTopLeft(vec2 set_paddle_top_left) {
  paddle_top_left_ = set_paddle_top_left;
}

vec2 Paddle::GetPaddleTopLeft() {
  return paddle_top_left_;
}

void Paddle::SetPaddleBottomRight(vec2 set_paddle_bottom_right) {
  paddle_bottom_right_ = set_paddle_bottom_right;
}

vec2 Paddle::GetPaddleBottomRight() {
  return paddle_bottom_right_;
}

void Paddle::SetColor(ci::Color set_color) {
  color_ = set_color;
}

ci::Color Paddle::GetColor() {
  return color_;
}

void Paddle::SetChangeInX(int set_change_in_x) {
  change_in_x_ = set_change_in_x;
}

void Paddle::MovePaddle() {
  //initialize the x positions of the paddle as that is the only thing that can change
  size_t curr_paddle_top_left_x = paddle_top_left_.x;
  size_t curr_paddle_bottom_right_x = paddle_bottom_right_.x;

  //update the paddle's location based on where it should move
  paddle_top_left_ = vec2{curr_paddle_top_left_x + change_in_x_, paddle_top_left_.y};
  paddle_bottom_right_ = vec2{curr_paddle_bottom_right_x + change_in_x_, paddle_bottom_right_.y};
}
} //namespace brickbreaker