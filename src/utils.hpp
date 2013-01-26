#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <string>
#include <set>
#include <iostream>

using namespace std;

SDL_Surface* loadImage(std::string filename);
void applySurface(SDL_Surface* source, SDL_Surface* destination, int x, int y, SDL_Rect* clip);

struct AABB
{
	int x, y, width, height;
};

#endif