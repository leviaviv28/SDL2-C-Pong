#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"
#include "ball.h"
#include "paddle.h"
#include "GameScene.h"
#include "Menu.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BALL_SPAWN_X ((WINDOW_WIDTH / 2) - 8)
#define BALL_SPAWN_Y ((WINDOW_HEIGHT / 2) - 8)

int main(int argc, char **argv){
	//SDL Initialization
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	Init(&window, &renderer, &font);
	//Menu Variables
	int selected = 0;
	//Game Variables
	//Player1 Variables
	Paddle player1;
	SDL_Rect player_rect = { 0, WINDOW_HEIGHT / 2, 16, 64};
	player1.rect = player_rect;
	player1.score = 0;
	player1.controls[0] = player1.controls[1] = 0;
	//Player2 Variables
	Paddle player2;
	player_rect.x = WINDOW_WIDTH - 16;
	player2.rect = player_rect;
	player2.score = 0;
	player2.controls[0] = player2.controls[1] = 0;
	//Ball Variables
	Ball ball;
	ball.vel_x = 5;
	ball.vel_y = 5;
	SDL_Rect ball_rect = {BALL_SPAWN_X, BALL_SPAWN_Y, 16, 16};
	ball.rect = ball_rect;
	//Scoreboard Variables
	SDL_Color White = {255, 255, 255};
	char score_str[5];
	sprintf(score_str, "%d  %d", player1.score, player2.score);
	SDL_Rect score_rect;
	//Event Handling Variables
	int running = 0;
	int paused = -1;
	SDL_Event event;
	//Game Loop
	int players = 1;
	while(!running){
		if(selected == 0){
			eventHandler_Menu(event, &running, &players, &selected);
			drawMenu(renderer, font, players);
		}else{
			if(players == 1)
				one_player_logic(event, &running, &ball, &player1, &player2, score_str, &paused);
			else
				two_player_logic(event, &running, &ball, &player1, &player2, score_str, &paused);
			renderScore(renderer, score_str, font, &score_rect, &White);
			drawGame(renderer, player1, player2, ball);
			if(paused == 1)
				drawPaused(renderer, font);
		}
		//Display updates on screen
		redraw(renderer);
	}
	//Release Resources
	quit(renderer, window, font);
	return 0;
}
