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

#ifndef YAFC_GRAPHICS_ANIMATION_H
#define YAFC_GRAPHICS_ANIMATION_H 1

#include <vector>

namespace Graphics
{

struct AnimationFrame
{
  int duration, index;
};

class Animation
{
  bool looping, sequence_over;
  int frame_index, time;
  std::vector<AnimationFrame> frames;

public:
  AnimationFrame*
  add_frame();

  void
  reset();

	void
	next_frame();

	void
	previous_frame();

  int
  tick();

  inline int
  index(){return this->frames[this->frame_index].index;};

  inline bool
  over(){return this->sequence_over;};

	inline auto
	size(){return this->frames.size();};

  Animation(bool looping, std::initializer_list<AnimationFrame> frames);
};

}

#endif /* YAFC_GRAPHICS_ANIMATION_H */
