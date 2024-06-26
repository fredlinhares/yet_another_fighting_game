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

#include "parser.hpp"

#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <regex>
#include <string>

namespace
{
  const std::regex re_title_num{"^\\[([0-9]+)\\]$"};
  const std::regex re_title_text{"^\\[([a-zA-Z_]+)\\]$"};
  const std::regex re_key_value{"^([a-zA-Z_]+)\\s*=\\s*([0-9a-zA-Z,\\-\\s]+)$"};
  const std::regex re_number{"\\s*(\\-*[0-9]+)\\s*"};
  const std::regex re_number_sequence{"\\s*(\\-*[0-9]+)[\\s,]*"};
  const std::regex re_frame{"^\\s*frame\\s*$"};
  const std::regex re_comment{"^\\s*#"};
  const std::regex re_empty{"^\\s*$"};

  void
  extract_numbers(int *nums, const int quantity, const char *string)
  {
    int index{0};
    std::smatch match;
    std::string text{string};

    while(std::regex_search(text, match, re_number_sequence))
    {
      nums[index] = std::atoi(match[1].str().c_str());

      index++;
      if(index > quantity) break;
      text = match.suffix().str();
    }
  }

void
throw_parsing_error(const char *file, int line)
{
  std::string error{"Error while parsing file: \""};
  error += file;
  error += "\" on line: ";
  error += std::to_string(line);
  error += ".";
  throw std::runtime_error{error};
}

}

namespace Parse
{

void
frames(std::vector<Graphics::Frame> *frames, const char *file_name)
{
  std::ifstream input{file_name};

  // In a malformed frame file, it can write attributes before defining a valid
  // frame. To prevent segmentation fault, the unused data goes to this frame.
  Graphics::Frame unused_frame{};
  Graphics::Frame *current_frame{&unused_frame};

  int num_line = 0;
  std::smatch match;
  for(std::string line; std::getline(input, line);)
  {
    num_line++;

    if(std::regex_match(line, match, re_key_value))
    {
      int nums[6];
      const char *key{match[1].str().c_str()};

      if(std::strcmp(key, "sprite") == 0)
      {
	extract_numbers(nums, 6, match[2].str().c_str());
	current_frame->set_sprite(
	  nums[0], nums[1], nums[2], nums[3], nums[4], nums[5]);
      }
      else if(std::strcmp(key, "head") == 0)
      {
	extract_numbers(nums, 4, match[2].str().c_str());
	current_frame->set_head(nums[0], nums[1], nums[2], nums[3]);
      }
      else if(std::strcmp(key, "upper_body") == 0)
      {
	extract_numbers(nums, 4, match[2].str().c_str());
	current_frame->set_upper_body(nums[0], nums[1], nums[2], nums[3]);
      }
      else if(std::strcmp(key, "lower_body") == 0)
      {
	extract_numbers(nums, 4, match[2].str().c_str());
	current_frame->set_lower_body(nums[0], nums[1], nums[2], nums[3]);
      }
      else if(std::strcmp(key, "collision") == 0)
      {
	extract_numbers(nums, 4, match[2].str().c_str());
	current_frame->set_collision(nums[0], nums[1], nums[2], nums[3]);
      }
    }
    else if(std::regex_match(line, match, re_title_num))
    {
      int index{std::atoi(match[1].str().c_str())};
      if(frames->size() < index + 1) frames->resize(index + 1);
      current_frame = &frames->at(index);
    }
    else if(std::regex_match(line, match, re_comment))
      continue;
    else if(std::regex_match(line, match, re_empty))
      continue;
    else
      throw_parsing_error(file_name, num_line);
  }
}

void
animations(
	std::unordered_map<std::string, Graphics::Animation*> *animations,
	const char *file_name, bool create_animation)
{
	std::ifstream input{file_name};

	// In a malformed frame file, it can write attributes before defining a valid
	// frame. To prevent segmentation fault, the unused data goes to this frame.
	Graphics::Animation unused_animation{false, {}};
	Graphics::Animation *current_animation{&unused_animation};

	Graphics::AnimationFrame unused_frame{};
	Graphics::AnimationFrame *current_frame{&unused_frame};

	int num_line = 0;
	std::smatch match;
	for(std::string line; std::getline(input, line);)
	{
		num_line++;

		if(std::regex_match(line, match, re_key_value))
		{
			const char *key{match[1].str().c_str()};

			if(std::strcmp(key, "duration") == 0)
				current_frame->duration = std::atoi(match[2].str().c_str());
			else if(std::strcmp(key, "index") == 0)
				current_frame->index = std::atoi(match[2].str().c_str());
		}
		else if(std::regex_match(line, match, re_frame))
		{
			current_frame = current_animation->add_frame();
		}
		else if(std::regex_match(line, match, re_title_text))
		{
			const char *title{match[1].str().c_str()};

			if(animations->contains(title))
				current_animation = animations->at(title);
			else if(create_animation == true)
			{
				animations->insert({title, new Graphics::Animation(true, {})});
				current_animation = animations->at(title);
			}
			else
				current_animation = &unused_animation;

			current_frame = &unused_frame;
		}
		else if(std::regex_match(line, match, re_comment))
			continue;
		else if(std::regex_match(line, match, re_empty))
			continue;
		else
			throw_parsing_error(file_name, num_line);
	}
}

}
