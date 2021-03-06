#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "display_screen.h"
#include <cinder/audio/Voice.h>

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

  /**
   * helper method to load the audio files into the app
   */
  void LoadAudioFiles();

  /**
   * helper method that plays the brick's sound effect
   */
  void PlayBrickSoundFX() const;

  /**
   * helper method that plays the paddle's sound effect
   */
  void PlayPaddleSoundFX() const;

  const int kWindowSize = 1250;
  const int kMargin = 100;
  const int kPaddleChange = 20;
  constexpr static int kBallXVelocity = -5;
  constexpr static int kBallYVelocity = -6;
  ci::audio::VoiceRef brick_collision_;
  ci::audio::VoiceRef paddle_collision_;

 private:
  DisplayScreen display_;

};
} // namespace brickbreaker