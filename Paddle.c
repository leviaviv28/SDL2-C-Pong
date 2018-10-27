#include "Ball.h"
#include "Paddle.h"

void cpuLogic(Paddle *cpu, Ball* ball){
	if(ball->rect.y >= cpu->rect.y && ball->rect.x > WINDOW_WIDTH - WINDOW_WIDTH / 4) cpu->rect.y += 5;
	else if(ball->rect.y <= cpu->rect.y + cpu->rect.h && ball->rect.x > WINDOW_WIDTH - WINDOW_WIDTH / 4) cpu->rect.y -= 5;
	else{
		if(cpu->rect.y + (cpu->rect.h / 2) > (WINDOW_HEIGHT / 2) + 10) cpu->rect.y -= 5;
		else if(cpu->rect.y + (cpu->rect.h / 2) < (WINDOW_HEIGHT / 2) - 10) cpu->rect.y += 5;
	}
	if(cpu->rect.y <= 0) cpu->rect.y = 0;
	else if(cpu->rect.y + cpu->rect.h >= WINDOW_HEIGHT) cpu->rect.y = WINDOW_HEIGHT - cpu->rect.h;
}

void playerLogic(Paddle* player, int up, int down){
	if(up && !down) player->rect.y -= 5;
	if(down && !up) player->rect.y += 5;
	if(player->rect.y <= 0) player->rect.y = 0;
	if(player->rect.y + player->rect.h >= WINDOW_HEIGHT) player->rect.y = WINDOW_HEIGHT - player->rect.h;
	return;
}
