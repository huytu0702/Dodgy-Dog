#include <Core.hpp>
#include <ComFunc.hpp>
#include <Bird.hpp>
#include <Time.hpp>
#include <Threat.hpp>
#include <iostream>
#include <TextShow.hpp>
#include <vector>

using namespace std;




Core Lbackground;
Core LLand;

TTF_Font* font_text = NULL;
TTF_Font* font_MENU = NULL;
Mix_Chunk* sound = NULL;


Core LMenu;
//Window

bool InitWindow()
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
		return success;
	}
}
bool Init()
{
	bool success = true;

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
		sound = Mix_LoadWAV("sound//making my way final.wav");
	}


	font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
	if (font_MENU == NULL)
	{
		return false;
	}




	return success;
}
//Load Menu
bool LoadMenu()
{
	bool ret = LMenu.LoadImage("image//menu.png", screen);
	if (ret == false)
		return false;
	return true;
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

void close()
{
	Lbackground.Free();
	LLand.Free();

	LMenu.Free();


	SDL_DestroyRenderer(screen);
	screen = NULL;

	SDL_DestroyWindow(window);
	window = NULL;



	IMG_Quit();
	SDL_Quit();
}



int main(int argc, char* argv[])
{

	if (InitWindow() == false)
	{
		return -1;
	}







	//Load Menu
	if (LoadMenu() == false)
		return -1;
	LMenu.SetRect(0, 0);


	//load background va khoi tao vi tri
	if (LoadBackground() == false)
		return -1;
	Lbackground.SetRect(0, -60);

	//load land va khoi tao vi tri
	if (loadLand() == false)
		return -1;
	LLand.SetRect(0, groundOfMap);

	//Set fps
	Time fps;


	//Game



	bool is_running = false;
	bool quit = false;

	//Menu
	while (!quit)
	{

		LMenu.Render(screen, NULL);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // Nếu nhấn nút thoát
				quit = true;
				close();
				break;
			case SDL_MOUSEBUTTONDOWN: // Nếu nhấn chuột

				int x, y;
				SDL_GetMouseState(&x, &y); // Lấy tọa độ chuột
				if (x >= 133 && x < 223 && y >= 302 && y < 346)
				{

					SDL_DestroyTexture(LMenu.GetTexture());
					is_running = true;
					quit = true;
				}
				break;
			}

		}
		SDL_RenderPresent(screen);

	}

again_label:

	//Gameloop

	Core Lreplay;
	bool retreplay = Lreplay.LoadImage("image//replay.png", screen);
	if (retreplay == false)
		return -1;

	//khoi tao
	if (Init() == false)
		return -1;
	Mix_PlayChannel(-1, sound, 0);
	Core LGameOver;	
	//Load gameover
	bool retGameOver = LGameOver.LoadImage("image//gameOver222.png", screen);
	if (retGameOver == false)
		return -1;

	Bird bird;
	/************************************Bird***************************************/

	bool retbird = bird.LoadImg("image//shiba.png", screen);
	bird.SetRect(100, 200);
	if (retbird == false)
	{
		return -1;
	}

	Core LExit;
	bool retExit = LExit.LoadImage("image//exit.png", screen);
	if (retExit == false)
		return -1;

	/********************************************************************************/
	Threat threat[3];
	bool ret = threat[0].LoadImage("image//plane.png", screen);
	bool ret1 = threat[1].LoadImage("image//plane.png", screen);
	bool ret2 = threat[2].LoadImage("image//plane.png", screen);
	if (ret == false || ret1 == false || ret2 == false)
		return -1;
	threat[0].SetRect(SCREEN_W, 0);
	threat[1].SetRect(SCREEN_W - 50, 50);
	threat[2].SetRect(SCREEN_W + 55, 50);

	//text
	TextShow text_count;
	text_count.SetColor(TextShow::WHITE_TEXT);
	//Threat: load anh va khoi tao vi tri


	int up_level_count = 0; // bien tang do kho game

	int dem = 0;
	bool quit_game_loop = false;
	int score[2];
	score[0] = 0;
	score[1] = 0;

	//land & background loop
	int land_x = 0;

	is_running = true;
	while (is_running)
	{

		fps.start(); //set fps

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit_game_loop = true;
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
			quit_game_loop = true;
			is_running = false;
			up_level_count = 0;
		}

		if (bird.getXPOS() < 0 || bird.getYPOS() < 0 || bird.getXPOS() > SCREEN_W || bird.getYPOS() > SCREEN_W)
		{
			//std::cout << "You lose! Your score is: " << up_level_count << std::endl;
			quit_game_loop = true;
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
		if (checkCollision(bird.GetRect(), threat[0].GetRect()) == true || checkCollision(bird.GetRect(), threat[1].GetRect()) == true || checkCollision(bird.GetRect(), threat[2].GetRect()) == true) {
			//std::cout << "You lose! Your score is: " << up_level_count << std::endl;
			quit_game_loop = true;
			up_level_count = 0;
			is_running = false;
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

		if (quit_game_loop == true)
		{

			dem++;

			is_running = false;



		}

		//Show game score

		int count = up_level_count;
		score[dem] = count;
		std::string count_str = std::to_string(count);
		text_count.SetText(count_str);
		text_count.LoadText(font_text, screen);
		if (!quit_game_loop) text_count.RenderText(screen, SCREEN_W * 0.49, 434);
		else text_count.RenderText(screen, -SCREEN_W * 0.49, -434);

		if (is_running == false) {
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



	while (quit_game_loop)
	{
		LGameOver.SetRect(-73, -50);

		LGameOver.Render(screen, NULL);

		Lreplay.SetRect(57, 337);
		Lreplay.Render(screen, NULL);

		LExit.SetRect(197, 337);
		LExit.Render(screen, NULL);

		std::string count_str = std::to_string(score[0]);
		text_count.SetText(count_str);
		text_count.LoadText(font_text, screen);
		if (score[0] <= 9) text_count.RenderText(screen, 242, 230);
		else text_count.RenderText(screen, 228, 230);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: // Nếu nhấn nút thoát
				quit_game_loop = false;
				close();
				break;

			case SDL_MOUSEBUTTONDOWN: // Nếu nhấn chuột
			{
				int x, y;
				SDL_GetMouseState(&x, &y); // Lấy tọa độ chuột
				if (x >= 57 && x < 157 && y >= 337 && y < 393)
				{

					bird.Free();
					threat->Free();
					LGameOver.Free();
					LExit.Free();
					goto again_label;

				}
				if (x >= 200 && x < 300 && y >= 337 && y < 393)
				{
					quit_game_loop = false;
					bird.Free();
					threat->Free();
					LGameOver.Free();
					LExit.Free();
					close();
				}
				break;
			}

			}
			SDL_RenderPresent(screen);
		}
	}



	Mix_FreeChunk(sound);
	Mix_CloseAudio();

	close();
	return 0;
}
