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
#include "mode/sprite.hpp"

EditorState *editor_state;

int
main(int argc, char *argv[])
{
  core.app_name = "Yet Another Fighting Character Editor";
  core.window_width = 1280;
  core.window_height = 720;
  core.init();

  editor_state = new EditorState();

  SDL_Texture* sprites;
  { // Parse args
    if(argc < 2)
    {
      std::cout << "insufficient arguments." << std::endl;
      core.finish();
      return 1;
    }

    editor_state->character = argv[1];
    std::string texture_path{
      "./fighters/" + editor_state->character + "/sprites.png"};
    editor_state->texture = Graphics::Texture::load(texture_path.c_str());
  }

  Mode::Base *game_mode = new Mode::Sprite{};

  { // main loop
    SDL_Event event;
    bool quit{false};
    auto frame_start = SDL_GetTicks();

    while(!quit)
    {
      // Input processing
      while(SDL_PollEvent(&event))
      {
	switch(event.type)
	{
	case SDL_QUIT:
	  quit = true;
	  break;
	case SDL_KEYDOWN:
	  game_mode->current_state->key_down(event.key.keysym.sym);
	  break;
	case SDL_KEYUP:
	  game_mode->current_state->key_up(event.key.keysym.sym);
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  game_mode->current_state->mouse_button_down(event.button);
	  break;
	case SDL_MOUSEBUTTONUP:
	  game_mode->current_state->mouse_button_up(event.button);
	  break;
	case SDL_MOUSEMOTION:
	  int x{event.motion.x};
	  int y{event.motion.y};

	  int xrel{event.motion.xrel};
	  int yrel{event.motion.yrel};

	  game_mode->current_state->mouse_motion(x, y, xrel, yrel);
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
  SDL_DestroyTexture(editor_state->texture);
  delete editor_state;
  core.finish();

  return 0;
}
