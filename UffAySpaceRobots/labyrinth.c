#include "labyrinth.h"

void labyrinth() {

	//build window
	SDL_Window* popup;
	popup = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_BORDERLESS);
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

	//show cursor in window
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
	SDL_Texture* pad = loadImage("images/room1/labyrinth.bmp", rendererPopup);

	//build texture back arrow
	SDL_Texture* arrow = loadImage("images/backArrow.bmp", rendererPopup);

	//build texture pocket light
	SDL_Texture* light = loadColorKeyImage("images/light_small.bmp", rendererPopup, 0xFF, 0xFF, 0xFF);

	//variables to track clicks
	SDL_Event mouse;
	int x = -960;
	int y = -540;
	int x_button = 0;
	int y_button = 0;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;

	//set dimensions for backArrow hitbox
	SDL_Rect dimensionsArrow;

	dimensionsArrow.x = ARROW_X;
	dimensionsArrow.y = ARROW_Y;
	dimensionsArrow.w = ARROW_DIM;
	dimensionsArrow.h = ARROW_DIM;

	//set dimensions for pocket light
	SDL_Rect dimensions;

	dimensions.x = 0;
	dimensions.y = 0;
	dimensions.w = 3840;
	dimensions.h = 2160;

	while (quit) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;
	//click on backArrow hitbox -> exit panel labyrinth
				if ( XYInRect(dimensionsArrow, x_button, y_button)) {

					quit = 0;
					SDL_DestroyWindow(popup);
				}
				break;

			case SDL_MOUSEMOTION:
				x = mouse.motion.x - 1920;
				y = mouse.motion.y - 1080;
				break;

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
			render(x, y, light, &dimensions, rendererPopup);
			render(dimensionsArrow.x, dimensionsArrow.y, arrow, &dimensionsArrow, rendererPopup);
			SDL_RenderPresent(rendererPopup);
		}
	}
	//hide cursor and delete second one
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);

}