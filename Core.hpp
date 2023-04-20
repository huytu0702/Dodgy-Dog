#pragma once

#include <ComFunc.hpp>


class Core
{
public:
	Core();
	~Core();

	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
	int getXPOS() { return rect.x; }
	int getYPOS() { return rect.y; }
	SDL_Rect GetRect() { return rect; }
	SDL_Texture* GetTexture() { return texture; } //lay ra texture

	virtual bool LoadImage(std::string path, SDL_Renderer* renderer); // virtual -> reuse
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();



protected:
	SDL_Texture* texture; //bien luu hinh anh
	SDL_Rect rect; // bien luu kich thuoc
};