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

#include "sprite_list.hpp"

#include "main.hpp"

SpriteList::Sprite::Sprite(int index, int x, int y, int w, int h):
	index{index},
	position{x, y, w, h}
{
}

void
SpriteList::set_positions()
{
	this->positions.clear();

	int final_index;
	int y{0};

	if(this->set_indexes.size() - 1 == this->current_set)
		final_index = editor_state->frames.size() - 1;
	else
		final_index = this->set_indexes[this->current_set + 1] - 1;

	for(int i{this->set_indexes[this->current_set]}; i <= final_index; i++)
	{
		Box *sprite = &editor_state->frames[i].sprite;

		this->positions.emplace_back(
			i,
			core.window_width - sprite->size.w,
			y,
			sprite->size.w,
			sprite->size.h);

		y += sprite->size.h;
	}
}

void
SpriteList::next_set()
{
}

void
SpriteList::previous_set()
{
}

void
SpriteList::render()
{
	for(Sprite &sprite: this->positions)
	{
		SDL_RenderCopy(
			core.renderer, editor_state->texture,
			&editor_state->frames[sprite.index].sprite.size, &sprite.position);
	}
}

SpriteList::SpriteList():
	current_set{0},
	width{0},
	height{core.window_height}
{
	int index{0};
	int current_height{0};

	for(const Frame &frame: editor_state->frames)
	{
		if(frame.sprite.size.w > this->width) this->width = frame.sprite.size.w;

		if(current_height + frame.sprite.size.h > this->height)
		{
			this->set_indexes.emplace_back(index);
			current_height = 0;
		}

		index++;
		current_height += frame.sprite.size.h;
	}

	this->set_positions();
}
