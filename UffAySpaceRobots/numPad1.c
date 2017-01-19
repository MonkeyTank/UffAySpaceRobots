#include "numPad1.h"

int numPad1() {
	
	int warnings = 0;

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
	SDL_Event mouse;
	//int x = -960;
	//int y = -540;
	int x_button = 250;
	int y_button = 250;

	while (1) {
		while (SDL_PollEvent(&mouse) != 0);
		
		if (SDL_MOUSEBUTTONDOWN == mouse.type){

			x_button = mouse.button.x;
			y_button = mouse.button.y;

		//on esc leave window
			if (XYInRect(esc, x_button, y_button)) {
				//hide cursor and delete second one
				SDL_FreeCursor(cursor);
				SDL_ShowCursor(SDL_DISABLE);
				SDL_DestroyWindow(popup);
				return 0;
			}

		//code for getting to the next room
			if (XYInRect(one, x_button, y_button)) {

				mouse.type = 0;
				mouse = getClick(mouse);
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (XYInRect(one, x_button, y_button)) {

					mouse.type = 0;
					mouse = getClick(mouse);
					x_button = mouse.button.x;
					y_button = mouse.button.y;

					if (XYInRect(one, x_button, y_button)) {

						mouse.type = 0;
						mouse = getClick(mouse);
						x_button = mouse.button.x;
						y_button = mouse.button.y;

						if (XYInRect(one, x_button, y_button)) {

							mouse.type = 0;
							mouse = getClick(mouse);
							x_button = mouse.button.x;
							y_button = mouse.button.y;

							if (XYInRect(enter, x_button, y_button)) {

								SDL_DestroyRenderer(rendererPopup);
								SDL_DestroyWindow(popup);
								return 1;
							}
						}
					}
				}
			}

		//code is not right, but enter has been pressed:
		//two warnings are issued and after third wrong try death awaits
			if (XYInRect(enter, x_button, y_button)) {
				Mix_PauseMusic();
		//warning returns 0 on death
				if (0 == warning(warnings)) {
					SDL_DestroyWindow(popup);
					return -1;
				}
				Mix_ResumeMusic();
				warnings++;
				mouse.button.x = 0;
				mouse.button.y = 0;

			}
			SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
		}
		SDL_RenderClear(rendererPopup);
		SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
		SDL_RenderPresent(rendererPopup);
		
	}
}
