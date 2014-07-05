#include "entity.hpp"

void Entity::LoadImage(SDL_Renderer *sdlRenderer, const char *path)
{
	SDL_Surface *tempSurf = IMG_Load(path);
	assertf(tempSurf != NULL, "Failed to load image \"%s\": %s", path, IMG_GetError());
	texture = SDL_CreateTextureFromSurface(sdlRenderer, tempSurf);
	assertf(texture != NULL, "Failed to create texture: %s", SDL_GetError());
	SDL_FreeSurface(tempSurf);
}

