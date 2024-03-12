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

#include "animation.hpp"

namespace Graphics
{

AnimationFrame*
Animation::add_frame()
{
  this->frames.emplace_back();
  return &this->frames.back();
}

void
Animation::reset()
{
  this->frame_index = 0;
  this->time = 0;
  this->sequence_over = false;
}

void
Animation::next_frame()
{
	this->time = 0;
	this->frame_index++;

	if(this->frame_index >= frames.size())
	{
		if(this->looping)
			this->frame_index = 0;
		else
		{
			this->frame_index--;
			this->sequence_over = true;
		}
	}
}

void
Animation::previous_frame()
{
	this->time = 0;
	this->frame_index--;

	if(this->frame_index < 0) this->frame_index = frames.size() - 1;
}

int
Animation::tick()
{
  AnimationFrame *frame = &this->frames[this->frame_index];

  if(this->sequence_over) return this->frame_index;

  this->time++;

  if(this->time >= frame->duration) this->next_frame();

  return frame->index;
}

Animation::Animation(
  bool looping, std::initializer_list<AnimationFrame> frames):
  looping{looping},
  frames{frames}
{
  this->reset();
}

}
