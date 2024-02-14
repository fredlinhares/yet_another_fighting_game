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

#ifndef YAFCE_SPRITE_H
#define YAFCE_SPRITE_H 1

#include "../common/core.hpp"
#include "../common/graphics/frame.hpp"

struct Sprite
{
  int outer_left, center_left, outer_right, center_right, outer_up,
    center_up, outer_down, center_down;
  SDL_Rect size;

  void
  update_box_size();

  Sprite(int x, int y, int w, int h);
  Sprite(const Graphics::Frame &frame);
};

#endif /* YAFCE_SPRITE_H */
