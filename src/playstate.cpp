#include "gameengine.hpp"

#include "playstate.hpp"

PlayState PlayState::m_PlayState;

bool PlayState::Init()
{
	for (int i = 0; i < 5; i++)
	{
		tiles[i].x = 32*i;
		tiles[i].y = 0;
		tiles[i].w = 32;
		tiles[i].h = 32;
	}
	
	tilemap = loadImage("tiles.png");

	return true;
}

void PlayState::Update(GameEngine* game) 
{

}

void PlayState::Draw(GameEngine* game) 
{
	SDL_FillRect(game->screen, 0, SDL_MapRGB(game->screen->format, 0, 0, 0));

	if (SDL_MUSTLOCK(game->screen))
		if (SDL_LockSurface(game->screen) < 0)
			return;

	applySurface(tilemap, game->screen, 20, 20);

	if (SDL_MUSTLOCK(game->screen))
		SDL_UnlockSurface(game->screen);

	SDL_Flip(game->screen);
}

void PlayState::Cleanup()
{
	SDL_FreeSurface(tilemap);
}

void PlayState::Pause()
{

}

void PlayState::Resume()
{
	
}

void PlayState::HandleEvents(GameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game->Quit();
						break;

					default:
						// stop yelling at me gcc
						break;
				}
				break;
		}
	}
}
