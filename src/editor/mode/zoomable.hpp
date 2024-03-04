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

#ifndef YAFCE_MODE_ZOOMABLE_H
#define YAFCE_MODE_ZOOMABLE_H 1

#include "../frame.hpp"
#include "../../common/core.hpp"

namespace Mode
{

class Zoomable
{
protected:
  int zoom;

public:
	virtual int
	x() const = 0;
	virtual int
	y() const = 0;

	virtual int
	up_limit() const = 0;
	virtual int
	down_limit() const = 0;
	virtual int
	left_limit() const = 0;
	virtual int
	right_limit() const = 0;

	virtual void
	default_state() = 0;

  inline int
  zoom_level(){return this->zoom;};

	void
	render_sprite(const Frame &frame);

	void
	render_rect(const SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b);
};

}

#endif /* YAFCE_MODE_ZOOMABLE_H */
