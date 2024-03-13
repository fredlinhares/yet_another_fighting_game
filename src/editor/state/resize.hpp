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

#ifndef YAFCE_STATE_RESIZE_H
#define YAFCE_STATE_RESIZE_H 1

#include "../button/zoomable.hpp"
#include "../frame.hpp"
#include "../mode.hpp"
#include "../state.hpp"

namespace State
{

struct Resize: public State::Base
{
	Mode::Base* const mode;
	Button::Zoomable* const zoomable;

	::Box* box;

  void (Resize::*vertical_move)(int num);
  void (Resize::*horizontal_move)(int num);

	void
	set_resize_move(Direction direction);

  void
  mouse_button_up(SDL_MouseButtonEvent& b);
  void
  mouse_motion(int x, int y, int xrel, int yrel);

  void
  up_corner(int y);
  void
  down_corner(int y);
  void
  left_corner(int x);
  void
  right_corner(int x);

	Resize(Mode::Base* mode, Button::Zoomable* zoomable);
};

}

#endif /* YAFCE_STATE_RESIZE_H */
