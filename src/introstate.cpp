#include "gameengine.hpp"

#include "introstate.hpp"
#include "playstate.hpp"

IntroState IntroState::m_IntroState;

bool IntroState::Init()
{
	font = TTF_OpenFont("DroidSans.ttf", 60);
	if (!font)
		return false;

	return true;
}

void IntroState::Update(GameEngine* game)
{

}

void IntroState::Draw(GameEngine* game)
{
	SDL_FillRect(game->screen, 0, SDL_MapRGB(game->screen->format, 0, 0, 0));

	if (SDL_MUSTLOCK(game->screen))
		if (SDL_LockSurface(game->screen) < 0)
			return;

	int w;
	TTF_SizeText(font, "Super rogue", &w, NULL);
	textSurface = TTF_RenderText_Shaded(font, "Super rogue", SDL_Color{255, 255, 255}, SDL_Color{20, 20, 20});

	applySurface(textSurface, game->screen, 400-w/2, 120, NULL);


	if (SDL_MUSTLOCK(game->screen))
		SDL_UnlockSurface(game->screen);

	SDL_Flip(game->screen);
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
