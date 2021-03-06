#include "room2.h"

int room2(SDL_Window *mainWindow) {

	//attempts to enter right code
	int attempts[1];
	attempts[0] = 0;

	//create hitboxes
	SDL_Rect colorHB = { COLOR_X, COLOR_Y, COLOR_WIDTH, COLOR_HEIGHT };
	SDL_Rect mensaHB = { MENSA_X, MENSA_Y, MENSA_WIDTH, MENSA_HEIGHT };
	SDL_Rect thingHB = { THING_X, THING_Y, THING_WIDTH, THING_HEIGHT };
	SDL_Rect numPadHB = { NUMPAD2_X, NUMPAD2_Y, NUMPAD2_WIDTH, NUMPAD2_HEIGHT };

	//create renderer for room2, hide the system cursor
	SDL_Renderer *rendererRoom2;
	rendererRoom2 = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererRoom2) {
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
	background = loadImage("images/room2/room2Background.bmp", rendererRoom2);

	if (!background) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture *light;
	light = loadColorKeyImage("images/light_cursor_final.bmp", rendererRoom2, 0xFF, 0xFF, 0xFF);

	if (!light) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	//set dimensions for backArrow hitbox
	SDL_Rect dimensions = { 0, 0, 3840, 2160 };

	SDL_Event mouse;
	int x = -960;
	int y = -540;
	int x_button = -960;
	int y_button = -540;


	SDL_RenderClear(rendererRoom2);
	SDL_RenderCopy(rendererRoom2, background, NULL, NULL);
	render(x, y, light, &dimensions, rendererRoom2);
	SDL_RenderPresent(rendererRoom2);

	flashback("text/flashback2.txt");
	Mix_PlayMusic(backgroundMusic, -1);
	int leave;

	while (1) {
		//constantly polling mouse to move pocket light graphic with cursor
		while (SDL_PollEvent(&mouse)) {
			switch (mouse.type) {

	//if click appears in hitbox open one of the panels in new window
			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (XYInRect(numPadHB, x_button, y_button)) {

	//numPad() returns 0 on esc, 1 on success and -1 on failure
					leave = numPad2(mainWindow, rendererRoom2, attempts);

					if (-1 == leave) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyRenderer(rendererRoom2);
						return 0;
					}
					else if (1 == leave) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyRenderer(rendererRoom2);
						return 1;
					}

				}
				else if (XYInRect(colorHB, x_button, y_button)) {

					colors();

				}
				else if (XYInRect(mensaHB, x_button, y_button)) {

					mensa();

				}
				else if (XYInRect(thingHB, x_button, y_button)) {

					things();

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
					if (esc(mainWindow, rendererRoom2)) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyRenderer(rendererRoom2);
						return -1;
					}
				}
				break;

			default:
				break;
			}

			//present in mainWindow
			SDL_RenderClear(rendererRoom2);
			SDL_RenderCopy(rendererRoom2, background, NULL, NULL);
			render(x, y, light, &dimensions, rendererRoom2);
			SDL_RenderPresent(rendererRoom2);
		}
	}
}

