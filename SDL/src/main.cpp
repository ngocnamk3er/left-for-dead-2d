#include"Game.h"
#include <stdio.h>
#include "GameStates/GSSelectLevel.h"
int main(int argc, char* args[])
{
//	Game* game = new Game();
	//Start up SDL and create window

	GSSelectLevel::LoadCSV();

	Game::GetInstance()->Run();
	//Free resources and close SDL
	Game:: GetInstance()->FreeInstance();

<<<<<<< HEAD

	//add branch thanhbl
=======
	GSSelectLevel::SaveCSV();

>>>>>>> 2337de13f80e56cff026f2b492a0ea413d909d85
	return 0;
}