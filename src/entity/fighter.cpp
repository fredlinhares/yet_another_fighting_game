/*
 * Copyright 2024 Frederico de Oliveira Linhares
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fighter.hpp"

namespace
{
  constexpr int orthogonal_speed = 3;
  constexpr int diagonal_speed = 2;

  inline void
  collide_top(Entity::Fighter &player)
  {
    if(player.sprite.y < 0) player.sprite.y = 0;
  }

  inline void
  collide_bottom(Entity::Fighter &player)
  {
    if((player.sprite.y + player.sprite.h) > WINDOW_HEIGHT)
      player.sprite.y = WINDOW_HEIGHT - player.sprite.h;
  }

  inline void
  collide_left(Entity::Fighter &player)
  {
    if(player.sprite.x < 0) player.sprite.x = 0;
  }

  inline void
  collide_right(Entity::Fighter &player)
  {
    if((player.sprite.x + player.sprite.w) > WINDOW_WIDTH)
      player.sprite.x = WINDOW_WIDTH - player.sprite.w;
  }
}

namespace Entity
{

void
Fighter::tick()
{
  // Set direction.
  { // Eliminate self-contradicting input like left-right movement.
    Direction vertical_direction{Direction::none};
    Direction horizontal_direction{Direction::none};

    if(input_status[DIRECTION_UP_BIT])
      vertical_direction = Direction::up;
    else if(input_status[DIRECTION_DOWN_BIT])
      vertical_direction = Direction::down;

    if(input_status[DIRECTION_LEFT_BIT])
      horizontal_direction = Direction::left;
    else if(input_status[DIRECTION_RIGHT_BIT])
      horizontal_direction = Direction::right;

    this->current_direction = vertical_direction + horizontal_direction;
  }

  { // Move
    switch(this->current_direction)
    {
    case Direction::up:
      this->sprite.y -= orthogonal_speed;
      collide_top(*this);
      break;
    case Direction::down:
      this->sprite.y += orthogonal_speed;
      collide_bottom(*this);
      break;
    case Direction::left:
      this->sprite.x -= orthogonal_speed;
      collide_left(*this);
      break;
    case Direction::right:
      this->sprite.x += orthogonal_speed;
      collide_right(*this);
      break;
    case Direction::up_left:
      this->sprite.x -= diagonal_speed;
      this->sprite.y -= diagonal_speed;
      collide_left(*this);
      collide_top(*this);
      break;
    case Direction::up_right:
      this->sprite.x += diagonal_speed;
      this->sprite.y -= diagonal_speed;
      collide_right(*this);
      collide_top(*this);
      break;
    case Direction::down_left:
      this->sprite.x -= diagonal_speed;
      this->sprite.y += diagonal_speed;
      collide_left(*this);
      collide_bottom(*this);
      break;
    case Direction::down_right:
      this->sprite.x += diagonal_speed;
      this->sprite.y += diagonal_speed;
      collide_right(*this);
      collide_bottom(*this);
      break;
    }
  }
}

void
Fighter::render()
{
  SDL_SetRenderDrawColor(core.renderer, 0x33, 0x33, 0x99, 0xff);
  SDL_RenderFillRect(core.renderer, &this->sprite);
}

Fighter::Fighter():
  sprite{0, 0, 63, 100}
{
}

}
