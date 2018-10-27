/*
 * renderer.h
 *
 *  Created on: Oct. 27, 2018
 *      Author: Levi
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Ball.h"
#include "Paddle.h"
#include "Menu.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)


int Init(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font);
int Window_Init(SDL_Window** window);
int Renderer_Init(SDL_Renderer** renderer, SDL_Window* window);
int Font_Init(TTF_Font** font, SDL_Renderer* renderer, SDL_Window* window);
void quit(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);
void renderScore(SDL_Renderer *renderer, const char *score_str, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);
void redraw(SDL_Renderer* renderer);
void drawGame(SDL_Renderer *renderer, Paddle player, Paddle cpu, Ball ball);
void drawMenuText(SDL_Renderer *renderer, TTF_Font* font, int players);
#endif /* RENDERER_H_ */
