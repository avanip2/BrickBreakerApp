#include "display_screen.h"
#include <catch2/catch.hpp>

using glm::vec2;
using brickbreaker::DisplayScreen;
using brickbreaker::Brick;
using brickbreaker::Ball;
using brickbreaker::Paddle;

TEST_CASE("check that wall collisions work") {
  DisplayScreen test_screen(vec2{0,0}, vec2{400,400});
  Ball ball(vec2{0,0}, vec2{0,0}, 10, ci::Color("blue"));

  SECTION("ball collides with right wall") {
    ball.SetPosition(vec2{390, 100});
    ball.SetVelocity(vec2{5, 4});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == -5);
    REQUIRE(ball.GetVelocity().y == 4);
  }

  SECTION("ball collides with left wall") {
    ball.SetPosition(vec2{10, 100});
    ball.SetVelocity(vec2{-5, 4});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 5);
    REQUIRE(ball.GetVelocity().y == 4);
  }

  SECTION("ball collides with top wall") {
    ball.SetPosition(vec2{100, 10});
    ball.SetVelocity(vec2{4, -5});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 4);
    REQUIRE(ball.GetVelocity().y == 5);
  }

  SECTION("velocity set to 0 when ball collides with bottom") {
    ball.SetPosition(vec2{100, 390});
    ball.SetVelocity(vec2{4,5});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 0);
    REQUIRE(ball.GetVelocity().y == 0);
    REQUIRE(test_screen.GetNumLives() == 2);
  }
}

TEST_CASE("ball does not collide with wall") {
  DisplayScreen test_screen(vec2{0,0}, vec2{400,400});
  Ball ball(vec2{0,0}, vec2{0,0}, 10, ci::Color("blue"));

  SECTION("ball does not collide with right wall due to position") {
    ball.SetPosition(vec2{385, 100});
    ball.SetVelocity(vec2{5,4});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 5);
    REQUIRE(ball.GetVelocity().y == 4);
  }

  SECTION("ball does not collide with right wall due to velocity") {
    ball.SetPosition(vec2{390, 100});
    ball.SetVelocity(vec2{-5, 4});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == -5);
    REQUIRE(ball.GetVelocity().y == 4);
  }

  SECTION("ball does not collide with the left wall due to position") {
    ball.SetPosition(vec2{15, 100});
    ball.SetVelocity(vec2{-5,4});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == -5);
    REQUIRE(ball.GetVelocity().y == 4);
  }

  SECTION("ball does not collide with left wall due to velocity") {
    ball.SetPosition(vec2{10, 100});
    ball.SetVelocity(vec2{5,4});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 5);
    REQUIRE(ball.GetVelocity().y == 4);
  }

  SECTION("ball does not collide with the top wall due to position") {
    ball.SetPosition(vec2{100, 15});
    ball.SetVelocity(vec2{4, -5});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 4);
    REQUIRE(ball.GetVelocity().y == -5);
  }

  SECTION("ball does not collide with the top wall due to velocity") {
    ball.SetPosition(vec2{100, 10});
    ball.SetVelocity(vec2{4,5});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 4);
    REQUIRE(ball.GetVelocity().y == 5);
  }

  SECTION("ball does not collide with the bottom wall due to position") {
    ball.SetPosition(vec2{100, 385});
    ball.SetVelocity(vec2{4,5});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 4);
    REQUIRE(ball.GetVelocity().y == 5);
  }

  SECTION("ball does not collide with the bottom wall due to velocity") {
    ball.SetPosition(vec2{100, 390});
    ball.SetVelocity(vec2{4, -5});
    test_screen.UpdateForBallCollisionWithWall(ball);
    REQUIRE(ball.GetVelocity().x == 4);
    REQUIRE(ball.GetVelocity().y == -5);
  }
}

TEST_CASE("ball collides with brick") {
  DisplayScreen test_screen(vec2{0,0}, vec2{400,400});
  Ball ball(vec2{0,0}, vec2{0,0}, 10, ci::Color("blue"));
  Brick brick(5, vec2{100, 50}, vec2{150, 100}, ci::Color("red"), 50);

  SECTION("ball collides with the right side of a brick") {
    ball.SetPosition(vec2{160, 75});
    ball.SetVelocity(vec2{-5, 4});
    test_screen.UpdateForBrickCollision(ball, brick);
    REQUIRE(ball.GetVelocity().x == 5);
    REQUIRE(ball.GetVelocity().y == -4);
  }

  SECTION("ball collides with the left side of the brick") {
    ball.SetPosition(vec2{90, 75});
    ball.SetVelocity(vec2{5,4});
    test_screen.UpdateForBrickCollision(ball, brick);
    REQUIRE(ball.GetVelocity().x == -5);
    REQUIRE(ball.GetVelocity().y == -4);
  }

  SECTION("ball collides with the bottom of the brick") {
    ball.SetPosition(vec2{125, 110});
    ball.SetVelocity(vec2{4, -5});
    test_screen.UpdateForBrickCollision(ball, brick);
    REQUIRE(ball.GetVelocity().x == -4);
    REQUIRE(ball.GetVelocity().y == 5);
  }

  SECTION("ball collides with the top of the brick") {
    ball.SetPosition(vec2{125, 40});
    ball.SetVelocity(vec2{4, 5});
    test_screen.UpdateForBrickCollision(ball, brick);
    REQUIRE(ball.GetVelocity().x == -4);
    REQUIRE(ball.GetVelocity().y == -5);
  }
}