# Main Loop

The first thing we need in any game is the [main loop](../src/game/main.cpp).
Each execution of it produces one game frame.
Each execution of it produces one game frame.
The main loop is responsible for the following tasks:

- Read input
- Update game
- Render
- Control frame speed


## Input reading

Here, the code processes all the input from the keyboard, joystick, mouse, and so on.
It also reads the commands to the application as the signal to close the game Window.


## Update game

Updates all elements of the game, making them move.


## Render

This engine uses a technique called double buffering.
It starts by rendering a temporary buffer instead of drawing everything directly to the screen.
Then, when the temporary buffer is complete, copy it to the screen.


## Timer

The timer is responsible for computing how long a frame takes to render.
It can also limit the amount of frames per second in a game.
