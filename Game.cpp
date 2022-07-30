#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;




Game::Game() : m_isGameOver(false)
{
}
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
//constexpr int kRegularColor = 7;
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
	return m_isGameOver;
}

bool Game::Update()
{
	int input = _getch();
	int arrowInput = 0;
	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();
	//Start of check if one arrow key were pressed

	OneOfArrowKeysPressed(input, arrowInput, newPlayerX, newPlayerY);
	//End of check if one arrow key were pressed

	//Start of If Position never Changed

	if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition()) {
		return false;
	}

	else {
		return HandleCollision(newPlayerX, newPlayerY);
	}
}

void Game::OneOfArrowKeysPressed(int input, int& arrowInput, int& newPlayerX, int& newPlayerY)
{
	if (input == kArrowInput) {
		arrowInput = _getch();
	}
	if ((input == kArrowInput && arrowInput == kLeftArrow) || (char)input == 'A' || (char)input == 'a') {
		newPlayerX--;
	}

	else if ((input == kArrowInput && arrowInput == kRightArrow) || (char)input == 'D' || (char)input == 'd') {
		newPlayerX++;
	}
	else if ((input == kArrowInput && arrowInput == kUpArrow) || (char)input == 'W' || (char)input == 'w') {
		newPlayerY--;
	}
	else if ((input == kArrowInput && arrowInput == kDownArrow) || (char)input == 'S' || (char)input == 's') {
		newPlayerY++;
	}
	else if (input == kEscapeKey) {
		m_UserQuit = true;
	}
	else if ((char)input == 'Z' || (char)input == 'z') {
		m_player.DropKey();
	}
}

void Game::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	m_level.Draw();

	//Set cursor position for player

	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();


	//Set cursor to the end of the level

	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_level.GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);
}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
	bool isGameDone = false;
	PlacableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY);

	if (collidedActor != nullptr && collidedActor->IsActive()) {

		switch (collidedActor->GeType())
		{
		case ActorType::Enemy:
		 ActorEnemyIsCollided(collidedActor, newPlayerX, newPlayerY);
		/*	if (isCollidedDecrementLives) {

			}*/
			
			break;
		case ActorType::Money:
			ActorMoneyIsCollided(collidedActor, newPlayerX, newPlayerY);
			break;
		case ActorType::Door:
			ActorDoorReachedIsCollided(collidedActor, newPlayerX, newPlayerY);
			break;
		case ActorType::Goal:
			isGameDone = ActorGoalReachedIsCollided(collidedActor, newPlayerX, newPlayerY);
			if (isGameDone) return isGameDone;
			break;
		default:
			break;
		}




	}

	else if (m_level.isSpace(newPlayerX, newPlayerY)) {
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_level.IsWall(newPlayerX, newPlayerY)) {

	}
	return isGameDone;
}

bool Game::ActorEnemyIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY)
{
	Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
	if (collidedEnemy) {
		collidedEnemy->Remove();
		m_player.SetPosition(newPlayerX, newPlayerY);
		m_player.DecrementLives();
		if (m_player.GetLives() < 0) {
			return true;
		}
	}

	return false;
}

void Game::ActorMoneyIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY)
{
	Money* collidedMoney = dynamic_cast<Money*> (collidedActor);
	if (collidedMoney) {
		collidedMoney->Remove();
		m_player.AddMoney(collidedMoney->GetWorth());
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	Key* collidedKey = dynamic_cast<Key*> (collidedActor);
	if (collidedKey) {
		if (!m_player.HasKey()) {
			m_player.PickupKey(collidedKey);
			collidedKey->Remove();
		}
	}
}

void Game::ActorDoorReachedIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY)
{
	Door* collidedDoor = dynamic_cast<Door*> (collidedActor);
	if (collidedDoor) {
		if (!collidedDoor->IsOpen()) {
			if (m_player.HasKey(collidedDoor->GetColor())) {
				collidedDoor->IsOpen();
				collidedDoor->Remove();
				m_player.UseKey();
				m_player.SetPosition(newPlayerX, newPlayerY);
			}
			else {

			}
		}
		else {
			m_player.SetPosition(newPlayerX, newPlayerY);
		}
	}
}

bool Game::ActorGoalReachedIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY)
{
	Goal* collidedGoal = dynamic_cast<Goal*> (collidedActor);
	if (collidedGoal) {
		collidedGoal->Remove();
		m_player.SetPosition(newPlayerX, newPlayerY);
		return true;
	}
	return false;
}
