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
#include "../common/main.hpp"
#include "mode/sprite.hpp"

int
main(int argc, char *argv[])
{
  core.app_name = "Yet Another Fighting Character Editor";
  core.window_width = 1280;
  core.window_height = 720;
  core.init();

  SDL_Texture* sprites;
  { // Parse args
    if(argc < 2)
    {
      std::cout << "insufficient arguments." << std::endl;
      core.finish();
      return 1;
    }

    sprites = Graphics::Texture::load(argv[1]);
  }

  Mode::Base *game_mode = new Mode::Sprite{sprites};

  main_loop(game_mode);

  delete game_mode;
  SDL_DestroyTexture(sprites);
  core.finish();

  return 0;
}
