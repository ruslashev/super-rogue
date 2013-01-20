#include "utils.hpp"

SDL_Surface* loadImage(std::string filename)
{
	SDL_Surface* loadedImage = NULL; 		//The image that's loaded
	SDL_Surface* optimizedImage = NULL; 	//The optimized image that will be used

	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if (loadedImage != NULL) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void applySurface(SDL_Surface* source, SDL_Surface* destination, int x, int y, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}