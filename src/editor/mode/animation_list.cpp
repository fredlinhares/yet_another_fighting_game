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
#include "animation.hpp"

namespace Mode
{

void
AnimationList::render()
{
	for(Button::Base *button: this->buttons) button->render();
}

AnimationList::AnimationList():
	click_button_state{&this->buttons}
{
	int y{10};

	for(const auto & [key, value]: editor_state->animations)
	{
		Button::Text* button{new Button::Text{key.c_str(), 10, y, [name = key]() {
			editor_state->next_game_mode = new Mode::Animation{name.c_str()};
		}}};
		this->buttons.push_back(button);

		y += 10 + button->location.h;
	}

	this->current_state = &this->click_button_state;
}

AnimationList::~AnimationList()
{
	for(Button::Base* button: this->buttons) delete button;
}

}
