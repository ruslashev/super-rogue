#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string>

SDL_Surface* loadImage(std::string filename);
void applySurface(SDL_Surface* source, SDL_Surface* destination, int x, int y);