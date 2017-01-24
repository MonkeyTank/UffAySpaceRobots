#include "main.h"

int main(int argc, char **argv) {

	int esc = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Error, SDL could not be initialised because: \n");
		fprintf(stderr, SDL_GetError());
		return -1;
	}

	SDL_Window *mainWindow;
	mainWindow = SDL_CreateWindow("mainWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_BORDERLESS);
	if (mainWindow == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}
	
	while (1) {

		//rooms return 0 on death, 1 on success and -1 on quit
		//die returns 0 on exit and 1 on restart

		esc = room1(mainWindow);

		if (!esc) {
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
		else if (-1 == esc) {
			Mix_Quit();
			SDL_DestroyWindow(mainWindow);
			SDL_Quit();
			exit(EXIT_SUCCESS);
		}

		esc = room2(mainWindow);

		if (!esc) {
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
		else if (-1 == esc) {
			Mix_Quit();
			SDL_DestroyWindow(mainWindow);
			SDL_Quit();
			exit(EXIT_SUCCESS);
		}

		esc = room3(mainWindow);

		if (!esc) {
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
		else if (-1 == esc) {
			Mix_Quit();
			SDL_DestroyWindow(mainWindow);
			SDL_Quit();
			exit(EXIT_SUCCESS);
		}
		flashback("text/flashback4.txt");
		exit(EXIT_SUCCESS);
	}
}