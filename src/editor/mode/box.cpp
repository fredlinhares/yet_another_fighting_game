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

	this->boxes.emplace_back(&this->frame->head);
	this->boxes.emplace_back(&this->frame->upper_body);
	this->boxes.emplace_back(&this->frame->lower_body);
	this->boxes.emplace_back(&this->frame->collision);
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
	sprite_list{[&](int index){
		this->frame = &editor_state->frames[index];
		this->set_boxes();
	}},
	zoomable{
		this, &this->boxes,
		core.window_width - this->sprite_list.location.w, core.window_height,
		(core.window_width - this->sprite_list.location.w) / 2,
		(core.window_height/6)*5},
	Base{&this->box_state}
{
	this->buttons.emplace_back(&this->zoomable);
	this->buttons.emplace_back(&this->sprite_list);

	this->set_boxes();
	this->set_limits();
}

Box::~Box()
{
	this->clear_state();
}

}
