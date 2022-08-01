#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int deltX, int deltaY) : PlacableActor(x,y)
,m_currentMovementX(0)
,m_currentMovementY(0)
,m_directionX(0)
,m_directionY(0)
,m_movementInX(deltX)
,m_movementInY(deltaY)
{
	InitDirection();
}
void Enemy::Draw()
{
	std::cout << (char)153;
}
void Enemy::Update()
{
	if (m_movementInX != 0) {
		UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
	}
	if (m_movementInY != 0) {
		UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
	}
	this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y + m_directionY);
}

void Enemy::InitDirection()
{
	if (m_movementInX != 0) {
		m_directionX = 1;
	}
	if (m_movementInY != 0) {
		m_directionY = 1;
	}
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	//go back or go forward depending on what happens
	current += direction;
	if (std::abs(current) > movement) {
		current = movement * direction;
		direction *= -1;
	}
}