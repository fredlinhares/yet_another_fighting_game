# Personagem

Each instance of the class [Fighter](../src/game/entity/fighter.hpp) contains information about a character controlled by a player or computer.


## Posição

The character animations use several sprites with different width and height.
It also uses collisionboxes, hurtboxes, and hitboxes.
Due to all these variations and positions, a character position is defined by its `x` and `y` position, and all other objects are relative to these two values.


## Máquina de Estados

Each fighter functions as a state machine.
Each [state](../src/entity/state.hpp) defines the animations and boxes.
The states may include:

- Light punch
- Strong punch
- Light punch crouching
- Jump
- Crouch

