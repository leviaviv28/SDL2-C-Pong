/*
 * Ball.h
 *
 *  Created on: Oct. 27, 2018
 *      Author: Levi
 */

#ifndef BALL_H_
#define BALL_H_

#include <SDL2/SDL.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BALL_SPAWN_X ((WINDOW_WIDTH / 2) - 8)
#define BALL_SPAWN_Y ((WINDOW_HEIGHT / 2) - 8)

typedef struct{
	SDL_Rect rect;
	int vel_x;
	int vel_y;
}Ball;

#include "Paddle.h"

void ballLogic(Ball* ball, Paddle* player, Paddle* cpu, char* score_str);

#endif /* BALL_H_ */
