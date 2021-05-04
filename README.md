# BrickBreaker
![](assets/brickbreaker.png)
![](assets/brickbreaker2.png)

## Description
BrickBreaker is a game in which there is one ball and an initial row of bricks near the top of the screen along with a 
paddle at the bottom of the screen. Each brick has a randomized number of hits needed to break it as well as a randomized
width. The paddle is moved using the keys and if the ball misses the paddle and touches the bottom of the gameplay screen,
the player will lose a life and they receive a total of 3 lives. If the player loses three lives, the game will be over.
Other ways the game can end include a brick reaching the bottom of the screen and it is not destroyed as well as the player
simply destroying all the brick. The player receives a score based on how many times they hit bricks. The ball will move
at a velocity when the space bar is pressed and keep moving unless the player lets the ball hit the bottom of the gameplay
screen to lose a life. If the player loses three lives, they can reset the game and play again with a single row of new bricks 
appearing at the top of the gameplay screen. The player will be able to control the paddle using the left and right keys on the keyboard.

### Controls
| Key       | Action                                                      |
|---------- |-------------------------------------------------------------|
| `right`   | Move paddle to the right                                    |
| `left`    | Move paddle to the left                                     |
| `space`   | Move the ball                                               |
| `return`  | Reset state to play again                                   |


## Dependencies
- [gcc] or [clang] or [MSVC 2015+][visual-studio]
- [cmake]
- [cinder]

