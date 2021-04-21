#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace brickbreaker {
class BrickBreakerApp : public ci::app::App {
 public:
  BrickBreakerApp();

  void draw() override;
  void update() override;

  const int kWindowSize = 1250;
  const int kMargin = 100;
};
} // namespace brickbreaker