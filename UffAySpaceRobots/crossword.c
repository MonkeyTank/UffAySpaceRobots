#include "crossword.h"

void crossword() {


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
	SDL_Texture *pad = loadImage("images/room3/ratsel/crossword.bmp", rendererPopup);
	SDL_Texture *hint_hex = loadImage("images/room3/ratsel/crossword_hint_hex.bmp", rendererPopup);
	SDL_Texture *error = loadImage("images/room3/ratsel/crossword_idiot.bmp", rendererPopup);

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
	SDL_Rect dimensions = { 1870, 1030, 50, 50 };
	SDL_Rect tip = { 1820, 0, 200, 100 };

	while (quit) {
		while (SDL_PollEvent(&keys)) {

			switch (keys.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = keys.button.x;
				y_button = keys.button.y;

				//click on backArrow hitbox -> exit panel Anagram
				if (XYInRect(dimensions, x_button, y_button)) {

					quit = 0;
					break;
				}

				if (XYInRect(tip, x_button, y_button)) {

					SDL_RenderClear(rendererPopup);
					SDL_RenderCopy(rendererPopup, hint_hex, NULL, NULL);
					SDL_RenderPresent(rendererPopup);
					SDL_Delay(5000);
					break;
				}

			case SDL_KEYDOWN:
				press = keys.key.keysym;

				//hit esc -> exit panel Anagram
				if (SDLK_ESCAPE == press.sym) {

					quit = 0;
					break;
				}

				//enter right code
				if (SDLK_1 == press.sym || SDLK_KP_1 == press.sym) {

					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (SDLK_4 == press.sym || SDLK_KP_4 == press.sym) {
						keys.type = 0;
						keys = getKey(keys);
						press = keys.key.keysym;

						if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
							SDL_RenderClear(rendererPopup);
							SDL_RenderCopy(rendererPopup, hint_hex, NULL, NULL);
							SDL_RenderPresent(rendererPopup);
							SDL_Delay(5000);
							break;
						}
					}
				}
				else if (SDLK_e == press.sym) {
					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
						SDL_RenderClear(rendererPopup);
						SDL_RenderCopy(rendererPopup, error, NULL, NULL);
						SDL_RenderPresent(rendererPopup);
						SDL_Delay(5000);
						break;
					}

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
	SDL_DestroyTexture(hint_hex);
	SDL_DestroyTexture(error);
	SDL_DestroyRenderer(rendererPopup);
	SDL_DestroyWindow(popup);
}