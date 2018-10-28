#include "GameScene.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Ball.h"
#include "Paddle.h"
#include "Renderer.h"

void eventHandler(SDL_Event event, Paddle* player1, Paddle* player2, int* running, int* paused){
	while(SDL_PollEvent(&event))
		switch(event.type){
		case SDL_QUIT:
			*running = 1;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode){
			case SDL_SCANCODE_W:
				player1->controls[0]=1;
				break;
			case SDL_SCANCODE_UP:
				player2->controls[0]=1;
				break;
			case SDL_SCANCODE_S:
				player1->controls[1]=1;
				break;
			case SDL_SCANCODE_DOWN:
				player2->controls[1]=1;
				break;
			case SDL_SCANCODE_ESCAPE:
				*paused *= -1;
				break;
			default:
				break;
			}
			break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode){
				case SDL_SCANCODE_W:
					player1->controls[0]=0;
					break;
				case SDL_SCANCODE_UP:
					player2->controls[0]=0;
					break;
				case SDL_SCANCODE_S:
					player1->controls[1]=0;
					break;
				case SDL_SCANCODE_DOWN:
					player2->controls[1]=0;
					break;
				default:
					break;
				}
		}
}

void one_player_logic(SDL_Event event, int* running, Ball* ball, Paddle* player, Paddle* cpu, char* score_str, int* paused){
	//Exit and Input Handling
	eventHandler(event, player, cpu, running, paused);
	if(*paused == -1){
		//Player Movement Logic
		playerLogic(player);
		//Ball Movement Logic
		ballLogic(ball, player, cpu, score_str);
		//CPU Logic
		cpuLogic(cpu, ball);
		//Win Conditions
		if(player->score >= 5 || cpu->score >= 5){
			sprintf(score_str, "%d  %d", player->score, cpu->score);
			player->score = 0;
			cpu->score = 0;
		}
	}
}

void two_player_logic(SDL_Event event, int* running, Ball* ball, Paddle* player1, Paddle* player2, char* score_str, int* paused){
	//Exit and Input Handling
	eventHandler(event, player1, player2, running, paused);
	if(*paused == -1){
		//Player Movement Logic
		playerLogic(player1);
		playerLogic(player2);
		//Ball Movement Logic
		ballLogic(ball, player1, player2, score_str);
		//Win Conditions
		if(player1->score >= 5 || player2->score >= 5){
			sprintf(score_str, "%d  %d", player1->score, player2->score);
			player1->score = 0;
			player2->score = 0;
		}
	}
}
