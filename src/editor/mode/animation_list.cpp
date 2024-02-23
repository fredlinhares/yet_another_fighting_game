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

#include "animation_list.hpp"

#include "../main.hpp"
#include <iostream>

namespace Mode
{

void
AnimationList::render()
{
	for(Button::Text &button: this->animation_buttons) button.render();
}

AnimationList::AnimationList():
	name_selection_state{this}
{
	int y{10};

	for(const auto & [key, value]: editor_state->animations)
	{
		this->animation_buttons.emplace_back(key.c_str(), 10, y, []() {
			std::cout << "clicked" << std::endl;
		});

		y += 10 + this->animation_buttons.back().src.h;
	}

	this->current_state = &this->name_selection_state;
}

}
