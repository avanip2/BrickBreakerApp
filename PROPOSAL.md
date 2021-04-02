**Final Project Proposal - Avani Puranik**

The project I would like to implement for the final project is a game that is sort of a combination between swipe
brick breaker and atari breakout. More specifically, my implementation of this game will involve one ball that
starts from a platform just above the bottom of a container and will travel upwards to collide with bricks that will
be randomly assigned a value that will tell the player how many times they have to get the ball to collide with
it for it to disappear. There will be a platform just above the bottom of the container that can be controlled by
the player via the mousepad and they will try to catch the ball on the platform to prevent it from hitting the 
bottom of the container. If the ball hits the bottom of the container, the player will lose a life. Once the player
allows the ball to hit the bottom of the container three times, the player has lost the game and the game is over.
The bricks will be randomly assigned a number of hits necessary to make it disappear from a range of values.
Additionally, after a certain number of seconds passes, a new line of bricks will appear on the screen along with
all the breaks the player has yet to destroy. If the bricks reach the sliding platform above the bottom of the
container, the player has lost the game and the game is over. 

During the first week of the project, I will work to create the brick class in which I will store each brick's
position, number of hits required to destroy it, and any other property I think is necessary to store as part of
the class for the brick. I will work on drawing each of the bricks and randomizing their x-position, since they
will all be in the same row and will have the same y-position with every set of bricks added to the screen in one
call of the draw method. I plan to store all the bricks in a vector and every time the screen updates, I will loop through the vector and check if 
any of the bricks have reached the bottom of the container. During the second week of the project, I will create
properties of the particle and write the method to execute the collisions of the particles with the bricks. This
will require updating properties of the brick as well, ensuring that the number of hits required to break each
brick also decreases and this change is properly displayed on the screen. During the final week of the project,
I will work on getting the sliding platform to move and properly execute its collisions with the ball as well.
Additionally, I will also try to implement some sort of sound effects every time the ball collides with the 
sliding platform and the brick to make the game a little more interesting for the player.

If there is extra time after I complete all the implementations mentioned above, I will work to implement
the addition of another ball in the game if the game continues for a certain amount of time to make it more
challenging for the player. This will likely require me to create a vector to store all the balls that are
added to the screen before the game ends. Another implementation I can add if I have extra time after completing
the other things mentioned above, I can also look into a way to make the ball's minimum and maximum possible
velocities increase if the game continues for a certain amount of time to add another element of challenge for
the player and help the game end quicker. I have chosen to do this game because I really like
the swipe brick breaker game and I wanted to put a new twist to it with the continuous movement of the ball and
randomization of brick size in a row. I hope to be able to utilize all the skills I have learned in this class
to make something fun for myself and others to play!