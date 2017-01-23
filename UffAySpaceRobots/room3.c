#include "room3.h"

int room3(SDL_Window *mainWindow) {

	//create hitboxes
	SDL_Rect crossHB, beerHB, sudokuHB, numPadHB;
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

	crossHB.x = CROSS_X, crossHB.y = CROSS_Y, crossHB.w = CROSS_WIDTH, crossHB.h = CROSS_HEIGHT;
	beerHB.x = BEER_X, beerHB.y = BEER_Y, beerHB.w = BEER_WIDTH, beerHB.h = BEER_HEIGHT;
	sudokuHB.x = SUD_X, sudokuHB.y = SUD_Y, sudokuHB.w = SUD_WIDTH, sudokuHB.h = SUD_HEIGHT;
	numPadHB.x = NUMPAD3_X, numPadHB.y = NUMPAD3_Y, numPadHB.w = NUMPAD3_WIDTH, numPadHB.h = NUMPAD3_HEIGHT;

	//create renderer for room3, hide the system cursor
	SDL_Renderer *rendererRoom3;
	rendererRoom3 = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererRoom3) {
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
	}

	SDL_ShowCursor(SDL_DISABLE);

	///////////////////////////////////////////////MUSIC//////////////////////////////////////////////////
	Mix_Music *backgroundMusic = NULL;

	//init sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//load music
	backgroundMusic = Mix_LoadMUS("sounds/background.mp3");

	if (NULL == backgroundMusic) {
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}


	//load graphics for background and pocket light
	SDL_Texture *background;
	background = loadImage("images/room3/room3Background.bmp", rendererRoom3);

	if (!background) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture *light;
	light = loadColorKeyImage("images/light_cursor_fade_small.bmp", rendererRoom3, 0xFF, 0xFF, 0xFF);

	if (!light) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	//define starting positions for cursor and loaded graphics
	SDL_Rect dimensions;
	dimensions.x = 0, dimensions.y = 0, dimensions.w = 3840, dimensions.h = 2160;

	SDL_Event mouse;
	int x = -960;
	int y = -540;
	int x_button = -960;
	int y_button = -540;

	//if right code in numPad is entered, quit is set to 0 and room3 is left
	int quit = 1;

	SDL_RenderClear(rendererRoom3);
	SDL_RenderCopy(rendererRoom3, background, NULL, NULL);
	render(x, y, light, &dimensions, rendererRoom3);
	SDL_RenderPresent(rendererRoom3);

	flashback3();
	Mix_PlayMusic(backgroundMusic, -1);
	int leave;

	while (quit) {
		//constantly polling mouse to move pocket light graphic with cursor
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

				//if click appears in hitbox open one of the panels in new window
			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (XYInRect(numPadHB, x_button, y_button)) {

		//numPad() returns 0 on esc, 1 on success and -1 on failure
					leave = numPad3();

					if (-1 == leave) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyRenderer(rendererRoom3);
						return 0;
					}
					else if (1 == leave) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyRenderer(rendererRoom3);
						return 1;
					}

				}
				else if (XYInRect(crossHB, x_button, y_button)) {

					crossword();

				}
				else if (XYInRect(sudokuHB, x_button, y_button)) {

					sudoku();

				}
				else if (XYInRect(beerHB, x_button, y_button)) {

					beer();

				}
				break;

				//tracking mouse
			case SDL_MOUSEMOTION:
				x = mouse.motion.x - 1920;
				y = mouse.motion.y - 1080;
				break;

			case SDL_KEYDOWN:
				if (SDLK_ESCAPE == mouse.key.keysym.sym) {
					//esc asks user, if he wants to exit  and returns 1 if yes and 0 if not
					if (esc(mainWindow, rendererRoom3)) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyRenderer(rendererRoom3);
						return -1;
					}
				}
				break;

			default:
				break;
			}

			//present in mainWindow
			SDL_RenderClear(rendererRoom3);
			SDL_RenderCopy(rendererRoom3, background, NULL, NULL);
			render(x, y, light, &dimensions, rendererRoom3);
			SDL_RenderPresent(rendererRoom3);
		}
	}
}

