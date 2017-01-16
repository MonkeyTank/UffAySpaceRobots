#include "main.h"

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Error, SDL could not be initialised because: \n");
		fprintf(stderr, SDL_GetError());
		return -1;
	}

	SDL_Window* mainWindow;
	mainWindow = SDL_CreateWindow("mainWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_BORDERLESS);
	if (mainWindow == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}

	room1(mainWindow);

	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	return 0;
}