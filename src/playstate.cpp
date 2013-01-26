#include "gameengine.hpp"

#include "playstate.hpp"

PlayState PlayState::m_PlayState;

const unsigned char PlayState::gamemap[10][10] = {
	{3,3,3,3,3,3,3,3,3,3},
	{3,0,0,0,0,2,2,0,0,3},
	{3,0,1,0,2,4,4,2,0,3},
	{3,1,1,1,0,2,2,4,2,3},
	{3,1,1,0,0,2,2,4,2,3},
	{3,0,0,0,2,3,3,3,4,3},
	{3,0,0,0,2,3,4,4,4,3},
	{3,0,0,0,2,3,3,3,4,3},
	{3,0,0,0,0,2,2,3,4,3},
	{3,3,3,3,3,3,3,3,3,3}
};

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

	knight.FromImage("knight.png");
	knight.SetPosition(AABB { 32, 32, 30, 30 } );

	return true;
}

void PlayState::Update(GameEngine* game) 
{

}

void PlayState::Draw(GameEngine* game) 
{
	SDL_FillRect(game->screen, 0, SDL_MapRGB(game->screen->format, 0, 0, 0));

	if (SDL_MUSTLOCK(game->screen)) {
		if (SDL_LockSurface(game->screen) < 0) {
			fprintf(stderr, "Failed to lock screen surface: %s\n", SDL_GetError());
			return;
		}
	}

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			applySurface(tilemap, game->screen, x*32, y*32, &tiles[gamemap[y][x]]);
		}
	}

	for (std::vector<Entity*>::iterator e = m_Entities.begin(); e != m_Entities.end(); e++)
	{
		(*e)->Draw(game->screen);
	}
	knight.Draw(game->screen);

	SDL_UnlockSurface(game->screen);
	SDL_UpdateRect(game->screen, 0, 0, 0, 0);
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
