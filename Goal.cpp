#include "Goal.h"
#include <iostream>
using namespace std;
Goal::Goal(int x, int y):PlacableActor(x,y)
{
}

void Goal::Draw()
{
	std::cout << "X";
}
