#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "init.h"
#include "pipeline.h"

using namespace std;

//const int SCREEN_WIDTH = 600;
//const int SCREEN_HEIGHT = 600;
const int UPSPEED = 100;
const int GRAVITY = 5;

void waitUntilKeyPressed();
void updateBird(SDL_Renderer* &renderer, SDL_Rect* &bird, const int GRAVITY);
void updateRenderer(SDL_Renderer* &renderer);
void updatePipe(SDL_Renderer* &renderer, Pipeline &pipe, const int velocity);


int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // Your drawing code here
    SDL_Rect* bird;
    bird->x = 150;
    bird->y = SCREEN_HEIGHT/2;
    bird->w = 30;
    bird->h = 30;

    Pipeline *pipes[3];
    pipes[0] = new Pipeline;
    pipes[1] = new Pipeline;
    pipes[2] = new Pipeline;
    int velocity = 3;

    while (bird->y<SCREEN_HEIGHT)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        updateBird(renderer, bird, GRAVITY);
        updatePipe(renderer, *pipes[0], velocity);
        if (pipes[0]->upPipe.x < SCREEN_WIDTH/2)
            updatePipe(renderer, *pipes[1], velocity);
        if (pipes[1]->upPipe.x < SCREEN_WIDTH/2)
            updatePipe(renderer, *pipes[2], velocity);
        if (pipes[0]->upPipe.x + pipes[0]->upPipe.w < 0)
        {
            delete pipes[0];
            pipes[0] = pipes[1];
            pipes[1] = pipes[2];
            pipes[2] = new Pipeline;
        }
        updateRenderer(renderer);
    }

    // use SDL_RenderPresent(renderer) to show it

	waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void updatePipe(SDL_Renderer* &renderer, Pipeline &pipe, const int velocity)
{
    pipe.upPipe.x = pipe.upPipe.x - velocity;
    SDL_RenderFillRect(renderer, pipe.get_UpPipe_Pointer());
    pipe.downPipe.x = pipe.downPipe.x - velocity;
    SDL_RenderFillRect(renderer, pipe.get_DownPipe_Pointer());
}

void updateBird(SDL_Renderer* &renderer, SDL_Rect* &bird, const int GRAVITY)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN)
        if (e.key.keysym.sym == SDLK_SPACE)
            bird->y = bird->y - UPSPEED;
    bird->y = bird->y + GRAVITY;
    if (bird->y < 0) bird->y = 0;
    SDL_RenderFillRect(renderer,bird);
}

void updateRenderer(SDL_Renderer* &renderer)
{
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
