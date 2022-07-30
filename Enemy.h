#pragma once
#include "PlacableActor.h"

class Enemy : public PlacableActor {
public :
		Enemy(int x, int y, int deltX = 0, int deltaY = 0);
		virtual void Draw() override;
		virtual void Update() override;
		virtual ActorType GeType() override { return ActorType::Enemy; }
private:
	int m_movementInX;
	int m_movementInY;
	int m_currentMovementX;
	int m_currentMovementY;
	
	int m_directionX;
	int m_directionY;
	void UpdateDirection(int& current, int& direction, int& movement);
};