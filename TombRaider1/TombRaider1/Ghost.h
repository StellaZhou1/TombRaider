#ifndef GHOST
#define GHOST
class Ghost
{
public:
	Ghost();
	Ghost(int hp,int x,int y,int atk,int dir,int speed);
	int hp=1000;
	int x=60;
	int y=60;
	int atk=100;
	int dir=0;
	int speed=10;
	int count=0;
	int x_axis;
	int y_axis;
private:
	void attack();
	void stay();
	void follow();
	void hide();
};

#endif
