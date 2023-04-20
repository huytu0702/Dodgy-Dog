#include <Threat.hpp>

void Threat::RandomPOS()
{
	
}


bool Threat::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = Core::LoadImage(path, screen);
	return ret;
}

void Threat::Show(SDL_Renderer* des)
{
	Core::Render(des);
}

void Threat::MoveThreat()
{
	rect.x -= 10;
	//create random
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 400 - THREAT_HEIGHT);
	//
	if (rect.x + THREAT_WIDTH < 0) {
		rect.x = SCREEN_W;
		rect.y = dis(gen);
	}
}

void Threat::MoveThreatLvUp()
{
	rect.x -= 5;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 400 - THREAT_HEIGHT);
	if (rect.x + THREAT_WIDTH < 0) {
		rect.x = SCREEN_W;
		rect.y = dis(gen);
	}
}

