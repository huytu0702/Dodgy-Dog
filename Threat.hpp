#pragma once

#include <ComFunc.hpp>
#include <Core.hpp>

class Threat : public Core
{
public:
	void RandomPOS();
	void MoveThreat();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void MoveThreatLvUp();
private:
	
};