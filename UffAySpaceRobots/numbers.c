#include "numbers.h"

void numbers() {

	//build window
	SDL_Window* popup;
	popup = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 375, SDL_WINDOW_BORDERLESS);
	if (popup == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}

	//set window size
	if (0 != SDL_SetWindowFullscreen(popup, 0)) {
		fprintf(stderr, "Fullscreen not possible! SDL_Error: %s", SDL_GetError());
	}

	//put window in focus
	if (0 != SDL_SetWindowInputFocus(popup)) {
		fprintf(stderr, "Window Focus could not be changend! SDL_Error: %s", SDL_GetError());
	}

	//show cursor in window and set a new one
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);


	//build renderer
	SDL_Renderer* rendererPopup;
	rendererPopup = SDL_CreateRenderer(popup, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererPopup) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}

	//build texture background
	SDL_Texture *row = loadImage("images/room1/zahlenreihe_tipp.bmp", rendererPopup);
	SDL_Texture *idiot = loadImage("images/room1/zahlenreihe_idiot.bmp", rendererPopup);
	SDL_Texture *tipp = loadImage("images/room1/zahlenreihe_tipp.bmp", rendererPopup);

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
	SDL_Rect dimensions;
	dimensions.x = 1150, dimensions.y = 325, dimensions.w = 50, dimensions.h = 50;

	SDL_Rect tippHB;
	tippHB.x = 0, tippHB.y = 0, tippHB.w = 163, tippHB.h = 67;


	while (quit) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

	//click on backArrow hitbox -> exit panel Popup
				if ( XYInRect(dimensions, x_button, y_button) ) {

					quit = 0;
					SDL_DestroyWindow(popup);
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
						SDL_RenderCopy(rendererPopup, tipp, NULL, NULL);
						SDL_RenderPresent(rendererPopup);

						SDL_Delay(5000);
					}
				
				}

				break;

				/*case SDL_MOUSEMOTION:
				x = mouse.motion.x - 1920;
				y = mouse.motion.y - 1080;
				break;*/

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, row, NULL, NULL);
			render(dimensions.x, dimensions.y, arrow, &dimensions, rendererPopup);
			SDL_RenderPresent(rendererPopup);
		}
	}
	//hide cursor and delete second one
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
}