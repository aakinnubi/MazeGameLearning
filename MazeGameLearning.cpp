// MazeGameLearning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;
int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY);
void UpdatePlayerPosition(int& playerX, int& playerY);
string kPlayerSymbol = "@";
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
	while (true) {
		system("cls");
		DrawLevel(levelArray, kwidth, kheight, playerX, playerY);
		UpdatePlayerPosition(playerX, playerX);
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

void UpdatePlayerPosition(int& playerX, int& playerY)
{
	char input = _getch();
	switch (input)
	{
		//player Y decreases when W is pressed
	case 'w':
	case'W':
	{
		playerY--;
		break;
	}
	//player Y increases when S is pressed
	case 's':
	case 'S':
	{
		playerY++;
		break;
	}
	case 'a':
	case 'A': {
		playerX--;
	}
	case 'd':
	case 'D': {
		playerX++;
	}
	default:
		break;
	}
}
