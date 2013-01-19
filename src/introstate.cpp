#include "gameengine.hpp"

#include "introstate.hpp"
#include "playstate.hpp"

IntroState IntroState::m_IntroState;

void IntroState::Init()
{
	font = TTF_OpenFont("DroidSans.ttf", 40);
}

void IntroState::Cleanup()
{
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}

void IntroState::Pause()
{

}

void IntroState::Resume()
{
	
}

void IntroState::HandleEvents(GameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						game->ChangeState(PlayState::Instance());
						break;

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

void IntroState::Update(GameEngine* game) 
{

}

void IntroState::Draw(GameEngine* game) 
{
	SDL_Color textColor = { 255, 255, 255 };
	textSurface = TTF_RenderText_Solid(font, "Super rogue", textColor);

	SDL_BlitSurface(textSurface, NULL, game->screen, NULL);

	SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}
