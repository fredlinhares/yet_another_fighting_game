# Copyright 2024 Frederico de Oliveira Linhares
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

require 'rake/clean'

OBJ = 'yafg'

CPP_H_FILES = FileList[
  'src/**/*.hpp'
]
CPP_FILES = FileList[
  'src/**/*.cpp'
]
CPP_OBJS = CPP_FILES.ext('.o')

LIBRARIES = [
  'SDL2',
  'SDL2_image',
]

CLEAN.include(
  FileList[
    'src/**/*.o',
  ]
)

rule '.o' => ['.cpp'] do |t|
  system("g++ #{t.source} -o #{t.name} -g -c -std=c++23")
end

task build: CPP_OBJS do
  libs = LIBRARIES.inject('') {_1 + "-l#{_2} "}

  system("g++ -o #{OBJ} #{CPP_OBJS} #{libs}")
end

task default: %[build]
