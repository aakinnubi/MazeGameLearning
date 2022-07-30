// MazeGameLearning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "Game.h"
#include "AudioManager.h"
using namespace std;
//int GetIndexFromCoordinates(int x, int y, int width);
//void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey);
//bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey);
//char* LoadLevel(string fileName, int& width, int& height);
//bool ConvertLevel(char* levelArray, int width, int height, int& playerX, int& playerY);
constexpr char kPlayerSymbol = '@';
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
const char GOL = 36;
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
//constexpr int kRegularColor = 7;
int main()
{

	Game myGame;
	if (myGame.Load()) {
		while (!myGame.IsGameOver()) {
			myGame.Run();
		}
		if (myGame.DidUSerQuit()) {
			cout << "Thanks for playing!" << endl;
		}
		else if (myGame.GetPlayerLives() < 0) {
			cout << "YOU LOSE!!!!" << endl;
			AudioManager::GetInstance()->PlayLoseSound();
		}
		else {
			cout << "YOU WON !!!" << endl;
			AudioManager::GetInstance()->PlayWinSound();
		}

	}
	else {
		cout << "Game did not load. Terminating Now!" << endl;
	}
	AudioManager::DestroyInstance();
	return 0;


}



