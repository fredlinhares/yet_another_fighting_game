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

#include "image.hpp"

#include "../main.hpp"

namespace Button
{

void
Image::click_action(int x, int y)
{
	this->callback();
}

void
Image::render()
{
	SDL_RenderCopy(
		core.renderer, editor_state->tex_direction_buttons,
		this->src, &this->location);
}

Image::Image(
	SDL_Rect* sprite, int x, int y, std::function<void(void)> callback):
	src{sprite},
	callback{callback}
{
	this->location.x = x;
	this->location.y = y;
	this->location.w = sprite->w;
	this->location.h = sprite->h;
}

}
