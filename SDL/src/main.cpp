#include"Game.h"
#include <stdio.h>
#include "GameStates/GSSelectLevel.h"
#include "Setting.h"

int main(int argc, char* args[])
{
//	Game* game = new Game();
	//Start up SDL and create window
	Setting::music = true;

	Setting::sfx = true;

	GSSelectLevel::LoadCSV();

	Game::GetInstance()->Run();
	//Free resources and close SDL
	Game:: GetInstance()->FreeInstance();

	GSSelectLevel::SaveCSV();

	return 0;
}