#include "numbers.h"

void numbers() {

	//build window
	SDL_Window *popup;
	popup = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 375, SDL_WINDOW_BORDERLESS);
	if (popup == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}

	//set window size
	if (0 != SDL_SetWindowFullscreen(popup, 0)) {
		fprintf(stderr, "Fullscreen not possible! SDL_Error: %s", SDL_GetError());
	}

	//show cursor in window and set a new one
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
	SDL_Texture *pad = loadImage("images/room1/zahlenreihe.bmp", rendererPopup);
	SDL_Texture *idiot = loadImage("images/room1/zahlenreihe_idiot.bmp", rendererPopup);
	SDL_Texture *hint = loadImage("images/room1/zahlenreihe_hint.bmp", rendererPopup);

	//build texture back arrow
	SDL_Texture* arrow = loadColorKeyImage("images/backArrow.bmp", rendererPopup, 0xFF, 0xFF, 0xFF);

	//variables to track clicks
	SDL_Event mouse;
	SDL_Keysym press;

	int x_button = 0;
	int y_button = 0;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;

	//set dimensions for backArrow hitbox
	SDL_Rect dimensions = { 1150, 325, 50, 50 };

	SDL_Rect tippHB = { 0, 0, 163, 67 };


	while (quit) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

	//click on backArrow hitbox -> exit panel Popup
				if ( XYInRect(dimensions, x_button, y_button) ) {

					quit = 0;
				}

				if (XYInRect(tippHB, x_button, y_button)) {

					SDL_RenderClear(rendererPopup);
					SDL_RenderCopy(rendererPopup, idiot, NULL, NULL);
					SDL_RenderPresent(rendererPopup);

					mouse.type = 0;
					mouse = getKey(mouse);
					press = mouse.key.keysym;

					if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
						SDL_RenderClear(rendererPopup);
						SDL_RenderCopy(rendererPopup, hint, NULL, NULL);
						SDL_RenderPresent(rendererPopup);

						SDL_Delay(5000);
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
	//free everything
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_DestroyTexture(pad);
	SDL_DestroyTexture(arrow);
	SDL_DestroyTexture(hint);
	SDL_DestroyTexture(idiot);
	SDL_DestroyRenderer(rendererPopup);
	SDL_DestroyWindow(popup);
}