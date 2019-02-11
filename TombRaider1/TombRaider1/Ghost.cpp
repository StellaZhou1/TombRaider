#include"Ghost.h"
#include "stdafx.h"
Ghost::Ghost()
{

}
Ghost::Ghost(int hp = 1000, int x = 30, int y = 30, int atk = 100, int dir = 0, int speed = 8)
{
	this->hp = hp;
	this->x = x;
	this->y = y;
	this->atk = atk;
	this->dir = dir;
	this->speed = speed;
}
void Ghost::attack()
{

}
void Ghost::stay()
{

}
void Ghost::follow()
{

}
void Ghost::hide()
{

}
