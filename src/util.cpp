#include <cstdlib>
#include "util.h"

namespace brickbreaker {

size_t GenerateRandomNumber(size_t min, size_t max) {
  size_t randomly_generated_number = ((rand() % (max - min + 1)) + min);
  return randomly_generated_number;
}

void DeleteElementFrom2DVector(std::vector<Brick>& bricks, size_t col) {
  bricks.erase(bricks.begin() + col);
}
} //namespace brickbreaker