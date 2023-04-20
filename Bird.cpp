
#include "Bird.hpp"
#include <ComFunc.hpp>

Bird::Bird()
{
    is_falling = false;
    y_val = 0;
    x_val = 0;
    is_die = false;
    x_pos = 100;
    y_pos = 100;
}

Bird::~Bird()
{
    Free();
}

void Bird::Action(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
        {
            if (is_falling == false)
            {
                y_val = -15;
            }
            break;
        }
        case SDLK_LEFT:
        {
            if (is_falling == false)
            {
                x_val = -10;
            }
            break;
        }
        case SDLK_RIGHT:
        {
            if (is_falling == false)
            {
                x_val = 10;
            }
            break;
        }
        case SDLK_DOWN:
        {
            if (is_falling == false)
            {
                y_val = 1;
            }
            break;
        }
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
        {
            y_val = 10;
        }
        break;

        case SDLK_LEFT:
        {
            x_val = 0;
        }
        break;
        case SDLK_RIGHT:
        {
            x_val = 0;
        }
        break;
        case SDLK_DOWN:
        {
            y_val = 10;
        }
        break;
        }
    }
}


bool Bird::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Core::LoadImage(path, screen);
    return ret;
}

void Bird::Show(SDL_Renderer* des)
{
    Core::Render(des);
}

void Bird::Falling(SDL_Renderer* des)
{  
    rect.y += y_val;
    rect.x += x_val;
    if ((rect.y + rect.h) >= groundOfMap)
    {
        LoadImg("image//shiba-dark.png", des);
        is_falling = true;
        Ground(des);
    } 
}


void Bird::Ground(SDL_Renderer* screen)
{
    y_val = 0;
    x_val = 0;
    rect.y = groundOfMap - rect.h;
    is_die = true;
}
