#include <cinder/audio/SamplePlayerNode.h>
#include <cinder/audio/Voice.h>
#include "brick_breaker_app.h"
#include "util.h"

namespace brickbreaker {

BrickBreakerApp::BrickBreakerApp() :
    display_(vec2{0,0}, vec2{900,900}) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  //LoadAudioFiles();
}

void BrickBreakerApp::draw() {
  //draw the background
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  //draw intro string on the screen
  std::string intro_label = "Welcome to BrickBreaker! Press space to move the ball";
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStringCentered(intro_label, vec2{1050,100});

  //display all components on the screen
  display_.Display();
}

void BrickBreakerApp::update() {
  //update the display using the advance frame method
  display_.AdvanceFrame();

  //check if there has been a collision with the paddle and play the sound effect
  if (display_.is_paddle_collision_) {
    //PlayPaddleSoundFX();
  }

  //check if there has been a collision with the brick and play the sound effect
  if (display_.is_brick_collision_) {
    //PlayBrickSoundFX();
  }
}

void BrickBreakerApp::keyDown(ci::app::KeyEvent event) {
  switch(event.getCode()) {

    //code for the right arrow key pressed
    case ci::app::KeyEvent::KEY_RIGHT: {
      //paddle should not be able to go beyond the box
      if (display_.paddle_.GetPaddleBottomRight().x == 900) {
        //do not allow movement beyond right side of box
        display_.paddle_.SetChangeInX(0);
        display_.paddle_.MovePaddle();
      } else {
        //set the x change to move the paddle
        display_.paddle_.SetChangeInX(kPaddleChange);
        display_.paddle_.MovePaddle();
      }
      break;
    }

    //code for the left arrow key pressed
    case ci::app::KeyEvent::KEY_LEFT: {
      if (display_.paddle_.GetPaddleTopLeft().x == 0) {
        //paddle should not be able to go beyond the left side of the box
        display_.paddle_.SetChangeInX(0);
        display_.paddle_.MovePaddle();
      } else {
        //set the x change to move the paddle
        display_.paddle_.SetChangeInX(-kPaddleChange);
        display_.paddle_.MovePaddle();
      }
      break;
    }

    //code for the space bar pressed
    case ci::app::KeyEvent::KEY_SPACE: {
      //set the ball's velocity to move when the space bar is pressed
      display_.ball_.SetVelocity(vec2{kBallXVelocity, kBallYVelocity});
      break;
    }

    //code for the return key pressed
    case ci::app::KeyEvent::KEY_RETURN: {
      //reset all state so the player can play again
      display_.Reset();
      break;
    }
  }
}

void BrickBreakerApp::LoadAudioFiles() {
  try {
    //read brick collisions file
    cinder::audio::SourceFileRef brick_collision_file;
    brick_collision_file = cinder::audio::load(ci::app::loadAsset(
        R"(Bonk 1.mp3)"));

    //read paddle collisions file
    cinder::audio::SourceFileRef paddle_collision_file;
    paddle_collision_file = cinder::audio::load(ci::app::loadAsset(
        R"(Ploop.mp3)"));

    //set brick and paddle collision by creating audio files
    brick_collision_ = ci::audio::Voice::create(brick_collision_file);
    paddle_collision_ = ci::audio::Voice::create(paddle_collision_file);

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

}

void BrickBreakerApp::PlayBrickSoundFX() const {
  //play sound effect
  brick_collision_ ->start();
  brick_collision_ ->stop();
}

void BrickBreakerApp::PlayPaddleSoundFX() const {
  //play sound effect
  paddle_collision_ ->start();
  paddle_collision_ ->stop();
}

}  // namespace brickbreaker