#include "numPad.h"

int numPad() {
	
	//create Hitboxes
	SDL_Rect seven, one, three, esc, enter;

	seven.x = SEVEN_X, seven.y = SEVEN_Y, seven.w = KEY_WIDTH, seven.h = KEY_HEIGHT;
	one.x = ONE_X, one.y = ONE_Y, one.w = KEY_WIDTH, one.h = KEY_HEIGHT;
	three.x = THREE_X, three.y = THREE_Y, three.w = KEY_WIDTH, three.h = KEY_HEIGHT;
	esc.x = ESC_X, esc.y = ESC_Y, esc.w = KEY_WIDTH, esc.h = KEY_HEIGHT;
	enter.x = ENTER_X, enter.y = ENTER_Y, enter.w = KEY_WIDTH, enter.h = KEY_HEIGHT;

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

	//set window focus
	if (0 != SDL_SetWindowInputFocus(popup)) {
		fprintf(stderr, "Window Focus could not be changend! SDL_Error: %s", SDL_GetError());
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

	SDL_Texture* pad = loadImage("images/numpad.bmp", rendererPopup);

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

				if ( XYInRect(esc, x_button, y_button) ) {

					quit = 0;
					SDL_DestroyWindow(popup);
				}
				else if (XYInRect(seven, x_button, y_button) ) {

					mouse.type = NULL;

					while (SDL_MOUSEBUTTONDOWN != mouse.type) {
						SDL_PollEvent(&mouse);
					}
					x_button = mouse.button.x;
					y_button = mouse.button.y;

					if ( XYInRect(one, x_button, y_button) ) {

						mouse.type = NULL;

						while (SDL_MOUSEBUTTONDOWN != mouse.type) {
							SDL_PollEvent(&mouse);
						}
						x_button = mouse.button.x;
						y_button = mouse.button.y;

						if ( XYInRect(three, x_button, y_button) ) {
							
							mouse.type = NULL;
							
							while (SDL_MOUSEBUTTONDOWN != mouse.type) {
								SDL_PollEvent(&mouse);
							}
							x_button = mouse.button.x;
							y_button = mouse.button.y;

							if ( XYInRect(seven, x_button, y_button) ) {
								
								mouse.type = NULL;

								while (SDL_MOUSEBUTTONDOWN != mouse.type) {
									SDL_PollEvent(&mouse);
								}
								x_button = mouse.button.x;
								y_button = mouse.button.y;

								if ( XYInRect(enter, x_button, y_button)) {
									
									//flashback2();
									SDL_DestroyWindow(popup);
									return 0;
								}
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