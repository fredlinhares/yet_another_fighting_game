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

#include "frame.hpp"

void
Frame::set_sprite(int x, int y, int w, int h)
{
  this->sprite.size.x = x;
  this->sprite.size.y = y;
  this->sprite.size.w = w;
  this->sprite.size.h = h;
	this->sprite.update_size();
}

void
Frame::set_head(int x, int y, int w, int h)
{
  this->head.size.x = x;
  this->head.size.y = y;
  this->head.size.w = w;
  this->head.size.h = h;
	this->head.update_size();
}

void
Frame::set_upper_body(int x, int y, int w, int h)
{
  this->upper_body.size.x = x;
  this->upper_body.size.y = y;
  this->upper_body.size.w = w;
  this->upper_body.size.h = h;
	this->upper_body.update_size();
}

void
Frame::set_lower_body(int x, int y, int w, int h)
{
  this->lower_body.size.x = x;
  this->lower_body.size.y = y;
  this->lower_body.size.w = w;
  this->lower_body.size.h = h;
	this->lower_body.update_size();
}

void
Frame::set_collision(int x, int y, int w, int h)
{
  this->collision.size.x = x;
  this->collision.size.y = y;
  this->collision.size.w = w;
  this->collision.size.h = h;
	this->collision.update_size();
}

Frame::Frame(const Graphics::Frame &frame):
	x{frame.x},
	y{frame.y},
  sprite{frame.sprite.x, frame.sprite.y, frame.sprite.w, frame.sprite.h},
  head{frame.head.x, frame.head.y, frame.head.w, frame.head.h},
  upper_body{
		frame.upper_body.x, frame.upper_body.y, frame.upper_body.w,
		frame.upper_body.h},
  lower_body{
		frame.lower_body.x, frame.lower_body.y, frame.lower_body.w,
		frame.lower_body.h},
  collision{
		frame.collision.x, frame.collision.y, frame.collision.w, frame.collision.h}
{
}

Frame::Frame(int x, int y, int w, int h):
	x{0},
	y{0},
	sprite{x, y, w, h},
	head{x, y, w, h},
	upper_body{x, y, w, h},
	lower_body{x, y, w, h},
	collision{x, y, w, h}
{
}
