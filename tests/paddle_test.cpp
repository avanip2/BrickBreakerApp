#include "paddle.h"
#include <catch2/catch.hpp>

using glm::vec2;
using brickbreaker::Paddle;

TEST_CASE("Paddle move method updates its position correctly") {
  Paddle paddle(vec2{50,50}, vec2{100,100}, ci::Color("gray"));

  SECTION("Right movements correctly updated") {
    paddle.SetChangeInX(10);
    paddle.MovePaddle();
    REQUIRE(paddle.GetPaddleTopLeft().x == 60);
    REQUIRE(paddle.GetPaddleTopLeft().y == 50);
    REQUIRE(paddle.GetPaddleBottomRight().x == 110);
    REQUIRE(paddle.GetPaddleBottomRight().y == 100);
  }

  SECTION("Left movements correctly updated") {
    paddle.SetChangeInX(-10);
    paddle.MovePaddle();
    REQUIRE(paddle.GetPaddleTopLeft().x == 40);
    REQUIRE(paddle.GetPaddleTopLeft().y == 50);
    REQUIRE(paddle.GetPaddleBottomRight().x == 90);
    REQUIRE(paddle.GetPaddleBottomRight().y == 100);
  }
}