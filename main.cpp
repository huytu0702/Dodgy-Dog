#include <Core.hpp>
#include <ComFunc.hpp>
#include <Bird.hpp>
#include <Time.hpp>
#include <Threat.hpp>
#include <iostream>
#include <TextShow.hpp>

Core Lbackground;	
Core LLand;
Core LGameOver;
Bird bird;
Threat threat[3];
TTF_Font* font_text = NULL;
TTF_Font* font_MENU = NULL;
Mix_Chunk* sound = NULL;

//Window
bool Init()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0)
		return false;
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //thiet lap che do ti le voi chat luong
	//tao cua so window
	window = SDL_CreateWindow("Dodgy Dog", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		success = false;
	}
	else
	{
		screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(screen, 0, 255, 0, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)) && imgFlags)
				success = false;
		}

		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_text = TTF_OpenFont("font//ARCADE.ttf", 50);
		if (font_text == NULL)
		{
			success = false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			success = false;
		}
		else
		{
			sound = Mix_LoadWAV("sound//Dod.wav");
		}


		font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
		if (font_MENU == NULL)
		{
			return false;
		}
	}
		
	

	return success;
}
//Load Background
bool LoadBackground()
{
	bool ret = Lbackground.LoadImage("image//background-night.png", screen);
		if (ret == false)
			return false;
	return true;
}
//Load land
bool loadLand()
{
	bool ret = LLand.LoadImage("image//land - Copy.png", screen);
	if (ret == false)
		return false;
	return true;
}
//load menu
bool LoadGameOver()
{
	bool ret = LGameOver.LoadImage("image//gameover11.png", screen);
	if (ret == false)
		return false;
	return true;
}


bool loadThreat()
{
	bool ret = threat[0].LoadImage("image//plane.png", screen);
	bool ret1 = threat[1].LoadImage("image//plane.png", screen);
	bool ret2 = threat[2].LoadImage("image//plane.png", screen);
	if (ret == false && ret1 == false && ret2 == false)
		return false;
	return true;
}

void close()
{
	Lbackground.Free();
	LLand.Free();
	bird.Free();
	LGameOver.Free();
	threat->Free();

	SDL_DestroyRenderer(screen);
	screen = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	

	IMG_Quit();
	SDL_Quit();
}


