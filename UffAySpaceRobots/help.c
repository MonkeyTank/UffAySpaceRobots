#include "help.h"

void help(SDL_Window *mainWindow, SDL_Renderer *rendererPopup) {

	SDL_Texture *pad = loadImage("images/tutorial.bmp", rendererPopup);

	//variables to track clicks
	SDL_Event keys;
	SDL_Keysym press;


	while (1) {
		while (SDL_PollEvent(&keys)) {
			switch (keys.type) {

			case SDL_KEYDOWN:
				press = keys.key.keysym;

				if (SDLK_ESCAPE == press.sym) {

					SDL_DestroyTexture(pad);
					return;
				}

				if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {

					SDL_DestroyTexture(pad);
					return;
				}

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
			SDL_RenderPresent(rendererPopup);
		}
	}
}
