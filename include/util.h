#pragma once

#include <vector>
#include "brick.h"
namespace brickbreaker {

/**
 * helper method to calculate a random number
 * @param min lower bound
 * @param max upper bound
 * @return the random number
 */
size_t GenerateRandomNumber(size_t min, size_t max);

void DeleteElementFrom2DVector(std::vector<Brick>& bricks, size_t col);
} //namespace brickbreaker