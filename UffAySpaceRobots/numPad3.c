#include "numPad3.h"

int numPad3(SDL_Window *mainWindow, SDL_Renderer *rendererPopup) {

	int warnings = 0;
	SDL_Rect pad_rect = { 610, 90, 700, 900 };

	SDL_Rect ESC = { ESC_X, ESC_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect ZERO = { ZERO_X, ZERO_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect ENTER = { ENTER_X, ENTER_Y, BUTTON_W, BUTTON_H2 };

	SDL_Rect ONE = { ONE_X, ONE_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect TWO = { TWO_X, TWO_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect THREE = { THREE_X, THREE_Y, BUTTON_W, BUTTON_H2 };

	SDL_Rect FOUR = { FOUR_X, FOUR_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect FIVE = { FIVE_X, FIVE_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect SIX = { SIX_X, SIX_Y, BUTTON_W, BUTTON_H2 };

	SDL_Rect SEVEN = { SEVEN_X, SEVEN_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect EIGHT = { EIGHT_X, EIGHT_Y, BUTTON_W, BUTTON_H2 };
	SDL_Rect NINE = { NINE_X, NINE_Y, BUTTON_W, BUTTON_H2 };

	SDL_Rect A = { A_X, A_Y, BUTTON_W, BUTTON_H1 };
	SDL_Rect B = { B_X, B_Y, BUTTON_W, BUTTON_H1 };
	SDL_Rect C = { C_X, C_Y, BUTTON_W, BUTTON_H1 };

	SDL_Rect D = { D_X, D_Y, BUTTON_W, BUTTON_H1 };
	SDL_Rect E = { E_X, E_Y, BUTTON_W, BUTTON_H1 };
	SDL_Rect F = { F_X, F_Y, BUTTON_W, BUTTON_H1 };


	//show cursor
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);


	SDL_Texture *pad = loadImage("images/numpad/numpad.bmp", rendererPopup);

	//variables to track clicks
	SDL_Event keys;
	SDL_Keysym press;

	int x = 0;
	int y = 0;
	int x_button = 250;
	int y_button = 250;

	while (1) {
		while (SDL_PollEvent(&keys)) {
			switch (keys.type) {

			case SDL_MOUSEBUTTONDOWN:
				x = keys.button.x;
				y = keys.button.y;

				if (XYInRect(ESC, x, y)) {

					SDL_FreeCursor(cursor);
					SDL_ShowCursor(SDL_DISABLE);
					SDL_DestroyTexture(pad);
					return 0;
				}


				//enter code
				if (XYInRect(SIX, x, y)) {

					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (XYInRect(FIVE, x, y)) {
						keys.type = 0;
						keys = getKey(keys);
						press = keys.key.keysym;

						if (XYInRect(TWO, x, y)) {
							keys.type = 0;
							keys = getKey(keys);
							press = keys.key.keysym;

							if (XYInRect(E, x, y)) {
								keys.type = 0;
								keys = getKey(keys);
								press = keys.key.keysym;

								if (XYInRect(ENTER, x, y)) {

									SDL_FreeCursor(cursor);
									SDL_ShowCursor(SDL_DISABLE);
									SDL_DestroyTexture(pad);
									return 1;

								}
							}
						}
					}
				}

				if (XYInRect(ENTER, x, y)) {
					Mix_PauseMusic();

					//warning returns 0 on death
					if (0 == warning(warnings)) {
						SDL_FreeCursor(cursor);
						SDL_ShowCursor(SDL_DISABLE);
						SDL_DestroyTexture(pad);
						return -1;
					}
					Mix_ResumeMusic();
					warnings++;
					break;
				}

			case SDL_KEYDOWN:
				press = keys.key.keysym;

				if (SDLK_ESCAPE == press.sym) {

					SDL_FreeCursor(cursor);
					SDL_ShowCursor(SDL_DISABLE);
					SDL_DestroyTexture(pad);

					return 0;
				}


				//enter code
				if (SDLK_6 == press.sym || SDLK_KP_6 == press.sym) {

					keys.type = 0;
					keys = getKey(keys);
					press = keys.key.keysym;

					if (SDLK_5 == press.sym || SDLK_KP_5 == press.sym) {
						keys.type = 0;
						keys = getKey(keys);
						press = keys.key.keysym;

						if (SDLK_2 == press.sym || SDLK_KP_2 == press.sym) {
							keys.type = 0;
							keys = getKey(keys);
							press = keys.key.keysym;

							if (SDLK_e == press.sym) {
								keys.type = 0;
								keys = getKey(keys);
								press = keys.key.keysym;

								if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {

									SDL_FreeCursor(cursor);
									SDL_ShowCursor(SDL_DISABLE);
									SDL_DestroyTexture(pad);

									return 1;

								}
							}
						}
					}
				}

				if (SDLK_RETURN == press.sym || SDLK_RETURN2 == press.sym) {
					Mix_PauseMusic();
					//warning returns 0 on death
					if (0 == warning(warnings)) {

						SDL_FreeCursor(cursor);
						SDL_ShowCursor(SDL_DISABLE);
						SDL_DestroyTexture(pad);				

						return -1;
					}
					Mix_ResumeMusic();
					warnings++;
					break;
				}

			default:
				break;
			}

			SDL_RenderClear(rendererPopup);
			SDL_RenderCopy(rendererPopup, pad, NULL, &pad_rect);
			SDL_RenderPresent(rendererPopup);
		}
	}
}
