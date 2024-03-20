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

#ifndef YAFCE_BUTTON_ANIMATION_CONTROLLER_H
#define YAFCE_BUTTON_ANIMATION_CONTROLLER_H 1

#include "../../common/graphics/animation.hpp"
#include "../button.hpp"
#include "../number.hpp"
#include "image.hpp"

namespace Mode
{
	class Animation;
};

namespace Button
{

class AnimationController: public Base
{
	Mode::Animation* const animation_mode;
	Number numbers;
	Image previous_frame_btn, next_frame_btn, play_btn, pause_btn, plus_btn,
		minus_btn;
	std::vector<Base*> buttons;

public:

	void
	click_action(int x, int y);

	void
	render();

	AnimationController(Mode::Animation *animation_mode);
};

}

#endif /* YAFCE_BUTTON_ANIMATION_CONTROLLER_H */
