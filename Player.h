#pragma once
#include "Point.h"
#include "PlacableActor.h"
#include "Key.h"

class Player: public PlacableActor
{
public:
	Player();
	bool HasKey();
	bool HasKey(int color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoeny(int money) { m_money += money; }
	int GetMoney() { return m_money; }
	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual void Draw() override;

private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
//	Point m_position;
//	bool m_hasKey;
//public:
//	Player();
//	~Player();
//	int GetXPosition(){ return m_position.x; };
//	int GetYPosition(){ return m_position.y; };
//
//	void SetPosition(int x, int y);
//	bool HasKey();
//	void PickupKey();
//	void UseKey();
//	void Draw();
//	int* GetXpositionPointer() { return &(m_position.x); }
//	int* GetYpositionPointer() { return &(m_position.y); }
//private:


// Inherited via PlacableActor


};

