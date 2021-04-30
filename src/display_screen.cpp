#include "display_screen.h"
#include "util.h"

namespace brickbreaker {

using glm::vec2;

DisplayScreen::DisplayScreen(vec2 set_display_top_left_position, vec2 set_display_bottom_right_position) {
  display_top_left_position_ = set_display_top_left_position;
  display_bottom_right_position_ = set_display_bottom_right_position;

  //add bricks, ball and paddle to the display by initializing them here
  AddBricksToDisplay(kMinBrickSize);
  ball_ = Ball(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2},
               vec2{0,0}, kBallSize,ci::Color("red"));
  paddle_ = Paddle(vec2{kPaddleLocation, display_bottom_right_position_.x - kPaddleSize},
                   vec2{kPaddleLocation + kPaddleLength, display_bottom_right_position_.x}, ci::Color("gray"));
  num_lives_ = 3;
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

  //display the ball and paddle
  ball_.DisplayBall();
  paddle_.DisplayPaddle();
  ci::gl::color(ci::Color("White"));
  ci::gl::drawStrokedRect(ci::Rectf(display_top_left_position_, display_bottom_right_position_));
}

void DisplayScreen::AdvanceFrame() {
  //loop through the rows in the display
  for (size_t row = 0; row < brick_rows_.size(); row++) {
    //loop through the bricks in the row
    for (Brick &brick : brick_rows_[row]) {
      if (brick.GetBottomRightPosition().y >= display_bottom_right_position_.y) {
        //remove all bricks from the display if a row has reached the bottom
        brick_rows_.clear();
      }

      //check if a collision has occurred between the ball and the current brick
      UpdateForBrickCollision(ball_, brick);
      if (brick.GetNumHits() == 0) {
        brick.SetNumHits(10); //placeholder
        // TODO: figure out how to remove a single brick from the 2d vector
      }
    }
  }

  // TODO: figure out how to use a sleep timer to add new bricks periodically

  //check if the number of lives is 0 and set the ball's position and velocity accordingly
  if (num_lives_ == 0) {
    ball_.SetVelocity(vec2{0,0});
    ball_.SetPosition(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2});
  }

  //check for ball collision with the wall and update the position of the ball
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
                    vec2{current_brick_position + brick_size, y_position + kMinBrickSize},
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

  //check if the ball is moving in the right direction for a collision to occur
  if ((ball.GetPosition().x >= brick.GetTopLeftPosition().x && x_velocity > 0) ||
      (ball.GetPosition().x <= brick.GetBottomRightPosition().x && x_velocity < 0)) {

    //check if the y position of the ball matches that of a brick
    if (brick.GetTopLeftPosition().y <= ball.GetPosition().y && brick.GetBottomRightPosition().y >= ball.GetPosition().y) {
      //set velocity and num hits accordingly
      x_velocity *= -1;
      num_hits--;
    }
  }

  //check if the ball is moving in the right direction for a collision to occur
  if ((ball.GetPosition().y >= brick.GetTopLeftPosition().y && y_velocity > 0) ||
      (ball.GetPosition().y <= brick.GetBottomRightPosition().y && y_velocity < 0)) {

    //check if the x position of the ball matches that of a brick
    if (brick.GetTopLeftPosition().x <= ball.GetPosition().x && brick.GetBottomRightPosition().x >= ball.GetPosition().x) {
      //set velocity and num hits accordingly
      y_velocity *= -1;
      num_hits--;
    }
  }

  //set the attributes of the ball and brick based on changes in if statements
  ball.SetVelocity(vec2{x_velocity, y_velocity});
  brick.SetNumHits(num_hits);
  //check to see if the ball is between the two y coordinates of the brick to see if a collision is even possible
  //if (brick.GetTopLeftPosition().y <= ball.GetPosition().y && brick.GetBottomRightPosition().y >= ball.GetPosition().y) {

    //check that the ball's x position is the same as the brick's top left x position and the ball is moving in the right direction
    //if (ball.GetPosition().x >= brick.GetTopLeftPosition().x && x_velocity > 0) {
      //set the ball's velocity and number of hits accordingly
      //ball.SetVelocity(vec2{-x_velocity, y_velocity});
      //brick.SetNumHits(num_hits--);
    //}

    //check that the ball's x position is the same as the brick's bottom right x position and the ball is moving in the right direction
    //if (ball.GetPosition().x <= brick.GetBottomRightPosition().x && x_velocity < 0) {
      //set the ball's velocity and number of hits on a brick
      //ball.SetVelocity(vec2{-x_velocity, y_velocity});
      //brick.SetNumHits(num_hits--);
    //}

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
    y_velocity *= -1;
    //num_lives_--;
    //ball.SetPosition(vec2{display_bottom_right_position_.x / 2, display_bottom_right_position_.y / 2});
    //ball.SetVelocity(vec2{kBallXVelocity,kBallYVelocity});
  }

  //check if the ball has collided with the side walls and negate the x_velocity accordingly
  if (((ball.GetPosition().x - ball.GetRadius()) <= display_top_left_position_.x && x_velocity < 0) ||
      (ball.GetPosition().x + ball.GetRadius() >= display_bottom_right_position_.x && x_velocity > 0)) {
    x_velocity *= -1;
  }

  //set the ball's updated velocity using new values
  ball.SetVelocity(vec2{x_velocity, y_velocity});
}

void DisplayScreen::RemoveBrickFromDisplay(Brick &brick_to_remove) {
  brick_to_remove.SetColor(ci::Color("black"));
}

} //namespace brickbreaker