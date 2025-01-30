# Yet Another Fighting Games

This is an engine for fighting games.

## Dependencies

This engine is mainly developed on GNU/Linux with the GCC compiler and [Rake](https://ruby.github.io/rake/) for automation.
To compile in another platform, you should use an equivalent environment.
For Windows, you can use [MSYS2 com MINGW](https://www.msys2.org/).
For MacOS, you can use [Homebrew](https://brew.sh/).

### Windows (MSYS2)

MSYS2 provides several different environments; I recommend using `MSYS2 MINGW64`.
To install the dependencies, use the command:

```
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf ruby
```

After installing Ruby, use this command to install `Rake`:

```
gem install rake
```


### Arch Linux

To install the dependencies using pacman:

```
pacman -S gcc sdl2 sdl2_image sdl2_ttf ruby ruby-rake
```


### Debian Linux

There are some specific packages for development that you need to install as dependencies on top of normal dependencies:

```
apt install g++ libsdl2-2.0-0 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev ruby ruby-rake
```


## Compiling

Once you have everything installed, go to inside the project folder and run Rake:

```
rake
```

After compiling the game, try running it to check if everything is working properly:

```
./yafg
```


## Code Documentation

Once you finished compiling and the game is running properly, you can read about the game architecture:


[Main Loop](doc/main_loop.markdown)

[Game Modes](doc/game_mode.markdown)

[System Initialization](doc/subsystems_initialization.markdown)

[Characters](doc/characters.markdown)
