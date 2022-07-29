#include "Door.h"
#include "Windows.h"
#include <iostream>
using namespace std;
Door::Door(int x, int y, int color, int closedColor): PlacableActor(x,y,color)
,m_isOpen(false)
,m_closedColor(closedColor)
{
}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen) {
		SetConsoleTextAttribute(console, m_color);
	}
	else {
		SetConsoleTextAttribute(console, m_closedColor);
	}
	std::cout << "|";
	SetConsoleTextAttribute(console, kRegularColor);
}