// Check collision
bool checkCollision() {
	if (bird.getXPOS() + bird_w > threat[0].getXPOS() && bird.getXPOS() < threat[0].getXPOS() + THREAT_WIDTH && bird.getYPOS() + bird_h > threat[0].getYPOS() && bird.getYPOS() < threat[0].getYPOS() + THREAT_HEIGHT
		|| bird.getXPOS() + bird_w > threat[1].getXPOS() && bird.getXPOS() < threat[1].getXPOS() + THREAT_WIDTH && bird.getYPOS() + bird_h > threat[1].getYPOS() && bird.getYPOS() < threat[1].getYPOS() + THREAT_HEIGHT
		|| bird.getXPOS() + bird_w > threat[2].getXPOS() && bird.getXPOS() < threat[2].getXPOS() + THREAT_WIDTH && bird.getYPOS() + bird_h > threat[2].getYPOS() && bird.getYPOS() < threat[2].getYPOS() + THREAT_HEIGHT) {
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	//land & background loop
	int land_x = 0;
	
	//khoi tao
	if (Init() == false)
		return -1;

	//Set fps
	Time fps;

	//Text
	TextShow text_count_;
	text_count_.SetColor(TextShow::WHITE_TEXT);
	bool is_running = true;
	

	//load background va khoi tao vi tri
	if (LoadBackground() == false)
		return -1;
	Lbackground.SetRect(0, -60);

	//load land va khoi tao vi tri
	if (loadLand() == false)
		return -1;
	LLand.SetRect(0, groundOfMap);

	//Load gameover
	if (LoadGameOver() == false)
		return -1;
	LGameOver.SetRect(0, 0);
	
/************************************Bird***************************************/
	//load anh va khoi tao vi tri
	bool ret = bird.LoadImg("image//shiba.png", screen);
	bird.SetRect(100, 200);
	if (ret == false)
	{
		return -1;
	}

/********************************************************************************/
	//Threat: load anh va khoi tao vi tri
	if (loadThreat() == false)
		return -1;
	threat[0].SetRect(SCREEN_W, 0);
	threat[1].SetRect(SCREEN_W - 50, 50);
	threat[2].SetRect(SCREEN_W + 55, 50);

	//text
	TextShow text_count;
	text_count.SetColor(TextShow::WHITE_TEXT);
	//Game
	bool endgame = false;
	int up_level_count = 0; // bien tang do kho game
	Mix_PlayChannel(-1, sound, 0);
	while (true)
	{
		fps.start(); //set fps
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}

			
			bird.Action(event, screen); // move
			
		}
		
		SDL_SetRenderDrawColor(screen, 0, 255, 0, 255);
		SDL_RenderClear(screen);

		bool is_fallling = bird.GetFalling();
		if (bird.GetFalling() == true)
		{
			
			//std::cout << "You lose! Your score is: " << up_level_count << std::endl;
				is_running = false;
				up_level_count = 0;
		} 
	
		if (bird.getXPOS() < 0 || bird.getYPOS() < 0 || bird.getXPOS() > SCREEN_W || bird.getYPOS() > SCREEN_W)
		{
			//std::cout << "You lose! Your score is: " << up_level_count << std::endl;
			is_running = false;
			up_level_count = 0;
		}
		

		Lbackground.Render(screen, NULL); //dua background len man hinh

/*********************land loop******************************/

			land_x -= 2;
			LLand.SetRect(land_x, groundOfMap);
			LLand.Render(screen, NULL);
			LLand.SetRect(land_x + SCREEN_W, groundOfMap);
			LLand.Render(screen, NULL);
			if (land_x <= -SCREEN_W)
			{
				land_x = 0;
			}
		
/***************************************************************/
			

		bird.Falling(screen);

		//Threat move
		if (up_level_count <= 5)
		{
			threat[0].MoveThreat();
			threat[1].MoveThreat();
		}
		else if (up_level_count <= 8)
		{
			threat[0].MoveThreat();
			threat[1].MoveThreat();
			threat[2].MoveThreat();
			
		}
		else if (up_level_count <= 15)
		{
			threat[0].MoveThreat();
			threat[1].MoveThreat();
			threat[2].MoveThreat();
			threat[2].MoveThreatLvUp();
		}
		else
		{
			threat[0].MoveThreat();
			threat[1].MoveThreatLvUp();
			threat[1].MoveThreat();
			threat[2].MoveThreat();
			threat[2].MoveThreat();
			threat[2].MoveThreatLvUp();
		}
		if (threat[0].getXPOS() == bird.getXPOS()) up_level_count++;

		//Check va cham
		if (checkCollision()) {
			//std::cout << "You lose! Your score is: " << up_level_count << std::endl;
			is_running = false;
			up_level_count = 0;
		}
		
		//Show
		bird.Show(screen);
		if (up_level_count <= 5)
		{
			threat[0].Show(screen);
			threat[1].Show(screen);
		}
		else
		{
			threat[0].Show(screen);
			threat[1].Show(screen);
			threat[2].Show(screen);

		}

		//Show game score
		int count = up_level_count;
		std::string count_str = std::to_string(count);
		text_count.SetText(count_str);
		text_count.LoadText(font_text, screen);
		text_count.RenderText(screen, SCREEN_W * 0.49, 434);
		
		if (is_running == false) {
			LGameOver.Render(screen, NULL);
			Mix_FreeChunk(sound);
			Mix_CloseAudio();
		}
	
		
	

		SDL_RenderPresent(screen);
		text_count.Free();
		//Set fps, can bang thoi gian tat ca frame
		int val1 = fps.get_ticks(); // real time
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) // 1000 / frame... 1 lan chay mat ? ms
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());  // delay time 
		}

	}
	
	Mix_FreeChunk(sound);
	Mix_CloseAudio();
	
	close();
	return 0;
}
