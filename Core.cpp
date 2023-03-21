#include <Core.hpp>

Core::Core()
{
	texture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0; 
	rect.h = 0;
}

Core::~Core()
{
	Free();
}

bool Core::LoadImage(std::string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL; // bien ket qua
	//Doc anh
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, load_surface);
		if (newTexture != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	texture = newTexture;

	return texture != NULL;
}

void Core::Render(SDL_Renderer* des, const SDL_Rect* clip) // load anh len des
{
	SDL_Rect renderQuad = { rect.x, rect.y, rect.w, rect.h };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(des, texture, clip, &renderQuad);
}

void Core::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}