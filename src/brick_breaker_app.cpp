#include "brick_breaker_app.h"
#include "util.h"

namespace brickbreaker {

BrickBreakerApp::BrickBreakerApp() :
    display_(vec2{0,0}, vec2{900,900}) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void BrickBreakerApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  //display all components on the screen
  display_.Display();
}

void BrickBreakerApp::update() {
  display_.AdvanceFrame();
}

void BrickBreakerApp::keyDown(ci::app::KeyEvent event) {
  switch(event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT: {
      display_.paddle_.SetChangeInX(kPaddleChange);
      display_.paddle_.MovePaddle();
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      display_.paddle_.SetChangeInX(-kPaddleChange);
      display_.paddle_.MovePaddle();
      break;
    }
    case ci::app::KeyEvent::KEY_SPACE: {
      display_.ball_.SetVelocity(vec2{kBallXVelocity, kBallYVelocity});
    }
  }
}

}  // namespace brickbreaker