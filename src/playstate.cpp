#include "gameengine.hpp"

#include "playstate.hpp"

PlayState PlayState::m_PlayState;

bool PlayState::Init()
{
	font = TTF_OpenFont("DroidSans.ttf", 30);	
	if (!font)
		return false;

	return true;
}

void PlayState::Cleanup()
{
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
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
						break;
				}
				break;
		}
	}
}

void PlayState::Update(GameEngine* game)
{

}

void PlayState::Draw(GameEngine* game)
{
	SDL_Color textColor = { 255, 0, 0 };
	textSurface = TTF_RenderText_Solid(font, "Poopy butts", textColor);

	SDL_BlitSurface(textSurface, NULL, game->screen, NULL);

	SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}
