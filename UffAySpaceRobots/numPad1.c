#include "numPad1.h"

int numPad1() {

	int warnings = 0;

	//build window
	SDL_Window* popup;
	popup = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 900, SDL_WINDOW_BORDERLESS);
	if (popup == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}

	//set window mode
	if (0 != SDL_SetWindowFullscreen(popup, 0)) {
		fprintf(stderr, "Fullscreen not possible! SDL_Error: %s", SDL_GetError());
	}

	//show cursor
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);

	//create renderer
	SDL_Renderer* rendererPopup;
	rendererPopup = SDL_CreateRenderer(popup, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererPopup) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture* pad = loadImage("images/numpad/numpad.bmp", rendererPopup);

	//variables to track clicks
	SDL_Event keys;
	SDL_Keysym press;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;

	int x_button = 250;
	int y_button = 250;

	while (quit) {
		while (SDL_PollEvent(&keys)) {
			switch (keys.type) {

			case SDL_KEYDOWN:
				press = keys.key.keysym;

				if (SDLK_ESCAPE == press.sym) {

					quit = 0;
					SDL_DestroyWindow(popup);
					return 0;
				}


				//enter code
				if (SDLK_7 == press.sym || SDLK_KP_7 == press.sym) {

					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (SDLK_1 == press.sym || SDLK_KP_1 == press.sym) {
						keys.type = 0;
						keys = getKey(keys);
						press = keys.key.keysym;

						if (SDLK_3 == press.sym || SDLK_KP_3 == press.sym) {
							keys.type = 0;
							keys = getKey(keys);
							press = keys.key.keysym;

							if (SDLK_7 == press.sym || SDLK_KP_7 == press.sym) {
								keys.type = 0;
								keys = getKey(keys);
								press = keys.key.keysym;

								if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {

									SDL_DestroyRenderer(rendererPopup);
									SDL_DestroyWindow(popup);
									return 1;

								}
							}
						}
					}
				}

				if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
					Mix_PauseMusic();
					//warning returns 0 on death
					if (0 == warning(warnings)) {
						SDL_DestroyWindow(popup);
						return -1;
					}
					Mix_ResumeMusic();
					warnings++;
					break;
				}
				
				/*case SDL_MOUSEMOTION:
				x = mouse.motion.x - 1920;
				y = mouse.motion.y - 1080;
				break;*/

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
			SDL_RenderPresent(rendererPopup);
		}
	}
	//hide cursor and delete second one
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
}
