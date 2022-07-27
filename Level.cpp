#include "Level.h"
#include <iostream>
#include <fstream>
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
const char GOL = 36;
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

Level::Level():m_pLevelData(nullptr),m_height(0),m_width(0)
{
}

Level::~Level()
{
	if (m_pLevelData != nullptr) {
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
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

		levelFile.getline(temp, tempSize, '\n');
		m_height = atoi(temp);

		m_pLevelData = new char[m_width * m_height];
		levelFile.read(m_pLevelData, m_width * m_height);
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

void Level::Draw(int x, int y)
{
	int index = GetIndexFromCoordinates(x, y);
	std::cout << m_pLevelData[index];
}

bool Level::IsSpace(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x,y)] == ' ';
}

bool Level::IsDoor(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == DOR;
}

bool Level::IsKey(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == KEY;
}

bool Level::IsGoal(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == GOL;
}

void Level::PickupKey(int x, int y)
{
	m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

void Level::OpenDoor(int x, int y)
{
	 m_pLevelData[GetIndexFromCoordinates(x,y)] == ' ';

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
			case'*':
				m_pLevelData[index] = KEY;
				break;
			case'D':
				m_pLevelData[index] = DOR;
				break;
			case 'X':
				m_pLevelData[index] = GOL;
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr) {
					*playerX = x;
					*playerY = y;
				}
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
	return x + y * m_width;
}
