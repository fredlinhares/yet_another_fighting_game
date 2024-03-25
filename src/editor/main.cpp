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

#include <iostream>

#include "../common/graphics/texture.hpp"
#include "main.hpp"

EditorState *editor_state;

namespace
{

void
load_texture(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	std::string texture_path{"./fighters/" + self->character + "/sprites.png"};
	self->texture = Graphics::Texture::load(texture_path.c_str());
}

void
unload_texture(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	SDL_DestroyTexture(self->texture);
}

void
load_direction_buttons(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	std::string texture_path{"./img/ui/directions.png"};
	self->tex_direction_buttons = Graphics::Texture::load(texture_path.c_str());
}

void
unload_direction_buttons(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	SDL_DestroyTexture(self->tex_direction_buttons);
}

void
load_frames(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	std::string frame_path{"./fighters/" + self->character + "/frames.conf"};
	Parse::frames(&self->frames, frame_path.c_str());
}

void
load_animations(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	std::string animations_path{
		"./fighters/" + self->character + "/animations.conf"};
	Parse::animations(&self->animations, animations_path.c_str(), true);
}

void
unload_animation(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	std::unordered_map<std::string, Graphics::Animation*>::iterator it;
	for(it = self->animations.begin(); it != self->animations.end(); it++)
		delete it->second;
}

void
load_font(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	// TODO: Usa a project's font.
	self->font = TTF_OpenFont("/usr/share/fonts/TTF/HanaMinA.ttf", 16);
}

void
unload_font(void *obj)
{
	auto self{static_cast<EditorState*>(obj)};

	TTF_CloseFont(self->font);
}

const CommandChain loader{
	{&load_texture, &unload_texture},
	{&load_direction_buttons, &unload_direction_buttons},
	{&load_frames, nullptr},
	{&load_animations, unload_animation},
	{&load_font, &unload_font}
};

}

EditorState::EditorState(const char* character):
	next_game_mode{nullptr},
	up_button{0, 0, 18, 18},
	down_button{18, 0, 18, 18},
	left_button{0, 18, 18, 18},
	right_button{18, 18, 18, 18},
	play_button{36, 0, 18, 18},
	pause_button{36, 18, 18, 18},
	plus_button{54, 0, 18, 18},
	minus_button{54, 18, 18, 18}
{
	this->character = character;

	loader.execute(this);
}

EditorState::~EditorState()
{
	loader.revert(this);
}

int
main(int argc, char *argv[])
{
  core.app_name = "Yet Another Fighting Character Editor";
  core.window_width = 1280;
  core.window_height = 720;
  core.init();

  { // Parse args
    if(argc < 2)
    {
      std::cout << "insufficient arguments." << std::endl;
      core.finish();
      return 1;
    }

		editor_state = new EditorState(argv[1]);
  }

	Mode::Base *game_mode = new Mode::Sprite{};

  { // main loop
    SDL_Event event;
    bool quit{false};
    auto frame_start = SDL_GetTicks();

    while(!quit)
    {
			// Change mode
			if(editor_state->next_game_mode != nullptr)
			{
				delete game_mode;
				game_mode = editor_state->next_game_mode;
				editor_state->next_game_mode = nullptr;
			}

      // Input processing
      while(SDL_PollEvent(&event))
      {
				switch(event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					game_mode->current_state()->key_down(event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					game_mode->current_state()->key_up(event.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					game_mode->current_state()->mouse_button_down(event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					game_mode->current_state()->mouse_button_up(event.button);
					break;
				case SDL_MOUSEMOTION:
					int x{event.motion.x};
					int y{event.motion.y};

					int xrel{event.motion.xrel};
					int yrel{event.motion.yrel};

					game_mode->current_state()->mouse_motion(x, y, xrel, yrel);
					break;
				}
      }

      // Update game
      game_mode->tick();

      { // Render
	SDL_SetRenderDrawColor(core.renderer, 0, 0, 0, 0xff);
	SDL_RenderClear(core.renderer);

	game_mode->render();

	SDL_RenderPresent(core.renderer);
      }

      timer(frame_start);
    }
  }

  delete game_mode;
  delete editor_state;
  core.finish();

  return 0;
}
