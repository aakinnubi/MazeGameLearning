#pragma once
#include "Player.h"
#include "Level.h"
class Game
{
	Player m_player;
	Level m_level;
	bool m_isGameOver;
	bool m_UserQuit;
public:
	Game();
	~Game();
	bool Load();
	void Run();

	/*virtual ActorType GeType() override { return ActorType::Door; }*/
	bool IsGameOver();
	bool DidUSerQuit() { return m_UserQuit; }
	int GetPlayerLives() { return m_player.GetLives(); }

	void Unload();
private:
	bool Update();
	void OneOfArrowKeysPressed(int input, int& arrowInput, int& newPlayerX, int& newPlayerY);
	void Draw();

	bool HandleCollision(int newPlayerX, int newPlayerY);
	void CollidedKeyPickedUp(PlacableActor* collidedActor, int newPlayerX, int newPlayerY);
	bool ActorEnemyIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY);
	void ActorMoneyIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY);
	void ActorDoorReachedIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY);
	bool ActorGoalReachedIsCollided(PlacableActor* collidedActor, int newPlayerX, int newPlayerY);
};

