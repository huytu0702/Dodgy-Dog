#include "Time.hpp"
#include "ComFunc.hpp"

Time::Time()
{
    start_tick_ = 0;
    paused_ticks_ = 0;
    is_paused_ = false;
    is_started_ = false;
}

void Time::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
}

void Time::stop()
{
    is_started_ = false;
    is_paused_ = false;
}

void Time::pause()
{
    if ((is_started_ == true) && (is_paused_ == false))
    {
        is_paused_ = true;
        paused_ticks_ = SDL_GetTicks() - start_tick_;
    }
}

void Time::resume()
{
    if (is_paused_ == true)
    {
        is_paused_ = false;
        //Reset the starting ticks
        start_tick_ = SDL_GetTicks() - paused_ticks_;
        //Reset the paused ticks
        paused_ticks_ = 0;
    }
}

int Time::get_ticks()
{
    if (is_started_ == true)
    {
        //If the timer is paused
        if (is_paused_ == true)
        {
            return paused_ticks_;
        }
        else
        {
            return SDL_GetTicks() - start_tick_;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Time::is_started()
{
    return is_started_;
}

bool Time::is_paused()
{
    return is_paused_;
}