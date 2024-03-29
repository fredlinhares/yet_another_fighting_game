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

#include "sprite.hpp"

#include "../../common/direction.hpp"
#include "../main.hpp"
#include "../mode/animation_list.hpp"
#include "../mode/sprite.hpp"
#include "../mode/box.hpp"

namespace State
{

void
Sprite::mouse_button_down(SDL_MouseButtonEvent& b)
{
	this->mode->change_state(new State::Scroll(this->mode));

	for(Button::Base *button: this->mode->buttons)
		if(button->is_clicked(b.x, b.y)) return;
}

Sprite::Sprite(Mode::Sprite* mode):
  mode{mode}
{
	key_map.insert({SDLK_e, [mode=this->mode](){
		mode->sprite_box.zoom_in();
		mode->zoom_in();
	}});
	key_map.insert({SDLK_d, [mode=this->mode](){
		mode->sprite_box.zoom_out();
		mode->zoom_out();
	}});
	key_map.insert({SDLK_n, [mode=this->mode](){mode->add_sprite();}});
}

}
