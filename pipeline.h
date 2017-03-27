const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

struct Pipeline
{
    SDL_Rect upPipe, downPipe;
    Pipeline()
    {
        upPipe.x = SCREEN_WIDTH;
        upPipe.y = 0;
        upPipe.w = 100;
        upPipe.h = rand()%(250) + 50;
        downPipe.x = SCREEN_WIDTH;
        downPipe.y = upPipe.h + 200 + rand()%100;
        downPipe.w = 100;
        downPipe.h = SCREEN_HEIGHT - downPipe.y;
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
