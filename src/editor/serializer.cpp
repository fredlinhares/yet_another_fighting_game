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

#include "serializer.hpp"

#include <fstream>
#include <stdexcept>

namespace
{

inline void
write_rect(std::ofstream &output, const SDL_Rect &rect)
{
	output << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h <<
		std::endl;
}

}

namespace Serializer
{

void
frames(const std::vector<Graphics::Frame> *frames, const char *file_name)
{
  std::ofstream output{file_name};
	if(!output.is_open())
		throw std::runtime_error("failed to open frames file");

	int index{0};
	for(const Graphics::Frame &frame: *frames)
	{
		output << "[" << index << "]" << std::endl;

		output << "sprite = " << frame.x << ", " << frame.y << ", ";
		write_rect(output, frame.sprite);

		output << "head = ";
		write_rect(output, frame.head);

		output << "upper_body = ";
		write_rect(output, frame.upper_body);

		output << "lower_body = ";
		write_rect(output, frame.lower_body);

		output << "collision = ";
		write_rect(output, frame.collision);

		output << std::endl;
		index++;
	}
}

void
animations(
	const std::unordered_map<std::string, Graphics::Animation*> *animations,
	const char *file_name)
{
  std::ofstream output{file_name};
	if(!output.is_open())
		throw std::runtime_error("failed to open animations file");

	for(const auto & [name, animation]: *animations)
	{
		output << "[" << name << "]" << std::endl;

		for(auto frame: animation->frames)
		{
			output << "frame" << std::endl;
			output << "duration = " << frame.duration << std::endl;
			output << "index = " << frame.index << std::endl;
			output << std::endl;
		}
	}
}

}
