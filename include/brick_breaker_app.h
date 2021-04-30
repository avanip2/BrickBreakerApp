#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "display_screen.h"

namespace brickbreaker {

/**
 * app that runs the game
 */
class BrickBreakerApp : public ci::app::App {
 public:
  BrickBreakerApp();

  /**
   * override method to draw
   */
  void draw() override;

  /**
   * override method to update screen
   */
  void update() override;

  /**
   * override method to add key event for paddle
   * @param event identified key event
   */
  void keyDown(ci::app::KeyEvent event) override;

  const int kWindowSize = 1250;
  const int kMargin = 100;
  const int kPaddleChange = 20;
  constexpr static int kBallXVelocity = -4;
  constexpr static int kBallYVelocity = -5;
 private:
  DisplayScreen display_;

};
} // namespace brickbreaker