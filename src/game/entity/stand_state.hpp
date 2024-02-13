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

#ifndef YAFG_ENTITY_STAND_STATE_H
#define YAFG_ENTITY_STAND_STATE_H 1

#include "../../common/graphics/animation.hpp"
#include "state.hpp"

namespace Entity
{

class StandState: public State
{
  Graphics::Animation animation;

public:

  void
  tick();

  StandState(Fighter *f);
};

}

#endif /* YAFG_ENTITY_STAND_STATE_H */
