#include "die.h"

int die(SDL_Window* dieWindow) {


	//create hitboxes
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);


	SDL_Rect exit = {EXIT_X, EXIT_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_Rect restart = { RESTART_X, RESTART_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

	//create renderer for die
	SDL_Renderer *rendererDie;
	rendererDie = SDL_CreateRenderer(dieWindow, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererDie) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}

	//show cursor
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Cursor *cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);

	///////////////////////////////////////////////MUSIC//////////////////////////////////////////////////
	Mix_Music *backgroundMusic = NULL;

	//init sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//load music
	backgroundMusic = Mix_LoadMUS("sounds/youdied.mp3");

	if (NULL == backgroundMusic) {
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//play music
	Mix_PlayMusic(backgroundMusic, 1);

	//load graphics for background
	SDL_Texture* background;
	background = loadImage("images/youdied.bmp", rendererDie);

	if (!background) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}


	SDL_Event mouse;
	int x_button = -960;
	int y_button = -540;

	//render graphic
	SDL_RenderClear(rendererDie);
	SDL_RenderCopy(rendererDie, background, NULL, NULL);
	SDL_RenderPresent(rendererDie);

	while (1) {
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

				//if click appears in hitbox open one of the panels in new window
			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (XYInRect(exit, x_button, y_button)) {

					Mix_HaltMusic();
					Mix_FreeMusic(backgroundMusic);
					backgroundMusic = NULL;
					SDL_DestroyRenderer(rendererDie);
					SDL_FreeCursor(cursor);
					SDL_ShowCursor(SDL_DISABLE);
					return 0;

				}
				else if (XYInRect(restart, x_button, y_button)) {

					Mix_HaltMusic();
					Mix_FreeMusic(backgroundMusic);
					backgroundMusic = NULL;
					SDL_DestroyRenderer(rendererDie);
					SDL_FreeCursor(cursor);
					SDL_ShowCursor(SDL_DISABLE);
					return 1;

				}
				break;

			default:
				break;
			}

			//present in mainWindow
			SDL_RenderClear(rendererDie);
			SDL_RenderCopy(rendererDie, background, NULL, NULL);
			SDL_RenderPresent(rendererDie);
		}
	}
}