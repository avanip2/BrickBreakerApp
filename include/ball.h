#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

class Ball {
 public:
  Ball(vec2 set_position, vec2 set_velocity, float set_radius, ci::Color set_color);

  void SetPosition(vec2 set_position);
  vec2 GetPosition();
  void SetVelocity(vec2 set_velocity);
  vec2 GetVelocity();
  void SetRadius(float set_radius);
  float GetRadius();
  void SetColor(ci::Color set_color);
  ci::Color GetColor();
 private:
  vec2 position_;
  vec2 velocity_;
  float radius_;
  ci::Color color_;
};
} //namespace brickbreaker