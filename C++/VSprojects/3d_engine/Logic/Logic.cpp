#include "Logic.h"

Player *player;
Rect *my_rect;

void Logic::GameInit()
{
	player = new Player(0.f, 0.f, -0.1f, 0.f, 0.f);
	my_rect = new Rect(0.3f, 0.2f, 0.1f, 0.1f);
}

void Logic::GameClose()
{
	delete my_rect;
	delete player;
}
