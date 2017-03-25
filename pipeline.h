const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

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
