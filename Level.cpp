#include <windows.h>
#include "Level.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Level.h"
#include "Player.h"
#include "Enemy.h";
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"


constexpr char WAL = (char)219;

Level::Level()
	:m_pLevelData(nullptr)
	,m_height(0)
	,m_width(0)
{
}

Level::~Level()
{
	if (m_pLevelData != nullptr) {
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}

	while (!m_pActors.empty()) {

		delete m_pActors.back();
		m_pActors.pop_back();
	}
}

bool Level::Load(std::string levelName, int* playerX, int* playerY)
{
	levelName.insert(0, "./");
	std::ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile) {
		std::cout << "Opening file failed!" << std::endl;
		return false;
	}
	else {
		constexpr int tempSize = 25;
		char temp[tempSize];
		levelFile.getline(temp, tempSize, '\n');
		m_width = atoi(temp);

		// Read height 
		levelFile.getline(temp, tempSize, '\n');
		m_height = atoi(temp);

		// Read level
		m_pLevelData = new char[m_width * m_height];
		/*m_height =m_width;*/
		m_pLevelData = new char[m_width * m_height];
		levelFile.read(m_pLevelData,(long long) m_width * (long long)m_height);
		bool anyWarnings = Convert(playerX,playerY);
		//levelArray, width, height, playerX, playerY
		if (anyWarnings) {
			std::cout << "There were some warnings in the level data, see above." << std::endl;
			system("pause");
		}
		return m_pLevelData;
	}
	return false;
}

void Level::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, (int)ActorColor::Regular);

	//Draw the level
	for (int y = 0; y < GetHeight(); ++y) {
		for (int x = 0; x < GetWidth(); ++x) {
			int indexToPrint = GetIndexFromCoordinates(x, y);
			std::cout << m_pLevelData[indexToPrint];
		}
		std::cout << std::endl;
	}

	COORD actorCursorPosition;

	//Draw actors

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor) {
		if ((*actor)->IsActive()) {
			actorCursorPosition.X = (*actor)->GetXPosition();
			actorCursorPosition.Y = (*actor)->GetYPosition();
			SetConsoleCursorPosition(console, actorCursorPosition);
			(*actor)->Draw();
		}
	}
}

PlacableActor* Level::UpdateActors(int x, int y)
{ 
	PlacableActor* collidedActor = nullptr;
	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); actor++) {
		(*actor)->Update();
		if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition()) {

			//should only be able to collide with one actor
			assert(collidedActor == nullptr);
			collidedActor = (*actor);
		}
	}
	return collidedActor;
}

bool Level::isSpace(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsWall(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == WAL;
}

bool Level::Convert(int* playerX, int* playerY)
{
	bool anyWarnings = false;
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			int index = GetIndexFromCoordinates(x, y);
			switch (m_pLevelData[index])
			{
			case'+':
			case'-':
			case'|':
				m_pLevelData[index] = WAL;
				break;
			case 'r':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Red));
				break;
			case 'g':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Green));
				break;
			case 'b':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Blue));
				break;
			case 'R':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Red, ActorColor::SolidRed));
				break;
			case 'G':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Red, ActorColor::SolidRed));
				break;
			case 'B':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Red, ActorColor::SolidBlue));
				break;
			case 'X':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Goal(x, y));
				break;
			case '$':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Money(x, y,1+rand()%5));
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr) {
					*playerX = x;
					*playerY = y;
				}
				break;
			case 'e':

				//create regular enemy and clear level
				m_pActors.push_back(new Enemy(x, y));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case 'h':
				//create horizontal enemy and clear level
				m_pActors.push_back(new Enemy(x, y, 3, 0));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case 'v':
				//create vertical enemy and clear level
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Enemy(x, y, 0, 2));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case ' ':
				break;
			default:
				std::cout << "Invalid character in level file: " << m_pLevelData[index] << std::endl;
				anyWarnings = true;
				break;
			}
		}
	}
	return anyWarnings;
}

int Level::GetIndexFromCoordinates(int x, int y)
{
	return x + y *m_width;
}
