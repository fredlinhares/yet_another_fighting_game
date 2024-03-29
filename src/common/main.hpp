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

#ifndef YAFC_MAIN_H
#define YAFC_MAIN_H 1

#include "core.hpp"

constexpr int FRAMES_PER_SECOND = 60;
constexpr int MAX_FRAME_DURATION = 1000/FRAMES_PER_SECOND;

inline void
timer(Uint32 &frame_start)
{
  auto frame_stop = SDL_GetTicks();
  auto frame_duration = frame_stop - frame_start;

  // If frame take less time than maximum allowed.
  if(MAX_FRAME_DURATION > frame_duration)
    SDL_Delay(MAX_FRAME_DURATION - frame_duration);

  frame_start = frame_stop;
}

#endif /* YAFC_CORE_H */
