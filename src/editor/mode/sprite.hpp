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

#ifndef YAFCE_MODE_SPRITE_H
#define YAFCE_MODE_SPRITE_H 1

#include <vector>

#include "../mode.hpp"
#include "../sprite.hpp"
#include "../state/scroll.hpp"
#include "../state/sprite.hpp"

namespace Mode
{

class Sprite: public Base
{
  SDL_Texture* texture;
  SDL_Rect src_rect, dst_rect;
  int tex_width, tex_height;
  int display_width, display_height;
  int zoom;

  std::vector<::Sprite> sprites;

  void
  correct_position();

  void
  define_display_position();

public:
  State::Scroll scroll_state;
  State::Sprite sprite_state;

  void
  zoom_in();
  void
  zoom_out();

  void
  scroll(int x, int y);

  void
  add_sprite();

  void
  tick();
  void
  render();

  Sprite(SDL_Texture* texture);
};

}

#endif /* YAFCE_MODE_SPRITE_H */
