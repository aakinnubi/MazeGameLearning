#include "Key.h"
#include <Windows.h>
#include <iostream>

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
