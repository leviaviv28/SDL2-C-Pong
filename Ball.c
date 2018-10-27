#include "ball.h"
#include <stdio.h>

void ballLogic(Ball* ball, Paddle* player, Paddle* cpu, char* score_str){
	ball->rect.x += ball->vel_x;
	ball->rect.y += ball->vel_y;
	if(ball->rect.x <= 0){
		ball->rect.x = BALL_SPAWN_X;
		ball->rect.y = BALL_SPAWN_Y;
		ball->vel_x *= -1;
		cpu->score++;
		sprintf(score_str, "%d  %d", player->score, cpu->score);
	}
	if(ball->rect.x + ball->rect.w >= WINDOW_WIDTH){
		ball->rect.x = BALL_SPAWN_X;
		ball->rect.y = BALL_SPAWN_Y;
		ball->vel_x *= -1;
		player->score++;
		sprintf(score_str, "%d  %d", player->score, cpu->score);
	}
	if(ball->rect.y <= 0){
				ball->rect.y = 0;
				ball->vel_y *= -1;
			}
	if(ball->rect.y + ball->rect.h >= WINDOW_HEIGHT){
				ball->rect.y = WINDOW_HEIGHT - ball->rect.h;
				ball->vel_y *= -1;
			}
	if(ball->rect.y + ball->rect.h >= player->rect.y && ball->rect.y <= player->rect.y + player->rect.h && ball->rect.x >= player->rect.x && ball->rect.x <= player->rect.x + player->rect.w){
		ball->rect.x = player->rect.x + player->rect.w;
		ball->vel_x *= -1;
	}
	if(ball->rect.y + ball->rect.h >= cpu->rect.y && ball->rect.y - ball->rect.h <= cpu->rect.y + cpu->rect.h && ball->rect.x + ball->rect.w >= cpu->rect.x && ball->rect.x <= cpu->rect.x + cpu->rect.w){
		ball->rect.x = cpu->rect.x - ball->rect.w;
		ball->vel_x *= -1;
	}
	return;
}
