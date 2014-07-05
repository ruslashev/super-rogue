#include "utils.hpp"
#include "player.hpp"

void Player::Draw(SDL_Renderer *sdlRenderer)
{
	SDL_RenderCopy(sdlRenderer, texture, NULL, NULL);
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}

