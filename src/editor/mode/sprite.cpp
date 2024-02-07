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

#include "sprite.hpp"

namespace Mode
{

void
Sprite::key_down(SDL_Keycode keycode)
{
}

void
Sprite::key_up(SDL_Keycode keycode)
{
}

void
Sprite::tick()
{
}

void
Sprite::render()
{
  int destination_width, destination_height;

  if(this->texture_width < core.window_width)
    destination_width = texture_width;
  else
    destination_width = core.window_width;

  if(this->texture_height < core.window_height)
    destination_height = texture_height;
  else
    destination_height = core.window_height;

  SDL_Rect destination{0, 0, destination_width, destination_height};

  SDL_RenderCopy(core.renderer, this->texture, &destination, &destination);
}

Sprite::Sprite(SDL_Texture* texture):
  texture{texture}
{
  SDL_QueryTexture(
    this->texture, nullptr, nullptr, &texture_width, &texture_height);
}

}
