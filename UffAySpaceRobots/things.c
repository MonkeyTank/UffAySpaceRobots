#include "things.h"

void things() {

	//build window
	SDL_Window *popup;
	popup = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1980, 1080, SDL_WINDOW_BORDERLESS);
	if (popup == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}

	//set window size
	if (0 != SDL_SetWindowFullscreen(popup, 0)) {
		fprintf(stderr, "Fullscreen not possible! SDL_Error: %s", SDL_GetError());
	}

	//show cursor in window
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);

	//build renderer
	SDL_Renderer *rendererPopup;
	rendererPopup = SDL_CreateRenderer(popup, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererPopup) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}

	//build texture background
	SDL_Texture *pad = loadImage("images/room2/ratsel/dinge.bmp", rendererPopup);
	SDL_Texture *error = loadImage("images/room2/ratsel/dinge_idiot.bmp", rendererPopup);
	SDL_Texture *success = loadImage("images/room2/ratsel/dinge_success.bmp", rendererPopup);
	SDL_Texture *hint = loadImage("images/room2/ratsel/dinge_hint.bmp", rendererPopup);

	//build texture back arrow
	SDL_Texture *arrow = loadColorKeyImage("images/backArrow.bmp", rendererPopup, 0xFF, 0xFF, 0xFF);

	//variables to track clicks
	SDL_Event keys;
	SDL_Keysym press;

	//int x = 450;
	//int y = 450;
	int x_button = 0;
	int y_button = 0;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;

	//set dimensions for backArrow hitbox
	SDL_Rect dimensions;

	dimensions.x = 1870;
	dimensions.y = 1030;
	dimensions.w = 50;
	dimensions.h = 50;

	while (quit) {
		while (SDL_PollEvent(&keys)) {

			switch (keys.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = keys.button.x;
				y_button = keys.button.y;

				//click on backArrow hitbox -> exit panel Anagram
				if (XYInRect(dimensions, x_button, y_button)) {

					quit = 0;
				}
				break;

			case SDL_KEYDOWN:
				press = keys.key.keysym;

				//hit esc -> exit panel Anagram
				if (SDLK_ESCAPE == press.sym) {

					quit = 0;
					break;
				}

				//enter right code
				if (SDLK_3 == press.sym || SDLK_KP_3 == press.sym) {

					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (SDLK_9 == press.sym || SDLK_KP_9 == press.sym) {
						keys.type = 0;
						keys = getKey(keys);
						press = keys.key.keysym;

						if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
							SDL_RenderClear(rendererPopup);
							SDL_RenderCopy(rendererPopup, success, NULL, NULL);
							SDL_RenderPresent(rendererPopup);
							SDL_Delay(3000);
							break;

						}
						else {
							SDL_RenderClear(rendererPopup);
							SDL_RenderCopy(rendererPopup, error, NULL, NULL);
							SDL_RenderPresent(rendererPopup);
							SDL_Delay(2000);
							break;
						}
					}
					else {
						SDL_RenderClear(rendererPopup);
						SDL_RenderCopy(rendererPopup, error, NULL, NULL);
						SDL_RenderPresent(rendererPopup);
						SDL_Delay(2000);
						break;
					}
				}

				//enter semi rigth code
				else if (SDLK_2 == press.sym || SDLK_KP_2 == press.sym) {
					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (SDLK_8 == press.sym || SDLK_KP_8 == press.sym) {
						keys.type = 0;
						keys = getKey(keys);
						press = keys.key.keysym;

						if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
							SDL_RenderClear(rendererPopup);
							SDL_RenderCopy(rendererPopup, hint, NULL, NULL);
							SDL_RenderPresent(rendererPopup);
							SDL_Delay(3000);
							break;

						}
						else {
							SDL_RenderClear(rendererPopup);
							SDL_RenderCopy(rendererPopup, error, NULL, NULL);
							SDL_RenderPresent(rendererPopup);
							SDL_Delay(2000);
							break;
						}
					}
					else {
						SDL_RenderClear(rendererPopup);
						SDL_RenderCopy(rendererPopup, error, NULL, NULL);
						SDL_RenderPresent(rendererPopup);
						SDL_Delay(2000);
						break;
					}
				}
				else {
					SDL_RenderClear(rendererPopup);
					SDL_RenderCopy(rendererPopup, error, NULL, NULL);
					SDL_RenderPresent(rendererPopup);
					SDL_Delay(2000);
					break;
				}

				break;

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
			render(dimensions.x, dimensions.y, arrow, &dimensions, rendererPopup);
			SDL_RenderPresent(rendererPopup);
		}
	}


	//hide cursor and delete second one
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_DestroyTexture(pad);
	SDL_DestroyTexture(arrow);
	SDL_DestroyTexture(error);
	SDL_DestroyTexture(success);
	SDL_DestroyTexture(hint);
	SDL_DestroyRenderer(rendererPopup);
	SDL_DestroyWindow(popup);
}