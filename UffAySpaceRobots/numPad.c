#include "numPad.h"

int numPad() {
	
	//build window
	SDL_Window* popup;
	popup = SDL_CreateWindow("popup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 900, SDL_WINDOW_SHOWN);
	if (popup == NULL) {
		fprintf(stderr, "Window could not be created! SDL_Error: %s", SDL_GetError());
	}

	//set window mode
	if (0 != SDL_SetWindowFullscreen(popup, 0)) {
		fprintf(stderr, "Fullscreen not possible! SDL_Error: %s", SDL_GetError());
	}

	//set window focus
	//if (0 != SDL_SetWindowInputFocus(popup)) {
	//	fprintf(stderr, "Window Focus could not be changend! SDL_Error: %s", SDL_GetError());
	//}

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

	SDL_Texture* pad = loadImage("images/room1/numPad.bmp", rendererPopup);

	//variables to track clicks
	SDL_Event mouse;
	//int x = -960;
	//int y = -540;
	int x_button = 250;
	int y_button = 250;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;

	while (quit) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (x_button > 450 && x_button < 500 && y_button > 450 && y_button < 500) {

					quit = 0;
					SDL_DestroyWindow(popup);
				}
				else if (x_button > 0 && x_button < 125 && y_button > 0 && y_button < 125) {

					mouse.type = NULL;

					while (SDL_MOUSEBUTTONDOWN != mouse.type) {
						SDL_PollEvent(&mouse);
					}
					x_button = mouse.button.x;
					y_button = mouse.button.y;

					if (x_button > 0 && x_button < 125 && y_button > 250 && y_button < 375) {

						mouse.type = NULL;

						while (SDL_MOUSEBUTTONDOWN != mouse.type) {
							SDL_PollEvent(&mouse);
						}
						x_button = mouse.button.x;
						y_button = mouse.button.y;

						if (x_button > 250 && x_button < 375 && y_button > 250 && y_button < 375) {
							
							mouse.type = NULL;
							
							while (SDL_MOUSEBUTTONDOWN != mouse.type) {
								SDL_PollEvent(&mouse);
							}
							x_button = mouse.button.x;
							y_button = mouse.button.y;

							if (x_button > 0 && x_button < 125 && y_button > 0 && y_button < 125) {
								printf("4. x: %d, y: %d\n", x_button, y_button);
								return 0;
							}
						}
					}
				}
				break;

			//case SDL_MOUSEMOTION:
			//	x = mouse.motion.x - 1920;
			//	y = mouse.motion.y - 1080;
			//	break;

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
			//render(x, y, light, &dimensions, rendererPopup);
			SDL_RenderPresent(rendererPopup);
		}
	}
	//hide cursor and delete second one
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
	return 1;
}