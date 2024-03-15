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

#include "scroll.hpp"

#include "../mode/sprite.hpp"

namespace State
{

void
Scroll::mouse_button_up(SDL_MouseButtonEvent& b)
{
	this->mode->reset_state();
}

void
Scroll::mouse_motion(int x, int y, int xrel, int yrel)
{
  this->mode->scroll(xrel, yrel);
}

Scroll::Scroll(Mode::Sprite* mode):
  mode{mode}
{
}

}
