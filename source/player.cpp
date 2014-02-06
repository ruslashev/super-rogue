#include "utils.hpp"
#include "player.hpp"

void Player::LoadImage(SDL_Renderer *sdlRenderer, const char *path)
{
	SDL_Surface *tempSurf = IMG_Load(path);
	assertf(tempSurf != NULL, "Failed to load image: %s", IMG_GetError());
	texture = SDL_CreateTextureFromSurface(sdlRenderer, tempSurf);
	assertf(texture != NULL, "Failed to create player's texture: %s", SDL_GetError());
	SDL_FreeSurface(tempSurf);
}

void Player::Draw(SDL_Renderer *sdlRenderer)
{
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, texture, NULL, NULL);
	SDL_RenderPresent(sdlRenderer);
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}

