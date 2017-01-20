#include "esc.h"

int esc(SDL_Window *mainWindow, SDL_Renderer *rendererESC) {

	//create hitboxes
	SDL_Rect exit, resume;
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

	exit.x = QUIT_X, exit.y = QUIT_Y, exit.w = BUTTON_WIDTH, exit.h = BUTTON_HEIGHT;
	resume.x = RESUME_X, resume.y = RESUME_Y, resume.w = BUTTON_WIDTH, resume.h = BUTTON_HEIGHT;


	//load graphics for background
	SDL_Texture* background;
	background = loadImage("images/esc.bmp", rendererESC);

	if (!background) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	//show cursor
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);

	SDL_Event mouse;
	int x_button = -960;
	int y_button = -540;

	//render graphic
	SDL_RenderClear(rendererESC);
	SDL_RenderCopy(rendererESC, background, NULL, NULL);
	SDL_RenderPresent(rendererESC);

	while (1) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

				//if click appears in hitbox open one of the panels in new window
			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (XYInRect(exit, x_button, y_button)) {

					SDL_DestroyTexture(background);
					SDL_FreeCursor(cursor);
					SDL_ShowCursor(SDL_DISABLE);
					return 1;

				}
				else if (XYInRect(resume, x_button, y_button)) {

					SDL_DestroyTexture(background);
					SDL_FreeCursor(cursor);
					SDL_ShowCursor(SDL_DISABLE);
					return 0;

				}
				break;

			default:
				break;
			}

			//present in mainWindow
			SDL_RenderClear(rendererESC);
			SDL_RenderCopy(rendererESC, background, NULL, NULL);
			SDL_RenderPresent(rendererESC);
		}
	}
}