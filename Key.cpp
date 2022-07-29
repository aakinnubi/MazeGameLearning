#include "Key.h"
#include <Windows.h>
#include <iostream>

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, m_color);
	std::cout << "+";
	SetConsoleTextAttribute(console, kRegularColor);
}
