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

struct Sprite
{
  SDL_Rect size;
  SDL_Rect edit_box, resize_up_box, resize_down_box, resize_left_box,
    resize_right_box, resize_up_right_box, resize_up_left_box,
    resize_down_right_box, resize_down_left_box;

  void
  update_box_size();

  Sprite(int x, int y, int w, int h);
};

#endif /* YAFCE_SPRITE_H */