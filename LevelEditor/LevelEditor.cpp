// LevelEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void GetLevelDimensions(int& width, int& height);
int main()
{
	int levelWidth;
	int levelHeight;
	GetLevelDimensions(levelWidth, levelHeight);
	char* pLevel = new char[levelWidth * levelHeight];
	for (int i = 0; i < levelWidth * levelHeight; i++) {
		pLevel[i] = ' ';
	}
	delete[] pLevel;
	pLevel = nullptr;
}

void GetLevelDimensions(int& width, int& height)
{
	cout << "Enter the width of your level: ";
	cin >> width;
	cout << "Enter the height of your level: ";
	cin >> height;
}
