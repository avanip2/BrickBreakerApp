#include "ball.h"

namespace brickbreaker {

using glm::vec2;

Ball::Ball(vec2 set_position, vec2 set_velocity, float set_radius, ci::Color set_color) {
  position_ = set_position;
  velocity_ = set_velocity;
  radius_ = set_radius;
  color_ = set_color;
}

void Ball::SetColor(ci::Color set_color) {
  color_ = set_color;
}

ci::Color Ball::GetColor() {
  return color_;
}

void Ball::SetVelocity(vec2 set_velocity) {
  velocity_ = set_velocity;
}

vec2 Ball::GetVelocity() {
  return velocity_;
}

void Ball::SetPosition(vec2 set_position) {
  position_ = set_position;
}

vec2 Ball::GetPosition() {
  return position_;
}

void Ball::SetRadius(float set_radius) {
  radius_ = set_radius;
}

float Ball::GetRadius() {
  return radius_;
}

} //namespace brickbreaker