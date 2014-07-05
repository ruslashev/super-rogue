#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>
#include <cstdarg>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void assertf(bool condition, const char *format, ...);
void LoadImage(SDL_Renderer *rend, const char *path, SDL_Texture **outTexture);

#endif

