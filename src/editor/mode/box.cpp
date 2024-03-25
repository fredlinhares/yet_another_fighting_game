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
Box::set_boxes()
{
	this->boxes.clear();

	this->boxes.emplace_back(
		this, &this->sprite_box, &this->frame->head, 0x66, 0x66, 0xbb);
	this->boxes.emplace_back(
		this, &this->sprite_box, &this->frame->upper_body, 0x22, 0x22, 0x77);
	this->boxes.emplace_back(
		this, &this->sprite_box, &this->frame->lower_body, 0x44, 0x44, 0x99);
	this->boxes.emplace_back(
		this, &this->sprite_box, &this->frame->collision, 0x33, 0x99, 0x33);
}

void
Box::set_limits()
{
	this->sprite_box.up_limit = - this->frame->sprite.h * 2;
	this->sprite_box.down_limit = this->frame->sprite.h * 2;
	this->sprite_box.left_limit = - this->frame->sprite.w * 2;
	this->sprite_box.right_limit = this->frame->sprite.w * 2;
}

void
Box::render()
{
	this->sprite_box.render_sprite(*this->frame);
	this->sprite_box.render();
	this->sprite_box.render_pivot();
	this->sprite_list.render();
}

Box::Box():
	frame{&editor_state->frames[0]},
	box_state{this},
	sprite_list{[&](int index){
		this->frame = &editor_state->frames[index];
		this->set_boxes();
	}},
	sprite_box{
		this, &this->boxes,
		core.window_width - this->sprite_list.location.w, core.window_height,
		(core.window_width - this->sprite_list.location.w) / 2,
		(core.window_height/6)*5},
	Base{&this->box_state}
{
	this->buttons.emplace_back(&this->sprite_box);
	this->buttons.emplace_back(&this->sprite_list);

	this->set_boxes();
	this->set_limits();
}

Box::~Box()
{
	this->clear_state();
}

}
