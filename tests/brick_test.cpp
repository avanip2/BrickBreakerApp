#include "brick.h"
#include <catch2/catch.hpp>

using glm::vec2;
using brickbreaker::Brick;

TEST_CASE("Brick number of hits is properly decrementing") {
  Brick brick(5, vec2{50,50}, vec2{100,100}, ci::Color("blue"), 50);

  SECTION("Decrease brick number of hits by 1") {
    brick.SetNumHits(brick.GetNumHits() - 1);
    REQUIRE(brick.GetNumHits() == 4);
  }
}