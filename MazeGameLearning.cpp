// MazeGameLearning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;
int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width,bool& playerHasKey);
constexpr char kPlayerSymbol = '@';
int main()
{
	constexpr int kwidth = 25;
	constexpr int kheight = 15;
	char levelArray[]{  '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','*','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-','-','-','-','-','-','-','-','-','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ',' ',' ',' ','X','|',
						'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+'
};
	int playerX = 1;
	int playerY = 1;
	bool playerHasKey = false;
	bool gameOver = false;
	while (!gameOver) {
		system("cls");
		DrawLevel(levelArray, kwidth, kheight, playerX, playerY);
		gameOver = UpdatePlayerPosition(levelArray,playerX, playerY,kwidth, playerHasKey);
	}

}


int GetIndexFromCoordinates(int x, int y, int width)
{
	return x+y*width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (playerX == x && playerY == y) {
				cout << kPlayerSymbol;
			}
			else {
				int index = GetIndexFromCoordinates(x, y, width);
				cout << level[index];
			}

		}
		cout << endl;
	}
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width,bool& playerHasKey)
{
	char input = _getch();
	int newPlayerX = playerX;
	int newPlayerY = playerY;
	switch (input)
	{
		//player Y decreases when W is pressed
	case 'w':
	case'W':
	{
		newPlayerY--;
		break;
	}
	//player Y increases when S is pressed
	case 's':
	case 'S':
	{
		newPlayerY++;
		break;
	}
	case 'a':
	case 'A': {
		newPlayerX--;
		break;
	}
	case 'd':
	case 'D': {
		newPlayerX++;
		break;
	}
	default:
		break;
	}
	//we get us where the player wants to move
	int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);
	if (level[index] == ' ') {
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == '*') {
		playerHasKey = true;
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == 'D' && playerHasKey) {
		level[index] = ' ';
		playerHasKey = false;
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == 'X') {
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		return true;
	}
	return false;
}
