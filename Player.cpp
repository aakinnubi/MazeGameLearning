#include "Player.h"
#include <iostream>
constexpr char kPlayerSymbol = '@';

Player::Player() :m_hasKey(false)
{
}

Player::~Player()
{
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
std::cout << kPlayerSymbol;
}