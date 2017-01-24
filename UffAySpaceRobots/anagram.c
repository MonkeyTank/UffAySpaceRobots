#include "anagram.h"

void anagram(SDL_Window *mainWindow, SDL_Renderer *rendererPopup) {
	
	SDL_Rect hintHB = { 170, 664, 200, 75 };
	SDL_Rect anagram_rect = { 160, 340, 1600, 400 };

	//show cursor in window
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);


	//build texture background
	SDL_Texture *pad = loadImage("images/room1/anagram.bmp", rendererPopup);
	SDL_Texture *hint= loadImage("images/room1/anagram_hint.bmp", rendererPopup);

	//build texture back arrow
	SDL_Texture *arrow = loadColorKeyImage("images/backArrow.bmp", rendererPopup, 0xFF, 0xFF, 0xFF);

	//variables to track clicks
	SDL_Event mouse;

	int x_button = 0;
	int y_button = 0;

	//quit is set by clicking on backArrow hitbox
	int quit = 1;

	//set dimensions for backArrow hitbox
	SDL_Rect dimensions = { 1710, 690, 50, 50 };

	while (quit) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

	//click on backArrow hitbox -> exit panel Anagram
				if ( XYInRect(dimensions, x_button, y_button) ) {

					quit = 0;
					break;
				}
				
				if (XYInRect(hintHB, x_button, y_button)) {

					SDL_RenderClear(rendererPopup);
					SDL_RenderCopy(rendererPopup, hint, NULL, &anagram_rect);
					SDL_RenderPresent(rendererPopup);
					SDL_Delay(8000);
					break;
				}

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, &anagram_rect);
			render(dimensions.x, dimensions.y, arrow, &dimensions, rendererPopup);
			SDL_RenderPresent(rendererPopup);
		}
	}

	//hide cursor and delete second one
	SDL_FreeCursor(cursor);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_DestroyTexture(pad);
	SDL_DestroyTexture(arrow);
	SDL_DestroyTexture(hint);
}