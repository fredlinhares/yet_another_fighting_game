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

#include "box.hpp"

#include "../main.hpp"

namespace Mode
{

void
Box::get_mouse_position(int &x, int &y)
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	x = (mouse_x - this->zoomable.x) / this->zoomable.zoom();
	y = (mouse_y - this->zoomable.y) / this->zoomable.zoom();
}

void
Box::set_limits()
{
	this->zoomable.up_limit = - this->frame->sprite.size.h * 2;
	this->zoomable.down_limit = this->frame->sprite.size.h * 2;
	this->zoomable.left_limit = - this->frame->sprite.size.w * 2;
	this->zoomable.right_limit = this->frame->sprite.size.w * 2;
}

void
Box::default_state()
{
	this->current_state = &this->box_state;
}

void
Box::render()
{
	this->zoomable.render_sprite(*this->frame);

	this->zoomable.render_rect(this->frame->head.size, 0x66, 0x66, 0xbb);
	this->zoomable.render_rect(this->frame->upper_body.size, 0x22, 0x22, 0x77);
	this->zoomable.render_rect(this->frame->lower_body.size, 0x44, 0x44, 0x99);
	this->zoomable.render_rect(this->frame->collision.size, 0x33, 0x99, 0x33);

	this->sprite_list.render();
}

Box::Box():
	frame{&editor_state->frames[0]},
	box_state{this},
	resize_state{this, &this->zoomable},
	sprite_list{&this->frame},
	zoomable{
		0, 0,
		core.window_width - this->sprite_list.location.w, core.window_height,
		(core.window_width - this->sprite_list.location.w) / 2,
		(core.window_height/6)*5}
{
	this->current_state = &this->box_state;
	this->set_limits();
}

}
