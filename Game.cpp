#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
Game::Game(): m_isGameOver(false)
{
}
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;
Game::~Game()
{
}

bool Game::Load()
{
	return m_level.Load("Level1.txt", m_player.GetXpositionPointer(), m_player.GetYpositionPointer());
}

void Game::Run()
{
	Draw();
	m_isGameOver = Update();
	if (m_isGameOver) {
		Draw();
	}
}

void Game::Unload()
{
}

bool Game::IsGameOver()
{
	return false;
}

bool Game::Update()
{
	char input = _getch();
	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();
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
	case' ':
		break;
	default:
		break;
	}
	//we get us where the player wants to move
	//int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);
	if (m_level.IsSpace(newPlayerX, newPlayerY)) {
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.IsKey(newPlayerX, newPlayerY)) {
		m_level.PickupKey(newPlayerX, newPlayerY);
		m_player.PickupKey();
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.IsDoor(newPlayerX,newPlayerY) && m_player.HasKey()) {
		m_level.OpenDoor(newPlayerX, newPlayerY);
		//level[index] = ' ';
		//playerHasKey = false;
		m_player.UseKey();
		m_player.SetPosition(newPlayerX, newPlayerY);
	/*	playerX = newPlayerX;
		playerY = newPlayerY;*/
	/*	PlayDoorOpenSound();*/
	}
	else if (m_level.IsDoor(newPlayerX, newPlayerY) && !m_player.HasKey()) {
		/*level[index] = ' ';
		playerHasKey = false;
		playerX = newPlayerX;
		playerY = newPlayerY;*/
		m_level.OpenDoor(newPlayerX, newPlayerY);
		m_player.SetPosition(newPlayerX, newPlayerY);
		//PlayDoorClosedSound();
	}
	else if (m_level.IsGoal(newPlayerX, newPlayerY)) {
		//level[index] = ' ';
		//playerX = newPlayerX;
		//playerY = newPlayerY;
		m_player.SetPosition(newPlayerX, newPlayerY);
		return true;
	}
	return false;
}

void Game::Draw()
{
	system("cls");
	for (int y = 0; y < m_level.GetHeight(); y++) {
		for (int x = 0; x < m_level.GetWidth(); x++) {
			if (m_player.GetXPosition() == x && m_player.GetYPosition() == y) {
				m_player.Draw();
			}
			else {
				/*int indexToPrint = GetIndexFromCoordinates(x, y, width);*/
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				if (m_level.IsDoor(x,y)) {
					if (m_player.HasKey()) {
						SetConsoleTextAttribute(console, kOpenDoorColor);
					}
					else {
						SetConsoleTextAttribute(console, kClosedDoorColor);
					}
				}
				else {
					SetConsoleTextAttribute(console, kRegularColor);
				}
				m_level.Draw(x, y);
			}

		}
		std::cout << std::endl;
	}
}
