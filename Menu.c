#include "Menu.h"
#include "Renderer.h"

void eventHandler_Menu(SDL_Event event, int* running, int* players, int* selected){
	while(SDL_PollEvent(&event))
		switch(event.type){
		case SDL_QUIT:
			*running = 1;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode){
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				*players = 1;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				*players = 2;
				break;
			case SDL_SCANCODE_SPACE:
				*selected = 1;
				break;
			default:
				break;
			}
			break;
		}
}
