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
	
	while (1) {

		//rooms return 0 on death and 1 on success
		//die returns 0 on exit and 1 on restart
		if (!room1(mainWindow)) {
			if (die(mainWindow)) {
				continue;
			}
			else {
				Mix_Quit();
				SDL_DestroyWindow(mainWindow);
				SDL_Quit();
				exit(EXIT_SUCCESS);
			}
		}

		if (!room2(mainWindow)) {
			if (die(mainWindow)) {
				continue;
			}
			else {
				Mix_Quit();
				SDL_DestroyWindow(mainWindow);
				SDL_Quit();
				exit(EXIT_SUCCESS);
			}
		}

		if (!room3(mainWindow)) {
			if (die(mainWindow)) {
				continue;
			}
			else {
				Mix_Quit();
				SDL_DestroyWindow(mainWindow);
				SDL_Quit();
				exit(EXIT_SUCCESS);
			}
		}
		exit(EXIT_SUCCESS);
	}
}