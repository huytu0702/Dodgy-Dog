#pragma once

#include <Core.hpp>
#include <ComFunc.hpp>

class Bird : public Core
{
public: 
	Bird();
	~Bird();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void Action(SDL_Event event_, SDL_Renderer* screen); //handle input
	
	
	//Hanh dong
	void Falling(SDL_Renderer* des);
	bool GetFalling() { return is_falling; }
	void SetFalling(bool falling) { is_falling = falling; }
	void Ground(SDL_Renderer* screen);
	bool Die() const { return is_die; }
private:
	//bien -> khi an tang bao nhieu
	int x_val;
	int y_val;

	int x_pos;
	int y_pos;
	bool is_die;
	bool is_falling;

};