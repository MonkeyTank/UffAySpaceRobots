#include "main.h"


int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Error, SDL could not be initialised because: \n");
		fprintf(stderr, SDL_GetError());
		return -1;
	}
	SDL_Quit();
	return 0;
}