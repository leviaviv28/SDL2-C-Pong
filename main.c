#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ball.h"
#include "paddle.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BALL_SPAWN_X ((WINDOW_WIDTH / 2) - 8)
#define BALL_SPAWN_Y ((WINDOW_HEIGHT / 2) - 8)

void renderScore(SDL_Renderer *renderer, const char *score_str, TTF_Font *font, SDL_Rect *rect, SDL_Color *color) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = TTF_RenderText_Solid(font, score_str, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = (WINDOW_WIDTH / 2) - 20;
    rect->y = 0;
    rect->w = surface->w;
    rect->h = surface->h;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

void eventHandler(SDL_Event event, int* up, int* down, int* running, int* pause){
	while(SDL_PollEvent(&event))
		switch(event.type){
		case SDL_QUIT:
			*running = 1;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode){
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				*up=1;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				*down=1;
				break;
			case SDL_SCANCODE_SPACE:
				*pause = 1;
				break;
			default:
				break;
			}
			break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode){
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					*up=0;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					*down=0;
					break;
				default:
					break;
				}
		}
}

void drawGame(SDL_Renderer *renderer, Paddle player, Paddle cpu, Ball ball){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 );
	SDL_Rect* player_rect = &player.rect;
	SDL_Rect* cpu_rect = &cpu.rect;
	SDL_Rect* ball_rect = &ball.rect;
	SDL_RenderFillRect(renderer, player_rect);
	SDL_RenderFillRect(renderer, cpu_rect);
	SDL_RenderFillRect(renderer, ball_rect);
	SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	return;
}

void quit(SDL_Renderer* renderer, SDL_Window* window){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	return;
}

int main(int argc, char **argv){
	//Check for any errors in initializations
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if(!window){
		printf("Error initializing window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	Uint32 render_flags =  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);
	if(!renderer){
			printf("Error initializing renderer: %s\n", SDL_GetError());
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 1;
		}
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Sans.ttf", 24);
	if(!font){
		printf("Error initializing font: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}
	//Declaring Player Variable
	Paddle player;
	SDL_Rect player_rect = { 0, WINDOW_HEIGHT / 2, 16, 64};
	player.rect = player_rect;
	player.score = 0;
	//Declaring CPU Variable
	Paddle cpu;
	SDL_Rect cpu_rect = { WINDOW_WIDTH - 16, WINDOW_HEIGHT / 2, 16, 64};
	cpu.rect = cpu_rect;
	cpu.score = 0;
	//Scoreboard Variables
	char score_str[5];
	sprintf(score_str, "%d  %d", player.score, cpu.score);
	SDL_Color White = {255, 255, 255};
	SDL_Rect score_rect;
	//Declaring Variables
	Ball ball;
	ball.vel_x = 5;
	ball.vel_y = 5;
	SDL_Rect ball_rect = {BALL_SPAWN_X, BALL_SPAWN_Y, 16, 16};
	ball.rect = ball_rect;
	//Input handling variables
	int up = 0;
	int down = 0;
	int paused = 0;
	int running = 0;
	SDL_Event event;
	//Game Loop
	while(!running){
		//Exit and Input Handling
		eventHandler(event, &up, &down, &running, &paused);
		//Player Movement Logic
		playerLogic(&player, up, down);
		//Ball Movement Logic
		ballLogic(&ball, &player, &cpu, score_str);
		//CPU Logic
		cpuLogic(&cpu, &ball);
		//Win Conditions
		if(player.score >= 5 || cpu.score >= 5){
			sprintf(score_str, "%d  %d", player.score, cpu.score);
			player.score = 0;
			cpu.score = 0;
		}
		//Draw game screen
		renderScore(renderer, score_str, font, &score_rect, &White);
		drawGame(renderer, player, cpu, ball);
		//Display updates on screen
		SDL_RenderPresent(renderer);
		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_Delay(1000/60);
	}
	//Release Resources
	quit(renderer, window);
	return 0;
}
