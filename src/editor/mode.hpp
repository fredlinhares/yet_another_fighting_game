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

#ifndef YAFCE_MODE_H
#define YAFCE_MODE_H 1

#include "../common/core.hpp"
#include "state.hpp"

namespace Mode
{

class Base
{
	State::Base* const default_state;
	State::Base *_current_state;

public:
	void
	change_state(State::Base *state);

	void
	reset_state();

	void
	clear_state();

	inline State::Base*
	current_state() {return this->_current_state;};

  virtual void
  tick(){};

  virtual void
  render() = 0;

	Base(State::Base *default_state);

  virtual
  ~Base(){};
};

}


#endif /* YAFCE_MODE_H */
