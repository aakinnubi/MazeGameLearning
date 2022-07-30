#include "Player.h"
#include <iostream>
using namespace std;
constexpr char kPlayerSymbol = '@';

constexpr int kStartingNumberOfLives = 3;

Player::Player() :PlacableActor(0,0)
, m_pCurrentKey(nullptr)
,m_money(0)
,m_lives(kStartingNumberOfLives)
{
}

Player::~Player()
{
}





bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(int color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (m_pCurrentKey) {
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
std::cout << kPlayerSymbol;
}

//void Player::Draw()
//{
//	cout << '@';
//}
