/*
 * OnePlayer.h
 *
 *  Created on: Oct. 27, 2018
 *      Author: Levi
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include <SDL2/SDL.h>
#include "Ball.h"
#include "Paddle.h"

void eventHandler(SDL_Event event, Paddle* player1, Paddle* player2, int* running, int* paused);
void one_player_logic(SDL_Event event, int* running, Ball* ball, Paddle* player, Paddle* cpu, char* score_str, int* paused);
void two_player_logic(SDL_Event event, int* running, Ball* ball, Paddle* player1, Paddle* player2, char* score_str, int* paused);

#endif /* GAMESCENE_H_ */
