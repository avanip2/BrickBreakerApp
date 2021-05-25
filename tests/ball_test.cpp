#include "ball.h"
#include <catch2/catch.hpp>

using glm::vec2;
using brickbreaker::Ball;

TEST_CASE("Ball position updated using velocity") {
  Ball ball(vec2{100,100}, vec2{0,0}, 10, ci::Color("red"));

  SECTION("Ball position does not change when velocity is 0") {
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 100);
    REQUIRE(ball.GetPosition().y == 100);
  }

  SECTION("Ball new velocity to positive x set correctly and update position correctly") {
    ball.SetVelocity(vec2{10,0});
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 110);
    REQUIRE(ball.GetPosition().y == 100);
  }

  SECTION("Ball new velocity to negative x set correctly and update position correctly") {
    ball.SetVelocity(vec2{-10,0});
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 90);
    REQUIRE(ball.GetPosition().y == 100);
  }

  SECTION("Ball new velocity to positive y set correctly and update position correctly") {
    ball.SetVelocity(vec2{0,10});
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 100);
    REQUIRE(ball.GetPosition().y == 110);
  }

  SECTION("Ball new velocity to negative y set correctly and update position correctly") {
    ball.SetVelocity(vec2{0,-10});
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 100);
    REQUIRE(ball.GetPosition().y == 90);
  }

  SECTION("Ball new velocity to negative x and y set correctly and update position correctly") {
    ball.SetVelocity(vec2{-10,-10});
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 90);
    REQUIRE(ball.GetPosition().y == 90);
  }

  SECTION("Ball new velocity to positive x and y set correctly and update position correctly") {
    ball.SetVelocity(vec2{10,10});
    ball.UpdatePosition();
    REQUIRE(ball.GetPosition().x == 110);
    REQUIRE(ball.GetPosition().y == 110);
  }
}