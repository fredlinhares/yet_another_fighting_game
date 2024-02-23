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

#ifndef YAFCE_MAIN_H
#define YAFCE_MAIN_H 1

#include <string>
#include <unordered_map>

#include "../common/graphics/animation.hpp"
#include "../common/main.hpp"
#include "../common/parser.hpp"
#include "mode/sprite.hpp"

struct EditorState
{
	Mode::Base *next_game_mode;

  std::string character;
  SDL_Texture *texture;
	TTF_Font *font;
	std::vector<Sprite> sprites;
	std::unordered_map<std::string, Graphics::Animation*> animations;

	EditorState(const char* character);
	~EditorState();
};

extern EditorState *editor_state;

#endif /* YAFCE_MAIN_H */
