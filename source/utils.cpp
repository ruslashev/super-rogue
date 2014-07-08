#include "utils.hpp"

void assertf(bool condition, const char *format, ...)
{
#ifndef RELEASE
	if (!condition) {
		char output[512];
		va_list args;
		va_start(args, format);
		vsnprintf(output, 512, format, args);
		va_end(args);
		std::string outputStr = output;
		outputStr += '\n';
		throw std::runtime_error(outputStr);
	}
#endif
}

void LoadImage(SDL_Renderer *rend, const char *path, SDL_Texture **outTexture)
{
	SDL_Surface *tempSurf = IMG_Load(path);
	assertf(tempSurf != NULL, "Failed to load image \"%s\": %s", path, IMG_GetError());

	*outTexture = SDL_CreateTextureFromSurface(rend, tempSurf);
	assertf(outTexture != NULL, "Failed to create texture: %s", SDL_GetError());

	SDL_FreeSurface(tempSurf);
}

double lerp(double a, double b, double t)
{
	return (1 - t)*a + t*b;
}

double clamp(double n, double min, double max)
{
    n = n > max ? max : n;
    return n < min ? min : n;
}
