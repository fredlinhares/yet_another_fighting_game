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

#include "../main.hpp"

namespace Button
{

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
			y + editor_state->up_button.h,
			sprite->size.w,
			sprite->size.h);

		y += sprite->size.h;
	}
}

void
SpriteList::next_set()
{
	this->current_set++;
	if(this->current_set >= this->set_indexes.size())
		this->current_set = 0;
}

void
SpriteList::previous_set()
{
	this->current_set--;
	if(this->current_set < 0)
		this->current_set = this->set_indexes.size() - 1;
}

void
SpriteList::click_action(int x, int y)
{
	if(Button::Base::is_point_inside_rect(this->up_button, x, y))
	{
		this->previous_set();
		this->set_positions();
		return;
	}
	if(Button::Base::is_point_inside_rect(this->down_button, x, y))
	{
		this->next_set();
		this->set_positions();
		return;
	}

	for(Sprite &sprite: this->positions)
	{
		if(Button::Base::is_point_inside_rect(sprite.position, x, y))
		{
			*this->frame = &editor_state->frames[sprite.index];
			return;
		}
	}
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

	SDL_RenderCopy(
		core.renderer, editor_state->tex_direction_buttons,
		&editor_state->up_button, &this->up_button);
	SDL_RenderCopy(
		core.renderer, editor_state->tex_direction_buttons,
		&editor_state->down_button, &this->down_button);
}

SpriteList::SpriteList(Frame **frame):
	frame{frame},
	current_set{0},
	sprites_height{
		core.window_height -
		editor_state->up_button.h - editor_state->down_button.h},
	up_button{0, 0, 18, 18},
	down_button{0, core.window_height - 18, 18, 18}
{
	int index{0};
	int current_height{0};

	this->location.y = 0;
	this->location.w = 0;
	this->location.h = core.window_height;

	this->set_indexes.emplace_back(0);
	for(const Frame &frame: editor_state->frames)
	{
		if(frame.sprite.size.w > this->location.w)
			this->location.w = frame.sprite.size.w;

		if(current_height + frame.sprite.size.h > this->sprites_height)
		{
			this->set_indexes.emplace_back(index);
			current_height = 0;
		}

		index++;
		current_height += frame.sprite.size.h;
	}

	{
		this->location.x = core.window_width - this->location.w;
		int button_pos_x{
			core.window_width - this->location.w / 2 -
			editor_state->up_button.w / 2};
		this->up_button.x = button_pos_x;
		this->down_button.x = button_pos_x;
	}

	this->set_positions();
}

}
