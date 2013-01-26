#include "utils.hpp"

SDL_Surface* loadImage(std::string filename)
{
	SDL_Surface* loadedImage = NULL; 		//The image that's loaded
	SDL_Surface* optimizedImage = NULL; 	//The optimized image that will be used

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

		SDL_FreeSurface(loadedImage);
	} else {
		fprintf(stderr, "Failed to load image file: %s\n", filename.c_str());
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