#include "Player.h"
constexpr char kPlayerSymbol = '@';

Player::Player() :m_hasKey(false)
{
}

Player::~Player()
{
}

int Player::GetXPosition()
{
	return m_position.x;
}

int Player::GetYPosition()
{
	return m_position.x;
}

void Player::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

bool Player::HasKey()
{
	return m_hasKey;
}

void Player::PickupKey()
{
	m_hasKey = true;
}

void Player::UseKey()
{
	m_hasKey = false;
}

void Player::Draw()
{
}
