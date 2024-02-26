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

#include "click_button.hpp"

namespace State
{

void
ClickButton::key_down(SDL_Keycode keycode)
{
}

void
ClickButton::mouse_button_down(SDL_MouseButtonEvent &b)
{
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);

	for(Button::Base *button: *this->buttons)
	{
		if(mouse_x > button->location.x &&
			 mouse_x < button->location.x + button->location.w &&
			 mouse_y > button->location.y &&
			 mouse_y < button->location.y + button->location.h)
		{
			button->click();
			break;
		}
	}
}

ClickButton::ClickButton(std::vector<Button::Base*> *buttons):
	buttons{buttons}
{
}

}
