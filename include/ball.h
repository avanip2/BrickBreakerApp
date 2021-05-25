#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace brickbreaker {

class Ball {
 public:
  Ball(vec2 set_position, vec2 set_velocity, float set_radius, ci::Color set_color);
  Ball();

  /**
   * helper method to display the ball
   */
  void DisplayBall() const;

  /**
   * helper method to update the position of the ball
   */
  void UpdatePosition();

  //setters and getters
  void SetPosition(vec2 set_position);

  vec2 GetPosition();

  void SetVelocity(vec2 set_velocity);

  vec2 GetVelocity();

  float GetRadius();

 private:
  //member variables of the ball class
  vec2 position_;
  vec2 velocity_;
  float radius_;
  ci::Color color_;
};
} //namespace brickbreaker