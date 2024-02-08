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

#ifndef YAFCE_STATE_SPRITE_H
#define YAFCE_STATE_SPRITE_H 1

#include "../state.hpp"

namespace Mode
{
  class Sprite;
}

namespace State
{

struct Sprite: public State::Base
{
  Mode::Sprite* const mode;

  void
  mouse_button_down(SDL_MouseButtonEvent& b);

  Sprite(Mode::Sprite* mode);
};

}

#endif /* YAFCE_STATE_SPRITE_H */
