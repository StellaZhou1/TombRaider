#include"People.h"
#include "stdafx.h"
People::People()
{
	hp = 1000;
	this->isAlive = true;
}
People::People(int hp=1000, int x=30, int y=30, int dir=0,int speed=10)
{
	this->hp = hp;
	this->x = x;
	this->y = y;
	this->dir = dir;
	this->speed = speed;
	this->isAlive = true;
}
void People::setx(int x)
{
	this->x = x;
}
void People::sety(int y)
{
	this->y = y;
}
void People::putBomb()
{

}
void People::move(int targetdir, int speed)
{
	//根据原来位置修正人物位置，暂时这样
	switch (targetdir)
	{
	case 0:
	{
		switch (dir)
		{
		case 0:
			y -= speed;
			break;
		case 1:
			//x -= 1;
			y -= speed;
			break;
		case 2:
			//x += 2;
			y -= speed;
			break;
		case 3:
			//x += 2;
			y -= speed;
			break;
		}
		if (y < 0)
			y = 0;

	}
	break;
	case 1:
	{
		y += speed;
			/*
		switch (dir)
		{
		case 0:
			x += 1;
			y += speed-2;
			break;
		case 1:
			y += speed;
			break;
		case 2:
			x += 3;
			y += speed-4;
			break;
		case 3:
			x += 3;
			y += speed-4;
			break;
		}*/
		if (y > 590)
			y = 590;
	}
	break;
	case 2:
	{
		x -= speed;
		/*
		switch (dir)
		{
		case 0:
			x -= speed+2;

			break;
		case 1:
			x -= speed+3;
			y += 4;
			break;
		case 2:
			x -= speed;

			break;
		case 3:
			x -= speed;

			break;
		}*/
		if (x < 0)
			x = 0;
		if (y > 590)
			y = 590;
	}
	break;
	case 3:
	{
		x += speed;
			/*
		switch (dir)
		{
		case 0:
			x += speed-2;

			break;
		case 1:
			x += speed-3;
			y += 4;
			break;
		case 2:
			x += speed;

			break;
		case 3:
			x += speed;

			break;
		}*/
		if (x > 620)
			x = 620;
		if (y > 590)
			y = 590;
	}
	break;
	
	}
	dir = targetdir;
}