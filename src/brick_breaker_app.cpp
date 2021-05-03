#include <cinder/audio/SamplePlayerNode.h>
#include <cinder/audio/Voice.h>
#include "brick_breaker_app.h"
#include "util.h"

namespace brickbreaker {

BrickBreakerApp::BrickBreakerApp() :
    display_(vec2{0,0}, vec2{900,900}) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  LoadAudioFiles();
}

void BrickBreakerApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  std::string intro_label = "Welcome to BrickBreaker! Press space to move the ball";
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStringCentered(intro_label, vec2{1050,100});
  //display all components on the screen
  display_.Display();
}

void BrickBreakerApp::update() {
  display_.AdvanceFrame();
  if (display_.is_brick_collision_) {
    PlayBrickSoundFX();
  }
  if (display_.is_paddle_collision_) {
    PlayPaddleSoundFX();
  }
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

void BrickBreakerApp::LoadAudioFiles() {
  cinder::audio::SourceFileRef brick_collision_file;
  brick_collision_file = cinder::audio::load(ci::app::loadAsset("Bonk 1.mp3"));
  cinder::audio::SourceFileRef paddle_collision_file;
  paddle_collision_file = cinder::audio::load(ci::app::loadAsset("Ploop.mp3"));
  brick_collision_ = ci::audio::Voice::create(brick_collision_file);
  paddle_collision_ = ci::audio::Voice::create(paddle_collision_file);
}

void BrickBreakerApp::PlayBrickSoundFX() {
  brick_collision_ ->stop();
  brick_collision_ ->start();
}

void BrickBreakerApp::PlayPaddleSoundFX() {
  paddle_collision_ ->stop();
  paddle_collision_ ->start();
}

}  // namespace brickbreaker