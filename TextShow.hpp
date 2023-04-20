#pragma once

#include <ComFunc.hpp>

class TextShow
{
public:
	TextShow();
	~TextShow();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	bool LoadText(TTF_Font* font, SDL_Renderer* screen);
	
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	void SetColor(int type);

	void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth() { return widthText; }
	int GetHeight() { return heightText; }

	void SetText(const std::string & text) { s_val = text; }
	std::string GetText() { return s_val; }

private:
	std::string s_val; // luu noi dung text
	SDL_Color text_color;
	SDL_Texture* texture_;  //handle text

	int widthText;
	int heightText;
};