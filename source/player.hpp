#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player
{
	SDL_Texture *texture;

public:
	void LoadImage(SDL_Renderer *sdlRenderer, const char *path);
	void Draw(SDL_Renderer *sdlRenderer);
	~Player();
};

#endif

