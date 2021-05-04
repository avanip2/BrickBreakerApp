#include <chrono>
#include <cinder/audio/Voice.h>
#include "display_screen.h"
#include "util.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;

  //add bricks, ball and paddle to the display by initializing them here
  AddBricksToDisplay(kBrickHeight);
  ball_ = Ball(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2},
               vec2{0,0}, kBallSize,ci::Color("red"));
  paddle_ = Paddle(vec2{kPaddleLocation, display_bottom_right_position_.x - kPaddleSize},
                   vec2{kPaddleLocation + kPaddleLength, display_bottom_right_position_.x}, ci::Color("gray"));

  //set state about the game cycle
  num_lives_ = 3;
  calls_to_advance_ = 0;
  current_score_ = 0;
}

void DisplayScreen::Reset() {
  //reset state about gameplay
  num_lives_ = 3;
  calls_to_advance_ = 0;
  current_score_ = 0;
  has_game_ended_ = false;
  brick_rows_.clear();

  //add bricks, ball and paddle to the display by initializing them here
  AddBricksToDisplay(kBrickHeight);
  ball_ = Ball(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2},
               vec2{0,0}, kBallSize,ci::Color("red"));
  paddle_ = Paddle(vec2{kPaddleLocation, display_bottom_right_position_.x - kPaddleSize},
                   vec2{kPaddleLocation + kPaddleLength, display_bottom_right_position_.x}, ci::Color("gray"));
}

void DisplayScreen::Display() const {
  //loop through the rows in the display
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    //loop through bricks in the row
    for (const Brick &brick : brick_rows_[row]) {
      //display each brick
      brick.DisplayBrick();
    }
  }

  //create string labels to print on the screen for score and lives
  std::string score_label = "Score: " + std::to_string(current_score_);
  std::string lives_label = "Lives: " + std::to_string(num_lives_);

  //display the ball and paddle
  ball_.DisplayBall();
  paddle_.DisplayPaddle();
  ci::gl::color(ci::Color("White"));
  ci::gl::drawStrokedRect(ci::Rectf(display_top_left_position_, display_bottom_right_position_));

  //draw the labels on the screen
  ci::gl::drawStringCentered(score_label, vec2{1050, 300});
  ci::gl::drawStringCentered(lives_label, vec2{1050, 400});

  //print that the game has ended if it ends
  if (has_game_ended_) {
    std::string game_ended_label = "The game has ended. Press return to play again.";
    ci::gl::drawStringCentered(game_ended_label, vec2{display_bottom_right_position_.x / 2, (display_bottom_right_position_.y / 2) + 100});
  }
}

void DisplayScreen::AdvanceFrame() {
  //increment the number of calls to update to maintain for determining length of program running
  calls_to_advance_++;

  //if all bricks have been destroyed, the game has ended
  if (brick_rows_.empty()) {
    has_game_ended_ = true;
  }

  //loop through the rows in the display
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    size_t brick_count = 0;
    //loop through the bricks in the row
    for (Brick &brick : brick_rows_[row]) {
      if (brick.GetBottomRightPosition().y >= display_bottom_right_position_.y) {
        //remove all bricks from the display if a row has reached the bottom
        brick_rows_.clear();
        has_game_ended_ = true;
      }

      //check if a collision has occurred between the ball and the current brick
      UpdateForBrickCollision(ball_, brick);

      //determine if the brick has no hits and remove it from the 2d vector if it does
      if (brick.GetNumHits() == 0) {
        DeleteElementFrom2DVector(brick_rows_[row], brick_count);
      }
      //increment count of bricks
      brick_count++;
    }
  }

  //if 2 minutes have passed, add more bricks to the display and reset counter for calls to advance back to 0
  if (calls_to_advance_ == 3600) {
    UpdateBrickPositions();
    calls_to_advance_ = 0;
  }

  //the game has ended if the player has no more lives
  if (num_lives_ == 0) {
    has_game_ended_ = true;
  }

  //if the game has ended, reset the position and velocity of the ball
  if (has_game_ended_) {
    ball_.SetVelocity(vec2{0,0});
    ball_.SetPosition(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2});
  }

  //check for ball collision with the wall and update the position of the ball
  UpdateForPaddleCollision(ball_, paddle_);
  UpdateForBallCollisionWithWall(ball_);
  ball_.UpdatePosition();
}

void DisplayScreen::AddBricksToDisplay(size_t y_position) {
  //initialize a vector of bricks to add each brick to and an initial position to update in the loop
  std::vector<Brick> bricks;
  size_t current_brick_position = kMinBrickSize;

  //loop through the number of bricks
  for (size_t brick = 0; brick < kNumberOfBricksPerRow; brick++) {

    //generate random sizes and number of hits for a brick
    size_t brick_size = GenerateRandomNumber(kMinBrickSize, kMaxBrickSize);
    size_t num_hits = GenerateRandomNumber(kMinNumberOfHits, kMaxNumberOfHits);

    //create new brick using randomly generated attributes and the position of each brick
    Brick new_brick(num_hits, vec2{current_brick_position, y_position},
                    vec2{current_brick_position + brick_size, y_position + kBrickHeight},
                    ci::Color("blue"), brick_size);

    //push brick to bricks vector and update current position for next brick's position
    bricks.push_back(new_brick);
    current_brick_position += brick_size + kBrickMargin;
  }

  //push row of bricks back to the row of bricks vector
  brick_rows_.push_back(bricks);
}

