#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL2/SDL.h>
#include "Ball.h"

typedef struct{
	SDL_Rect rect;
	int score;
	int controls[2];
}Paddle;

void cpuLogic(Paddle *cpu, Ball* ball);
void playerLogic(Paddle* player);

#endif /* PADDLE_H_ */
