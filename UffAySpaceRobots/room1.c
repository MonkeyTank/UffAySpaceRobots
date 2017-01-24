#include "room1.h"

int room1(SDL_Window *mainWindow) {

	//create hitboxes
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

	SDL_Rect anagramHB = { ANA_X, ANA_Y, ANA_WIDTH, ANA_HEIGHT };
	SDL_Rect labyrinthHB = { LAB_X, LAB_Y, LAB_WIDTH, LAB_HEIGHT };
	SDL_Rect numbersHB = { NUM_X, NUM_Y, NUM_WIDTH, NUM_HEIGHT };
	SDL_Rect numPadHB = { NUMPAD1_X, NUMPAD1_Y, NUMPAD1_WIDTH, NUMPAD1_HEIGHT };
	SDL_Rect paperclipHB = {PAPERCLIP_X, PAPERCLIP_Y, PAPERCLIP_W, PAPERCLIP_H};

	//create renderer for room1, hide the system cursor
	SDL_Renderer *rendererRoom1;
	rendererRoom1 = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == rendererRoom1) {
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
	SDL_Texture* background;
	background = loadImage("images/room1/room1Background.bmp", rendererRoom1);

	if ( !background ) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture* light;
	light = loadColorKeyImage("images/light_cursor_final.bmp", rendererRoom1, 0xFF, 0xFF, 0xFF);

	if ( !light ) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	SDL_Texture* paperclip;
	paperclip = loadColorKeyImage("images/paperclip.bmp", rendererRoom1, 0xFF, 0xFF, 0xFF);

	if (!paperclip) {
		fprintf(stderr, "Could not load image! SDL_Error: %s", SDL_GetError());
	}

	//define starting positions for cursor and loaded graphics
	SDL_Rect dimensions = { 0, 0, 3840, 2160 };
	
	SDL_Event mouse;
	int x = -960;
	int y = -540;
	int x_button = -960;
	int y_button = -540;


	SDL_RenderClear(rendererRoom1);
	SDL_RenderCopy(rendererRoom1, background, NULL, NULL);
	SDL_RenderCopy(rendererRoom1, paperclip, NULL, &paperclipHB);
	render(x, y, light, &dimensions, rendererRoom1);
	SDL_RenderPresent(rendererRoom1);

	//tell story
	welcome(mainWindow, rendererRoom1);
	flashback("text/flashback1.txt");
	flashback("text/flashback1_1.txt");
	Mix_PlayMusic(backgroundMusic, -1);
	int leave;

	while (1) {
	//constantly polling mouse to move pocket light graphic with cursor
		while (SDL_PollEvent(&mouse)) {
			switch ( mouse.type ) {

	//if click appears in hitbox open one of the panels in new window
			case SDL_MOUSEBUTTONDOWN:
				x_button = mouse.button.x;
				y_button = mouse.button.y;

				if (XYInRect(numPadHB, x_button, y_button)) {
	
	//numPad() returns 0 on esc, 1 on success and -1 on failure
					leave = numPad1(mainWindow, rendererRoom1);

					if (-1 == leave) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyTexture(paperclip);
						SDL_DestroyRenderer(rendererRoom1);
						return 0;
					}
					else if (1 == leave) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyTexture(paperclip);
						SDL_DestroyRenderer(rendererRoom1);
						return 1;
					}
					
				}
				else if (XYInRect(anagramHB, x_button, y_button)) {
					
					anagram(mainWindow, rendererRoom1);				

				}
				else if (XYInRect(numbersHB, x_button, y_button)) {

					numbers(mainWindow, rendererRoom1);

				}
				else if (XYInRect(labyrinthHB, x_button, y_button)) {

					labyrinth();

				}
				else if (XYInRect(paperclipHB, x_button, y_button)) {

					help(mainWindow, rendererRoom1);

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
					if (esc(mainWindow, rendererRoom1)) {
						Mix_HaltMusic();
						Mix_FreeMusic(backgroundMusic);
						backgroundMusic = NULL;
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(light);
						SDL_DestroyTexture(paperclip);
						SDL_DestroyRenderer(rendererRoom1);
						return -1;
					}
				}
				break;

			default:
				break;
			}

		//present in mainWindow
			SDL_RenderClear(rendererRoom1);
			SDL_RenderCopy(rendererRoom1, background, NULL, NULL);
			SDL_RenderCopy(rendererRoom1, paperclip, NULL, &paperclipHB);
			render(x, y, light, &dimensions, rendererRoom1);
			SDL_RenderPresent(rendererRoom1);
		}
	}
}
	