void DisplayScreen::UpdateForBrickCollision(Ball &ball, Brick &brick) {
  //set initial variables for velocity of ball and number of hits on a brick
  float x_velocity = ball.GetVelocity().x;
  float y_velocity = ball.GetVelocity().y;
  size_t num_hits = brick.GetNumHits();
  bool was_x_collision = false;
  bool was_y_collision = false;

  //check if the ball is moving in the right direction for a collision to occur
  if (((ball.GetPosition().x + ball.GetRadius() >= brick.GetTopLeftPosition().x) && x_velocity > 0) ||
      ((ball.GetPosition().x - ball.GetRadius() <= brick.GetBottomRightPosition().x) && x_velocity < 0)) {

    //check if the y position of the ball matches that of a brick
    if (brick.GetTopLeftPosition().y <= ball.GetPosition().y + ball.GetRadius()
    && brick.GetBottomRightPosition().y >= ball.GetPosition().y - ball.GetRadius()) {
      //set was x collision to true
      was_x_collision = true;
    }
  }

  //check if the ball is moving in the right direction for a collision to occur
  if (((ball.GetPosition().y + ball.GetRadius() >= brick.GetTopLeftPosition().y) && y_velocity > 0) ||
      ((ball.GetPosition().y - ball.GetRadius() <= brick.GetBottomRightPosition().y) && y_velocity < 0)) {

    //check if the x position of the ball matches that of a brick
    if (brick.GetTopLeftPosition().x <= ball.GetPosition().x + ball.GetRadius()
    && brick.GetBottomRightPosition().x >= ball.GetPosition().x - ball.GetRadius()) {
      //set was y collision to true
      was_y_collision = true;
    }
  }

  //if a collision has occurred, change state about the game
  if (was_x_collision && was_y_collision) {

    //decrement number of hits on brick and set that there was a hit on the brick
    if (num_hits > 0) {
      num_hits--;
    }
    is_brick_collision_ = true;

    //set ball velocities
    x_velocity *= -1;
    y_velocity *= -1;

    //increment the score
    current_score_++;
  }

  //set the attributes of the ball and brick based on changes in if statements
  ball.SetVelocity(vec2{x_velocity, y_velocity});
  brick.SetNumHits(num_hits);
}

void DisplayScreen::UpdateForBallCollisionWithWall(Ball &ball) {
  //set initial variables for the x and y velocities of the ball
  float x_velocity = ball.GetVelocity().x;
  float y_velocity = ball.GetVelocity().y;

  //check to make sure a collision with the wall is possible and negate y_velocity if collision has happened
  if ((ball.GetPosition().y - ball.GetRadius()) <= display_top_left_position_.y && y_velocity < 0) {
    y_velocity *= -1;
  }

  //if the ball has reached the bottom, decrement the number of lives(commented out for purposes of making sure other code works)
  if ((ball.GetPosition().y + ball.GetRadius()) >= display_bottom_right_position_.y && ball.GetVelocity().y > 0) {
    y_velocity = 0;
    x_velocity = 0;
    num_lives_--;
    ball.SetPosition(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2});
  }

  //check if the ball has collided with the side walls and negate the x_velocity accordingly
  if (((ball.GetPosition().x - ball.GetRadius()) <= display_top_left_position_.x && x_velocity < 0) ||
      (ball.GetPosition().x + ball.GetRadius() >= display_bottom_right_position_.x && x_velocity > 0)) {
    x_velocity *= -1;
  }

  //set the ball's updated velocity using new values
  ball.SetVelocity(vec2{x_velocity, y_velocity});
}

void DisplayScreen::UpdateForPaddleCollision(Ball &ball, Paddle &paddle) {
  //set initial variables for calculations
  float x_velocity = ball.GetVelocity().x;
  float y_velocity = ball.GetVelocity().y;

  //check if there is a possible collision with the top of the paddle
  if ((ball.GetPosition().y + ball.GetRadius() >= paddle.GetPaddleTopLeft().y) && y_velocity > 0) {

    //check if the x position of the ball matches that of a brick
    if (paddle.GetPaddleTopLeft().x <= ball.GetPosition().x + ball.GetRadius()
        && paddle.GetPaddleBottomRight().x >= ball.GetPosition().x - ball.GetRadius()) {
      //set velocity and num hits accordingly
      y_velocity *= -1;
      is_paddle_collision_ = true;
    }
  }

  //set velocity of the ball to the new velocity
  ball.SetVelocity(vec2{x_velocity, y_velocity});
}

void DisplayScreen::UpdateBrickPositions() {
  //loop through the rows of bricks backwards to start from the newest addition
  for (int row = brick_rows_.size() - 1; row >= 0; row--) {
    //loop through each brick
    for (Brick &brick : brick_rows_[row]) {
      //recalculate the y position to add the height of the brick to each y position of the brick
      size_t top_left_y_position = brick.GetTopLeftPosition().y + kBrickHeight;
      size_t bottom_right_y_position = brick.GetBottomRightPosition().y + kBrickHeight;

      //set the new positions of the brick
      brick.SetTopLeftPosition(vec2{brick.GetTopLeftPosition().x, top_left_y_position});
      brick.SetBottomRightPosition(vec2{brick.GetBottomRightPosition().x, bottom_right_y_position});
    }
  }

  //add new bricks to the top row
  AddBricksToDisplay(kBrickHeight);
}

size_t DisplayScreen::GetNumLives() const {
  return num_lives_;
}

} //namespace brickbreaker