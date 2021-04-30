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

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;

  const int kWindowSize = 1250;
  const int kMargin = 100;
 private:
  DisplayScreen display_;

};
} // namespace brickbreaker