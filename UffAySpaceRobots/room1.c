#include "room1.h"

void room1(SDL_Window* mainWindow) {

	//create renderer for room1, hide the system cursor
	SDL_Renderer* rendererRoom1;
	rendererRoom1 = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererRoom1) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}

	SDL_ShowCursor(SDL_DISABLE);

	//load graphics for background and pocket light
	SDL_Texture* background;
	background = loadImage("images/room1/room1Background.bmp", rendererRoom1);

	if ( !background ) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture* light;
	light = loadColorKeyImage("images/light_cursor.bmp", rendererRoom1, 0xFF, 0xFF, 0xFF);

	if ( !light ) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	//define starting positions for cursor and loaded graphics
	SDL_Rect dimensions;

	dimensions.x = 0;
	dimensions.y = 0;
	dimensions.w = 3840;
	dimensions.h = 2160;

	SDL_Event mouse;
	int x = -960;
	int y = -540;
	int x_button = -960;
	int y_button = -540;
	//if right code in numPad is entered, quit is set to 0 and room1 is left
	int quit = 1;

	while (quit) {
	//constantly polling mouse to move pocket light graphic with cursor
		while (SDL_PollEvent(&mouse)) {
			switch ( mouse.type ) {

	//if click appears in hitbox open one of the panels in new window
			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (x_button > NUMPAD_X_MIN && x_button < NUMPAD_X_MAX && y_button > NUMPAD_Y_MIN && y_button < NUMPAD_Y_MAX) {

					quit = numPad();
					
				}
				else if (x_button > ANA_X_MIN && x_button < ANA_X_MAX && y_button > ANA_Y_MIN && y_button < ANA_Y_MAX) {
					
					anagram();				

				}
				else if (x_button > NUM_X_MIN && x_button < NUM_X_MAX && y_button > NUM_Y_MIN && y_button < NUM_Y_MAX) {

					numbers();

				}
				else if (x_button > LAB_X_MIN && x_button < LAB_X_MAX && y_button > LAB_Y_MIN && y_button < LAB_Y_MAX) {

					labyrinth();

				}
				break;

		//tracking mouse
			case SDL_MOUSEMOTION:
				x = mouse.motion.x - 1920;
				y = mouse.motion.y - 1080;
				break;

			default:
				break;
			}

		//present in mainWindow
			SDL_RenderClear(rendererRoom1);
			SDL_RenderCopy(rendererRoom1, background, NULL, NULL);
			render(x, y, light, &dimensions, rendererRoom1);
			SDL_RenderPresent(rendererRoom1);
		}
	}
	return;
}
	
