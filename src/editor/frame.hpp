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

#ifndef YAFCE_FRAME_H
#define YAFCE_FRAME_H 1

#include "box.hpp"

struct Frame
{
	// The position of the sprites are relative to the pivot.
  int x, y;
  Box sprite, head, upper_body, lower_body, collision;

  void
  set_sprite(int x, int y, int w, int h);
  void
  set_head(int x, int y, int w, int h);
  void
  set_upper_body(int x, int y, int w, int h);
  void
  set_lower_body(int x, int y, int w, int h);
  void
  set_collision(int x, int y, int w, int h);

  Frame(const Graphics::Frame &frame);
	Frame(int x, int y, int w, int h);
};

#endif /* YAFCE_FRAME_H */
