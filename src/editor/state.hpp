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

#ifndef YAFCE_STATE_H
#define YAFCE_STATE_H 1

#include <functional>
#include <unordered_map>

#include "../common/core.hpp"

namespace State
{

class Base
{
protected:
	std::unordered_map<SDL_Keycode, std::function<void(void)>> key_map;

public:
  virtual void
  key_down(SDL_Keycode keycode);
  virtual void
  key_up(SDL_Keycode keycode);

  virtual void
  mouse_button_down(SDL_MouseButtonEvent& b){};
  virtual void
  mouse_button_up(SDL_MouseButtonEvent& b){};
  virtual void
  mouse_motion(int x, int y, int xrel, int yrel){};

	Base();
	virtual
	~Base(){};
};

}

#endif /* YAFCE_STATE_H */
