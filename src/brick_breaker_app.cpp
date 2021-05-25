#include "brick_breaker_app.h"

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

}  // namespace brickbreasker