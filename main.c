#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

void ballLogic(SDL_Rect* ball, int* ball_vel_x, int* ball_vel_y, SDL_Rect* player, SDL_Rect* cpu, int* player_score, int* cpu_score, char* score_str){
	ball->x += *ball_vel_x;
	ball->y += *ball_vel_y;
	if(ball->x <= 0){
		ball->x = BALL_SPAWN_X;
		ball->y = BALL_SPAWN_Y;
		*ball_vel_x *= -1;
		*cpu_score = *(cpu_score) + 1;
		sprintf(score_str, "%d  %d", *player_score, *cpu_score);
	}
	if(ball->x + ball->w >= WINDOW_WIDTH){
		ball->x = BALL_SPAWN_X;
		ball->y = BALL_SPAWN_Y;
		*ball_vel_x *= -1;
		*player_score = *(player_score) + 1;
		sprintf(score_str, "%d  %d", *player_score, *cpu_score);
	}
	if(ball->y <= 0){
				ball->y = 0;
				*ball_vel_y *= -1;
			}
	if(ball->y + ball->h >= WINDOW_HEIGHT){
				ball->y = WINDOW_HEIGHT - ball->h;
				*ball_vel_y *= -1;
			}
	if(ball->y + ball->h >= player->y && ball->y <= player->y + player->h && ball->x >= player->x && ball->x <= player->x + player->w){
		ball->x = player->x + player->w;
		*ball_vel_x *= -1;
	}
	if(ball->y + ball->h >= cpu->y && ball->y - ball->h <= cpu->y + cpu->h && ball->x + ball->w >= cpu->x && ball->x <= cpu->x + cpu->w){
		ball->x = cpu->x - ball->w;
		*ball_vel_x *= -1;
	}
	return;
}

void cpuLogic(SDL_Rect *cpu, SDL_Rect *ball){
	if(ball->y >= cpu->y && ball->x > WINDOW_WIDTH - WINDOW_WIDTH / 4) cpu->y += 5;
	else if(ball->y <= cpu->y + cpu->h && ball->x > WINDOW_WIDTH - WINDOW_WIDTH / 4) cpu->y -= 5;
	else{
		if(cpu->y + (cpu->h / 2) > (WINDOW_HEIGHT / 2) + 10) cpu->y -= 5;
		else if(cpu->y + (cpu->h / 2) < (WINDOW_HEIGHT / 2) - 10) cpu->y += 5;
	}
	if(cpu->y <= 0) cpu->y = 0;
	else if(cpu->y + cpu->h >= WINDOW_HEIGHT) cpu->y = WINDOW_HEIGHT - cpu->h;
}

void playerLogic(SDL_Rect* player, int up, int down){
	if(up && !down) player->y -= 5;
	if(down && !up) player->y += 5;
	if(player->y <= 0) player->y = 0;
	if(player->y + player->h >= WINDOW_HEIGHT) player->y = WINDOW_HEIGHT - player->h;
	return;
}

void drawGame(SDL_Renderer *renderer, SDL_Rect* player, SDL_Rect *cpu, SDL_Rect *ball){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 );
	SDL_RenderFillRect(renderer, player);
	SDL_RenderFillRect(renderer, cpu);
	SDL_RenderFillRect(renderer, ball);
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
	SDL_Window *window = SDL_CreateWindow("SLD2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
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

	//Scoreboard Variables
	int player_score = 0, cpu_score = 0;
	char score_str[5];
	sprintf(score_str, "%d  %d", player_score, cpu_score);
	SDL_Color White = {255, 255, 255};
	SDL_Rect score_rect;
	//Declaring Player Variable
	SDL_Rect player = { 0, WINDOW_HEIGHT / 2, 16, 64};
	//Declaring CPU Variable
	SDL_Rect cpu = { WINDOW_WIDTH - 16, WINDOW_HEIGHT / 2, 16, 64};
	//Declaring Variables
	SDL_Rect ball = { BALL_SPAWN_X, BALL_SPAWN_Y, 16, 16};
	int ball_vel_x = 5;
	int ball_vel_y = 5;
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
		ballLogic(&ball, &ball_vel_x, &ball_vel_y, &player, &cpu, &player_score, &cpu_score, score_str);
		//CPU Logic
		cpuLogic(&cpu, &ball);
		//Win Conditions
		if(player_score >= 5 || cpu_score >= 5){
			sprintf(score_str, "%d  %d", player_score, cpu_score);
			player_score = 0;
			cpu_score = 0;
		}
		//Draw game screen
		renderScore(renderer, score_str, font, &score_rect, &White);
		drawGame(renderer, &player, &cpu, &ball);
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
