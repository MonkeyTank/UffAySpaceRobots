#include "numbers.h"

void numbers(SDL_Window *mainWindow, SDL_Renderer *rendererPopup) {

	SDL_Rect tippHB = { 360, 353, 163, 67 };
	SDL_Rect numbers_rect = { 360, 353, 1200, 375 };
	
	//show cursor in window and set a new one
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);


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
	SDL_Rect dimensions = { 1510, 678, 50, 50 };


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
					SDL_RenderCopy(rendererPopup, idiot, NULL, &numbers_rect);
					SDL_RenderPresent(rendererPopup);

					mouse.type = 0;
					mouse = getKey(mouse);
					press = mouse.key.keysym;

					if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
						SDL_RenderClear(rendererPopup);
						SDL_RenderCopy(rendererPopup, hint, NULL, &numbers_rect);
						SDL_RenderPresent(rendererPopup);

						SDL_Delay(8000);
					}
				
				}

				break;

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, &numbers_rect);
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
}