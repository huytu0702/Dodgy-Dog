#include <TextShow.hpp>

TextShow::TextShow()
{
	text_color.r = 255;  
	text_color.g = 255;
	text_color.b = 255;
}

TextShow::~TextShow()
{

}

bool TextShow::LoadText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, s_val.c_str(), text_color);
	if (text_surface)
	{
		texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
		if (texture_)
		{
			widthText = text_surface->w;
			heightText = text_surface->h;
		}

		SDL_FreeSurface(text_surface);
	}

	return texture_ != NULL;
}

void TextShow::Free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}

void TextShow::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextShow::SetColor(int type) // xetnhanh
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0 };	
		text_color = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0, 0, 0 };
		text_color = color;
	}
}

void TextShow::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect Renderquad = { x, y, widthText, heightText};
	if (clip != NULL)
	{
		Renderquad.w = clip->w;
		Renderquad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, texture_, clip, &Renderquad, angle, center, flip);
}