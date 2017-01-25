#include "captcha.h"

void captcha(SDL_Window *mainWindow, SDL_Renderer *rendererPopup) {

	SDL_Rect rect1 = { 508, 388, 196, 196 };
	SDL_Rect rect2 = { 760, 392, 196, 196 };
	SDL_Rect rect3 = { 996, 388, 196, 196 };
	SDL_Rect rect4 = { 1232, 388, 196, 196 };

	//show cursor in window and set a new one
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);


	//build texture background
	SDL_Texture *pad = loadImage("images/room3/ratsel/captcha_big.bmp", rendererPopup);
	SDL_Texture *idiot = loadImage("images/room3/ratsel/captcha_big_error.bmp", rendererPopup);

	//build texture back arrow
	SDL_Texture* arrow = loadColorKeyImage("images/backArrow.bmp", rendererPopup, 0xFF, 0xFF, 0xFF);

	//variables to track clicks
	SDL_Event mouse;
	SDL_Keysym press;

	int x_button = 0;
	int y_button = 0;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;


	while (quit) {
		while (SDL_PollEvent(&mouse));
		
		switch (mouse.type) {

		case SDL_MOUSEBUTTONDOWN:
			x_button = mouse.button.x;
			y_button = mouse.button.y;


			if (XYInRect(rect4, x_button, y_button)) {

				warning(3);
				quit = 0;
				break;
			}
			else if (XYInRect(rect1, x_button, y_button) || XYInRect(rect2, x_button, y_button) || XYInRect(rect3, x_button, y_button)) {

				SDL_RenderClear(rendererPopup);
				SDL_RenderCopy(rendererPopup, idiot, NULL, NULL);
				SDL_RenderPresent(rendererPopup);
				SDL_Delay(3000);
				break;
			}			

		default:
			break;
		}

		SDL_RenderClear(rendererPopup);
		SDL_RenderCopy(rendererPopup, pad, NULL, NULL);
		SDL_RenderPresent(rendererPopup);
	}
	
	//hide cursor and delete second one
	//free everything
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_DestroyTexture(pad);
	SDL_DestroyTexture(arrow);
	SDL_DestroyTexture(idiot);
}