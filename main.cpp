#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Flappy Bird";

struct Pipeline
{
    SDL_Rect upPipe, downPipe;
    Pipeline()
    {
        upPipe.w = 100;
        upPipe.h = rand()%(300);
        upPipe.x = SCREEN_WIDTH;
        upPipe.y = 0;
        downPipe.w = 100;
        downPipe.h = rand() % (300);
        downPipe.x = SCREEN_WIDTH;
        downPipe.y = SCREEN_HEIGHT - downPipe.h;
    }
    SDL_Rect* get_UpPipe_Pointer()
    {
        return &upPipe;
    }
    SDL_Rect* get_DownPipe_Pointer()
    {
        return &downPipe;
    }
} ;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void updateBird(SDL_Renderer* &renderer, SDL_Rect* &bird, int gravity);
void updateRenderer(SDL_Renderer* &renderer);
void updatePipe(SDL_Renderer* &renderer, Pipeline &pipe, int velocity);


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

    int gravity = 4, velocity = 5;
    Pipeline *first = new Pipeline, *second = new Pipeline, *third = new Pipeline;

    while (bird->y<SCREEN_HEIGHT)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        updateBird(renderer, bird, gravity);
        updatePipe(renderer, *first, velocity);
        if (first->upPipe.x < 300)
            updatePipe(renderer, *second, velocity);
        if (second->upPipe.x < 300)
            updatePipe(renderer, *third, velocity);
        if (first->upPipe.x+100 < 0)
        {
            delete first;
            first = second;
            second = third;
            third = new Pipeline;
        }
        updateRenderer(renderer);
    }

    // use SDL_RenderPresent(renderer) to show it

	waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void updatePipe(SDL_Renderer* &renderer, Pipeline &pipe, int velocity)
{
    pipe.upPipe.x = pipe.upPipe.x - velocity;
    SDL_RenderFillRect(renderer, pipe.get_UpPipe_Pointer());
    pipe.downPipe.x = pipe.downPipe.x - velocity;
    SDL_RenderFillRect(renderer, pipe.get_DownPipe_Pointer());
}

void updateBird(SDL_Renderer* &renderer, SDL_Rect* &bird, int gravity)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN)
        if (e.key.keysym.sym == SDLK_UP)
            gravity = gravity - 100;
    bird->y = bird->y + gravity;
    SDL_RenderFillRect(renderer,bird);
}

void updateRenderer(SDL_Renderer* &renderer)
{
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
