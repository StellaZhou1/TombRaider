//TombRaider1.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TombRaider1.h"
#define MAX_LOADSTRING 100
#define STONE 1
#define BOX 3
#define GRASS 2
#define HOUSE 4
#define GHOSTC 5
#define BOMBC 6
#define CHARACTER 7
//道具
#define BOOK 8
#define SHOE 9
#define BUBBLE 10
//按键ID
#define IDB_ONE 3301
#define IDB_ZERO 3300
#define IDB_TWO 3302
#define IDB_THREE 3303

#define IDD_ZERO 2200
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
MCI_OPEN_PARMS m_mciOpen;
MCI_PLAY_PARMS m_mciPlay;
struct Box {
	int hp = 600;
	bool state = true;
	int x;
	int y;
};
int map[18][18] = {};
int col = 18;
int row = 18;
int num;
int num_box = 25;
int countatk = 0;
int maxBomb = 2;
int item[25] = {};
int bombplus = 0;
HDC gvdc, gvdcbuf, gvbgdc;
HBITMAP gvbg,vicbg;
HBITMAP gv, gvn, gvmap;
HWND hBtnEtr,hBtnQuit;
HWND resEtr,resExt;
HBITMAP btnetrbmp, btnextbmp;
HWND hwnd;
HWND startwd;
DWORD tPre, tNow; 
HDC mdc, hdc, bufdc, bufdc_walk,bufdc_n;
HDC ghostdc, ghostdcn;
HDC bombdc;
HDC bgbufdc,bgdc;

HBITMAP base,box,house,housen,fullmap,girl[4],girln[4];
HBITMAP ghost[4], ghostn[4],bomb,bombn;
HBITMAP bgmap,bgpic, hp1, hp2, hp3, hp4, hp5, hp6, hp7, hp8, hp9, hp10, hp1n, hp2n, hp3n, hp4n, hp5n, hp6n, hp7n, hp8n, hp9n, hp10n;

HBITMAP bookbmp, bubblebmp,bubblen, shoebmp,shoen;
People people(1000, 30, 30, 0, 10);
LList<Ghost> ghostlist;
LList<Bomb> bomblist;
LList<Box> boxlist;
// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//函数原型
void paintMap(HDC hdc);
void paintWalk(HDC hdc);
void generateMap();
bool checkCollision(int x,int y,int targetdir,int speed);
void generateGhost(int freq);
void paintGhost(HDC hdc, Ghost g);
void initPeople(People p);
void paintBomb(HDC hdc,Bomb b);
//void findPosition(People p, Bomb b);
bool canPutBomb(Bomb *b);
void doHurt( Bomb *b);
bool getPeople(People*& it);
void checkAlive(People *it);
void gameOver(HDC hdc);
void paintbg(HDC hdc);
void initBox();
void paintvic(HDC hdc);
void initItems();
void pickItem();
void gHurtP();
void paintHP(int hp,int x,int y,HDC hdc);
void decision(int x,int y,int hp);

//决策树：决定追击or逃走or停下
void decision(int x,int y,int hp)
{
	
}

void paintHP(int hp,int x, int y, HDC hdc)
{

	switch (hp / 100)
	{
	case 1:
		SelectObject(gvdcbuf, hp1n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp1);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 2:
		SelectObject(gvdcbuf, hp2n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp2);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 3:
		SelectObject(gvdcbuf, hp3n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp3);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 4:
		SelectObject(gvdcbuf, hp4n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp4);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 5:
		SelectObject(gvdcbuf, hp5n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp5);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
	case 6:
		SelectObject(gvdcbuf, hp6n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp6);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 7:
		SelectObject(gvdcbuf, hp7n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp7);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 8:
		SelectObject(gvdcbuf, hp8n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp8);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 9:
		SelectObject(gvdcbuf, hp9n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp9);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 10:
		SelectObject(gvdcbuf, hp10n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp10);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	}

}
void gHurtP()
{
	int ix = 0;
	int iy = 0;
	//需要修改
	switch (people.dir)
	{
	case 0:
		ix = people.x / 32;
		iy = people.y / 32 - 1;
		break;
	case 1:
		ix = people.x / 32;
		iy = people.y / 32 + 1;
		break;
	case 2:
		ix = people.x / 32 - 1;
		iy = people.y / 32;
		break;
	case 3:
		ix = people.x / 32 + 1;
		iy = people.y / 32;
		break;
	}
	//==============
	
}
void pickItem()
{
	int ix = 0;
	int iy = 0;
	switch (people.dir)
	{
	case 0:
		ix = people.x / 32;
		iy = people.y / 32-1;
		break;
	case 1:
		ix = people.x / 32;
		iy = people.y / 32+1;
		break;
	case 2:
		ix = people.x / 32-1;
		iy = people.y / 32;
		break;
	case 3:
		ix = people.x / 32+1;
		iy = people.y / 32;
		break;
	}

	if (map[ix][iy] == BOOK)
	{
		bombplus++;

		map[ix][iy] = GRASS;
	}
	if (map[ix][iy] == BUBBLE)
	{
		maxBomb += 1;
		map[ix][iy] = GRASS;
	}
	if (map[ix][iy] == SHOE)
	{
		People *ptemp = new People;
		getPeople(ptemp);
		ptemp->speed += 5;
		map[ix][iy] = GRASS;
	}

}
void initItems()
{
	for (int i = 0; i < num_box; i++)
	{
		item[i] = 0;
	}
	int countit = 0;
	while(countit<10)
	{

		srand((unsigned)time(NULL));
		int book = rand() % num_box;
		if (item[book] == 0)
		{
			item[book] = BOOK;
			countit++;
		}
		int bubble = rand() % num_box;

		if (item[bubble] == 0)
		{
			item[bubble] = BUBBLE;
			countit++;
		}

		int shoe = rand() % num_box;

		if (item[shoe] == 0)
		{
			item[shoe] = SHOE;
			countit++;
		}
	}
	
}

void paintvic(HDC hdc)
{
	SelectObject(gvbgdc, vicbg);
	BitBlt(hdc, 0, 0, 593, 615, gvbgdc, 0, 0, SRCCOPY);
}
void initBox()
{
	boxlist.init();



	Box b0;
	b0.x = (row / 2) - 1;
	b0.y = (col / 2) - 1;
	boxlist.append(b0);
	Box b1;
	b1.x = (row / 2);
	b1.y = (col / 2) - 1;
	boxlist.append(b1);
	Box b2;
	b2.x = (row / 2) - 1;
	b2.y = (col / 2);
	boxlist.append(b2);
	Box b3;
	b3.x = (row / 2) + 1;
	b3.y = (col / 2);
	boxlist.append(b3);
	Box b4;
	b4.x = (row / 2) - 1;
	b4.y = (col / 2) + 1;
	boxlist.append(b4);
	Box b5;
	b5.x = (row / 2) + 1;
	b5.y = (col / 2) + 1;
	boxlist.append(b5);
	Box b6;
	b6.x = (row / 2);
	b6.y = (col / 2) + 1;
	boxlist.append(b6);
	Box b7;
	b7.x = (row / 2) - 1;
	b7.y = (col / 2) - 3;
	boxlist.append(b7);
	Box b8;
	b8.x = (row / 2) + 1;
	b8.y = (col / 2) - 2;
	boxlist.append(b8);
	Box b9;
	b9.x = (row / 2) - 1;
	b9.y = (col / 2) + 2;
	boxlist.append(b9);
	Box b10;
	b10.x = (row / 2) - 4;
	b10.y = (col / 2) - 2;
	boxlist.append(b10);
	Box b11;
	b11.x = (row / 2) +6;
	b11.y = (col / 2) + 3;
	boxlist.append(b11);
	Box b12;
	b12.x = (row / 2) - 4;
	b12.y = (col / 2) - 4;
	boxlist.append(b12);
	Box b13;
	b13.x = (row / 2) - 3;
	b13.y = (col / 2) - 4;
	boxlist.append(b13);
	Box b14;
	b14.x = (row / 2) - 3;
	b14.y = (col / 2) + 7;
	boxlist.append(b14);
	Box b15;
	b15.x = (row / 2) + 4;
	b15.y = (col / 2) + 2;
	boxlist.append(b15);
	Box b16;
	b16.x = (row / 2) + 2;
	b16.y = (col / 2) + 4;
	boxlist.append(b16);
	Box b17;
	b17.x = (row / 2);
	b17.y = (col / 2) + 3;
	boxlist.append(b17);
	Box b18;
	b18.x = (row / 2)-7;
	b18.y = (col / 2) + 2;
	boxlist.append(b18);
	Box b19;
	b19.x= (row / 2) + 5;
	b19.y = (col / 2) + 2;
	boxlist.append(b19);
	Box b20;
	b20.x = (row / 2) + 4;
	b20.y = (col / 2) + 4;
	boxlist.append(b20);
	Box b21;
	b21.x = (row / 2) - 5;
	b21.y = (col / 2) -1;
	boxlist.append(b21);
	Box b22;
	b22.x = (row / 2) - 5;
	b22.y = (col / 2) + 1;
	boxlist.append(b22);
	Box b23;
	b23.x = (row / 2) +1;
	b23.y = (col / 2) +5;
	boxlist.append(b23);
	Box b24;
	b24.x = (row / 2) - 2;
	b24.y = (col / 2) - 2;
	boxlist.append(b24);
}
void paintbg(HDC hdc)
{
	SelectObject(gvbgdc, gvbg);
	BitBlt(hdc, 0, 0, 593, 620, gvbgdc, 0, 0, SRCCOPY);
}
void gameOver(HDC hdc)
{
	int x = 30;
	int y = 50;
	//SelectObject(gvdc, gvmap);
	SelectObject(gvdcbuf, gvn);
	BitBlt(hdc, x, y, 500, 339, gvdcbuf, 0, 0, SRCAND);
	SelectObject(gvdcbuf, gv);
	BitBlt(hdc, x, y, 500, 339, gvdcbuf, 0, 0, SRCPAINT);
	//
	//把mdc上的人粘贴到hdc上
	//SelectObject(gvdc, gvmap);
	//BitBlt(hdc, x, y, 500, 339, gvdc, 0, 0, SRCCOPY);
}






void checkAlive(People *it)
{
	if (it->hp <= 0)
		it->isAlive = false;
}

bool getPeople(People*& it)
{
	*&it = &people;
	return true;
}
void doHurt(Bomb *b)
{
	/*
	People *p = new People;
	getPeople(p);
	p->hp -= 100;*/
	for(int i= b->x_axis-1;i<= b->x_axis + 1;i++)
		for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
		{
			if (!(i == b->x_axis&&i == b->y_axis))
			{
				
				if (people.x/32 == i&&people.y/32==j)
				{
					People *p = new People;
					getPeople(p);
					p->hp -= b->atk;
					//p->hp -= 100;

				}
					
				else if (map[i][j] == BOX)
				{
					//写box struct
					Box *box = new Box;
					int cntbox = 0;
					while (boxlist.fence->next != boxlist.tail)
					{

						boxlist.getValue(box);
						for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
						{
							for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
							{
								if (!(i == b->x_axis&&i == b->y_axis))
								{
									if (box->x == i && box->y == j)
									{
										box->hp -= b->atk;
										paintHP(box->hp, box->x * 32, box->y * 32, hdc);
										if (box->hp <= 0)
										{
											Box *del = new Box;
											map[i][j] = GRASS;
											boxlist.remove(*del);
											if (item[cntbox] == BOOK)
												map[i][j] = BOOK;
											else if (item[cntbox] == SHOE)
												map[i][j] = SHOE;
											else if (item[cntbox] == BUBBLE)
												map[i][j] = BUBBLE;
										}
										break;
									}
								}

							}
						}
						boxlist.next();
						cntbox++;
					}
					boxlist.setStart();
				}
				else if (map[i][j] == GHOSTC)
				{
					Ghost *g = new Ghost;
					while (ghostlist.fence->next != ghostlist.tail)
					{
						ghostlist.getValue(g);
						for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
						{
							for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
							{
								if (!(i == b->x_axis&&i == b->y_axis))
								{
									if (g->x_axis == i && g->y_axis == j)
									{
										g->hp -= b->atk;
										paintHP(g->hp,g->x,g->y,hdc);
										if (g->hp <= 0)
										{
											Ghost *del = new Ghost;
											map[i][j] = GRASS;
											ghostlist.remove(*del);
										}
										break;
									}
								}

							}
						}
						ghostlist.next();
					}
					ghostlist.setStart();
				}
			}
			
		}
	
}
void changeValue(Bomb *&b)
{
	b->loop += 1;
}

//这里用了引用传递对象，所以数据成员的值可以被修改
bool canPutBomb(Bomb *b)
{
	int x, y;
	//检测是否能放置炸弹
	//不能的情况：不是草
	if ((bomblist.leftcnt + bomblist.rightcnt) == maxBomb)
		return false;
	switch (people.dir)
	{
		//人向上，炸弹放在人的上方,暂时不考虑为石头的情形和边界情形，稍后再做检测
	case 0:
		x = (people.x / 32);
		y = ((people.y+6) / 32) - 1;
		break;
		//人向下
	case 1:
		x = (people.x / 32);
		y = ((people.y - 6) / 32) + 1;
		break;
		//人向左
	case 2:
		x = ((people.x+5) / 32) - 1;
		y = (people.y / 32);
		break;
		//人向右
	case 3:
		x = ((people.x - 5) / 32) + 1;
		y = (people.y / 32);
		break;
	}
	if (map[x][y] != GRASS)
		return false;
	else
	{
		b->x_axis = x;
		b->y_axis = y;
		b->x = x * 32;
		b->y = y * 32;
		return true;
	}
	
}
/* 检测是否能放置时已经完成，不需再做一遍
void findPosition(People p,Bomb b)
{
	
	//确定炸弹位置
	switch (people.dir)
	{
		//人向上，炸弹放在人的上方
	case 0:
		b.x_axis = (people.x / 32);
		b.y_axis = (people.y / 32)-1;
		break;
		//人向下
	case 1:
		b.x_axis = (people.x / 32);
		b.y_axis = (people.y / 32) + 1;
		break;
		//人向左
	case 2:
		b.x_axis = (people.x / 32) - 1;
		b.y_axis = (people.y / 32);
		break;
		//人向右
	case 3:
		b.x_axis = (people.x / 32) + 1;
		b.y_axis = (people.y / 32);
		break;
	}
}*/
void paintBomb(HDC hdc, Bomb b)
{
	int w, h;
	w = h = 23;
	//分阶段绘制
	int src_start_x =0;
	int src_start_y=0;
	//阶段1
	b.tN = GetTickCount();
	//if ((b.tN-b.tP) < 200)
	if ((b.loop) < 5)
	{
		src_start_x = src_start_y = 0;
	}
	//阶段2

	//else if ((b.tN - b.tP) > 200 && (b.tN - b.tP) < 400)
	else if (b.loop > 5 && b.loop <10)
	{
		src_start_x = 24;
		src_start_y = 0;
	}
	//阶段3
	else if (b.loop > 10 && b.loop < 15)
	{
		src_start_x = 48;
		src_start_y = 0;
	}
	//阶段4
	else if (b.loop > 15 && b.loop < 20)
	{
		src_start_x = 72;
		src_start_y = 0;
	}
	SelectObject(bombdc, bombn);
	BitBlt(mdc, b.x, b.y, w, h, bombdc, src_start_x, src_start_y, SRCAND);
	SelectObject(bombdc, bomb);
	BitBlt(mdc, b.x, b.y, w, h, bombdc, src_start_x, src_start_y, SRCPAINT);

	BitBlt(hdc, b.x, b.y, w, h, mdc, b.x, b.y, SRCCOPY);
	//把人物图按现在的坐标贴到mdc上，同时消除背景
	/*
	SelectObject(ghostdcn, ghostn[g.dir]);
	BitBlt(mdc, g.x, g.y, w, h, ghostdcn, g.count*w, 0, SRCAND);
	SelectObject(ghostdc, ghost[g.dir]);
	BitBlt(mdc, g.x, g.y, w, h, ghostdc, g.count*w, 0, SRCPAINT);
	//把mdc上的人粘贴到hdc上
	BitBlt(hdc, g.x, g.y, w, h, mdc, g.x, g.y, SRCCOPY);
	 g.count++;
	//判断是否已经完成一轮动作，若完成，则从头开始动
	if (g.count == 3)
	{
		g.count = 0;

	}*/
}
//这样做不能改变people的x和y值
void initPeople(People p)
{
	srand((unsigned)time(NULL));
	while (true)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			p.setx(x*32);
			p.sety(y*32);
			break;
		}
	}
}

void paintGhost(HDC hdc,Ghost g)
{
	int w, h;
	w = h = 32;

	//把人物图按现在的坐标贴到mdc上，同时消除背景
	//（这种方法只有背景为白色才能用，transparentblt也可以实现）
	SelectObject(ghostdcn, ghostn[g.dir]);
	BitBlt(mdc, g.x, g.y, w, h, ghostdcn, g.count*w, 0, SRCAND);
	SelectObject(ghostdc, ghost[g.dir]);
	BitBlt(mdc, g.x, g.y, w, h, ghostdc, g.count*w, 0, SRCPAINT);
	//把mdc上的人粘贴到hdc上
	BitBlt(hdc, g.x, g.y, w, h, mdc, g.x, g.y, SRCCOPY);
	g.count++;
	//判断是否已经完成一轮动作，若完成，则从头开始动
	if (g.count == 3)
	{
		g.count = 0;

	}

}
//freq参数指生成ghost的频率，现在暂时没有用，设成0
void generateGhost(int freq)
{
	int count = 0;
	
	srand((unsigned)time(NULL));
	while(count<11)
	{
		int x = (rand() % 500)/32;
		int y= (rand() % 500) /32;
		if (map[x][y] == GRASS)
		{
			count++;
			
			Ghost ghost(1000, x * 32, y * 32, 100, 0, 8);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlist.append(ghost);
			
			paintGhost(hdc, ghost);
		}
		
	}
	//TextOut(hdc, 80, 80, "ttttttttt", lstrlen("ttttttttt"));
}
bool checkCollision(int x, int y, int targetdir,int speed)
{
	//碰撞检测
	//当人走到地图上map[i][j]==STONE时，不能继续走，返回原位置
	//每次检测遍历人周围的所有石头？
	int w, h;
	w = h = 32;
	//选择图片大小

	//(1)计算人所在的坐标上下左右的地块是否是stone，是则表明有collision，返回true
	if (map[(x+5) / 32][(y+6) / 32] != GRASS || map[(x + w-5) / 32][(y+6) / 32] != GRASS
		|| map[(x + 5) / 32][(y + h-6) / 32] != GRASS || map[(x + w-5) / 32][(y + h-6) / 32] != GRASS||y>636)
	{
		return true;
	}
	//否则返回false
		return false;
}

void paintMap(HDC hdc)
{
	//重绘地图
	for (int i = 0; i<row; i++)
		for (int j = 0; j< col; j++)
		{
			if (map[i][j] == BOX)
			{
				SelectObject(bufdc, box);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc,  192,64, SRCCOPY);
			}
			else if (map[i][j] == STONE || map[i][j] == GRASS|| map[i][j] == HOUSE
				|| map[i][j] == GHOSTC|| map[i][j] == BOMBC || map[i][j] == BOOK
				|| map[i][j] == BUBBLE || map[i][j] == SHOE)
			{
				SelectObject(bufdc, base);
				if(map[i][j] == HOUSE || map[i][j] == GHOSTC|| map[i][j] == BOMBC || map[i][j] == BOOK
					|| map[i][j] == BUBBLE || map[i][j] == SHOE)
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, GRASS * 32, 0, SRCCOPY);
				else
					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, (map[i][j]) * 32, 0, SRCCOPY);
			}
			if (map[i][j] == HOUSE)
			{
				SelectObject(bufdc, housen);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
				SelectObject(bufdc, house);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);
			}
			if (map[i][j] == BOOK)
			{
				//paintbook
				SelectObject(bufdc, bookbmp);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);

			}
			if (map[i][j] == BUBBLE)
			{
				//paint bubble
				
				SelectObject(bufdc, bubblen);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
				SelectObject(bufdc, bubblebmp);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);

			}
			if (map[i][j] == SHOE)
			{
				
				SelectObject(bufdc, shoen);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
				SelectObject(bufdc, shoebmp);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);

			}
		}

	//将fullmap存到mdc中
	SelectObject(mdc, fullmap);

	BitBlt(hdc, 0, 0, 593, 620, mdc, 0, 0, SRCCOPY);
	
}
//人物走动
void paintWalk(HDC hdc)
{//把人物走动的图片保存到bufdc_walk dc上
	
	int w, h;
	w = h = 32;
	//选择图片大小
	/*
	switch (people.dir)
	{
	case 0:
		w = 55;
		h = 74;
		break;
	case 1:
		w = 53;
		h = 77;
		break;
	case 2:
		w = 60;
		h = 74;
		break;
	case 3:
		w = 60;
		h = 74;
		break;
	}*/
	//把人物图按现在的坐标贴到mdc上，同时消除背景
	//（这种方法只有背景为白色才能用，transparentblt也可以实现）
	SelectObject(bufdc_n, girln[people.dir]);
	BitBlt(mdc, people.x, people.y, w, h, bufdc_n, num*w, 0, SRCAND);
	SelectObject(bufdc_walk, girl[people.dir]);
	BitBlt(mdc, people.x, people.y, w, h, bufdc_walk, num*w, 0, SRCPAINT);
	//把mdc上的人粘贴到hdc上
	BitBlt(hdc, people.x, people.y, w, h, mdc, people.x, people.y, SRCCOPY);
	tPre = GetTickCount();
	num++;
	//判断是否已经完成一轮动作，若完成，则从头开始动
	if (num == 3)
		num = 0;
	
}
void generateMap()
{
	//生成随机地图
	//为地图数组赋值
	//TODO:1）把地图的一部分写死，安排大本营；2）随机产生道具

	srand((unsigned)time(NULL));
	for(int i=0;i<row;i++)
		for (int j = 0; j < col ;j++)
		{
				map[i][j] = GRASS;
				
		}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (rand() % 5 == 0)
				map[i][j] = STONE;
			else if(rand() % 5 == 1)
				map[row - 2-i][j] = STONE;
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < row; i++)
		{
			if ((rand()+106) % 5 == 0)
				map[i][j] = STONE;
			else if ((rand() + 106) % 5 == 1)
				map[i][col-2-j] = STONE;
		}
	}
	//左边一列石头
		map[(row / 2) - 4][(col / 2) - 3] =
		map[(row / 2) - 4][(col / 2) -4] =
		map[(row / 2) - 4][(col / 2)-5] =
		map[(row / 2) -4][(col / 2) + 2] =
		map[(row / 2) - 4][(col / 2) +1] =
		map[(row / 2) - 4][(col / 2)] =
		map[(row / 2) - 4][(col / 2) + 2] =
		map[(row / 2) - 4][(col / 2) + 1] =
		
		map[(row / 2) - 4][(col / 2) + 4] =
		//右边一列石头
		map[(row / 2) + 4][(col / 2) - 3] =
		map[(row / 2) + 4][(col / 2) + 4] =
		map[(row / 2) + 3][(col / 2) + 5] =
		map[(row / 2) + 4][(col / 2) + 2] =
		map[(row / 2) + 4][(col / 2) + 1] =
		map[(row / 2) + 4][(col / 2)] =
		
		map[(row / 2) + 4][(col / 2) + 1] =
		map[(row / 2) + 4][(col / 2) + 3] =
	//下面石头
		
		map[(row / 2) ][(col / 2) + 4] =
		map[(row / 2)+1][(col / 2) + 5] =
		map[(row / 2) + 1][(col / 2) + 2] =
		map[(row / 2) + 2][(col / 2) + 1] =
	//右上角为石头+箱子
	
		map[(row / 2) + 2][(col / 2) - 2] =
		map[(row / 2) + 1][(col / 2) - 3] =
		map[(row / 2) + 2][(col / 2) - 3] =
		//左下角为石头
		
		map[(row / 2) - 2][(col / 2) + 2] =
		map[(row / 2) - 1][(col / 2) + 3] =
		map[(row / 2) - 2][(col / 2) + 3] =
		//左上角为石头+箱子
		map[(row / 2) - 1][(col / 2) - 2] =
		map[(row / 2) - 2][(col / 2) - 2] =
		
		map[(row / 2) - 2][(col / 2) - 3] =
		//右侧石头
		map[(row / 2) + 2][(col / 2) + 2] =
		map[(row / 2) + 2][(col / 2) + 1] =
		//下方石头
		map[(row / 2) + 1][(col / 2) +2] =
			//左侧石头
		map[(row / 2) -2][(col / 2) - 1] =
		//内部右上角
		map[(row / 2) + 1][(col / 2) - 1] =
		STONE;
		map[(row / 2) - 1][(col / 2) - 1] =
		
		map[(row / 2)][(col / 2) - 1] =
		map[(row / 2) - 1][(col / 2)] =
		map[(row / 2) + 1][(col / 2)] =
		map[(row / 2) - 1][(col / 2) + 1] =
		map[(row / 2) + 1][(col / 2) + 1] =
		map[(row / 2)][(col / 2) + 1] = 
		map[(row / 2) - 1][(col / 2) - 3] =
		//右上角箱子
		map[(row / 2) + 1][(col / 2) - 2] =
		//左下角箱子
		map[(row / 2) - 1][(col / 2) + 2] =
		//左列箱子
			map[(row / 2) - 4][(col / 2) - 2] =
		map[(row / 2) - 4][(col / 2) - 4] =
		map[(row / 2) - 3][(col / 2) - 4] =
		//map[(row / 2) - 3][(col / 2) + 4] =
		//右列箱子
		map[(row / 2) + 4][(col / 2) + 2] =
		map[(row / 2) + 2][(col / 2) + 4] =
		//下面箱子
		map[(row / 2)][(col / 2) + 3] =
			map[(row / 2) + 5][(col / 2) + 2] =
			map[(row / 2) +4][(col / 2) + 4] =
			map[(row / 2) - 5][(col / 2) -1] =
			map[(row / 2) + 6][(col / 2) + 3] =
			map[(row / 2) -3][(col / 2) + 7] =
			map[(row / 2) -7][(col / 2)+2] =


			map[(row / 2) - 5][(col / 2) + 1] =
			map[(row / 2) +1][(col / 2) + 5] =
			map[(row / 2) - 2][(col / 2) -2] =
		BOX;
	map[(row / 2)][(col / 2)] = HOUSE;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TOMBRAIDER1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TOMBRAIDER1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
			//每20ms刷新一次，进行重绘
			tNow = GetTickCount();

			if (tNow - tPre >= 30)
			{
				//bomblist.remove(*item);
				
				//if (people.hp > 200)

			///	{
				//People *ptemp = new People;
				//getPeople(ptemp);
				//checkAlive(ptemp);
				bool vic = false;
				if ((people.x / 32 == row / 2 - 1 && people.y / 32 == col / 2) ||
					(people.x / 32 == row / 2 + 1 && people.y / 32 == col / 2) ||
					(people.x / 32 == row / 2 && people.y / 32 == col / 2-1) ||
					(people.x / 32 == row / 2  && people.y / 32 == col / 2+ 1)
					)
				{
					//胜利
					paintvic(hdc);
					vic = true;
				}
				if (vic)
				{
					//重置


				}
				else
				{
					if (people.hp <= 0)
					{
						//TODO:game over画面
						paintbg(hdc);
						//重置
						/*
						resEtr = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
							TEXT(""),
							WS_VISIBLE | WS_CHILD | BS_BITMAP,
							200, 420, 109, 40,
							hwnd,
							(HMENU)IDB_TWO,  
							hInst,
							NULL);
						resExt = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
							TEXT(""),
							WS_VISIBLE | WS_CHILD | BS_BITMAP,
							400, 420, 109, 40,
							hwnd,
							(HMENU)IDB_THREE,  
							hInst,
							NULL);
						SendMessage(resEtr, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)btnetrbmp);
						SendMessage(resExt, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)btnextbmp);
						*/
					}
					else
					{
						//gameOver(hdc);
						paintMap(hdc);
						paintWalk(hdc);
						
						//char c[20] = "";
						//sprintf_s(c, "hp%d", people.hp);
						//MessageBox(msg.hwnd, c, "message", MB_ICONERROR);

						//绘制妖怪
						Ghost *it = new Ghost;
						while (ghostlist.fence->next != ghostlist.tail)
						{
							ghostlist.getValue(it);
							paintGhost(hdc, *it);
							ghostlist.next();
						}
						ghostlist.setStart();

						//绘制炸弹
					//遍历炸弹链表

						//for (int i = 0; i < (ghostlist.leftcnt + ghostlist.rightcnt); i++)
						//{
						Bomb *item = new Bomb;
						bomblist.setStart();

						if ((bomblist.leftcnt + bomblist.rightcnt) > 0) {
							while (bomblist.fence != bomblist.tail)
							{
								bool flag = false;
								bomblist.getValue(item);
								//loopIncrement(&itemref);

								item->tN = GetTickCount();
								changeValue(item);

								if (item->loop < 20)
								{

									paintBomb(hdc, *item);
									//MessageBox(msg.hwnd, "tttttttt", "message", MB_ICONERROR);
								}
								else
								{
									doHurt(item);
									flag = true;
									countatk++;

									//sprintf_s(c, "y%d", item->y_axis);
									map[item->x_axis][item->y_axis] = GRASS;
									Bomb *btemp = new Bomb;
									bomblist.remove(*btemp);
								}
								//在这里停住了，所以才能一次次地doHurt()
								//如果没有停住，就会自动hurt
								/*
								if (flag)
								{
									char c[20] = "";
									sprintf_s(c, "countatk%d", countatk);
									333MessageBox(msg.hwnd, "atk", "message", MB_ICONERROR);
									MessageBox(msg.hwnd, c, "message", MB_ICONERROR);
									sprintf_s(c, "hp%d", people.hp);
									MessageBox(msg.hwnd, c, "message", MB_ICONERROR);
								}*/

								//else 
								//{
									//char c[20] = "";

									//sprintf_s(c, "次數%d", item->loop);
									//MessageBox(msg.hwnd, c, "message", MB_ICONERROR);
									//bomblist.remove(*item);
								//}
								bomblist.next();
							}

							
						}paintHP(people.hp,people.x,people.y,hdc);
					}
				}
				
			}
			
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOMBRAIDER1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TOMBRAIDER1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   num = 0;
   startwd= CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   //载入地图图片资源
   base = (HBITMAP)LoadImage(NULL, "base.bmp", IMAGE_BITMAP, 288, 32, LR_LOADFROMFILE);
   //载入人图片资源
   //角色图
   girl[0] = (HBITMAP)LoadImage(NULL, "Yangguo_00.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girl[1] = (HBITMAP)LoadImage(NULL, "Yangguo_01.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girl[2] = (HBITMAP)LoadImage(NULL, "Yangguo_02.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girl[3] = (HBITMAP)LoadImage(NULL, "Yangguo_03.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);

   girln[0] = (HBITMAP)LoadImage(NULL, "Yangguon_00.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girln[1] = (HBITMAP)LoadImage(NULL, "Yangguon_01.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girln[2] = (HBITMAP)LoadImage(NULL, "Yangguon_02.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girln[3] = (HBITMAP)LoadImage(NULL, "Yangguon_03.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
  
   //怪物图
   ghost[0] = (HBITMAP)LoadImage(NULL, "Mashroom0.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   ghost[1] = (HBITMAP)LoadImage(NULL, "Mashroom1.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   ghost[2] = (HBITMAP)LoadImage(NULL, "Mashroom2.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   ghost[3] = (HBITMAP)LoadImage(NULL, "Mashroom3.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);

   ghostn[0] = (HBITMAP)LoadImage(NULL, "Mashroomn0.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   ghostn[1] = (HBITMAP)LoadImage(NULL, "Mashroomn1.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   ghostn[2] = (HBITMAP)LoadImage(NULL, "Mashroomn2.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   ghostn[3] = (HBITMAP)LoadImage(NULL, "Mashroomn3.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   box = (HBITMAP)LoadImage(NULL, "box.bmp", IMAGE_BITMAP, 256, 256, LR_LOADFROMFILE);
   house= (HBITMAP)LoadImage(NULL, "house.bmp", IMAGE_BITMAP, 32,32, LR_LOADFROMFILE);
   housen= (HBITMAP)LoadImage(NULL, "housen.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   //炸弹
   bomb= (HBITMAP)LoadImage(NULL, "bomb.bmp", IMAGE_BITMAP, 256,128, LR_LOADFROMFILE);
   bombn = (HBITMAP)LoadImage(NULL, "bombn.bmp", IMAGE_BITMAP, 256, 128, LR_LOADFROMFILE);
   bgpic= (HBITMAP)LoadImage(NULL, "bgpic.bmp", IMAGE_BITMAP, 1064, 624, LR_LOADFROMFILE);
   //按键
   btnetrbmp= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
   btnextbmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
 //结束界面
   gv= (HBITMAP)LoadImage(NULL, "gv.bmp", IMAGE_BITMAP, 500, 339, LR_LOADFROMFILE);
   gvn = (HBITMAP)LoadImage(NULL, "gvn.bmp", IMAGE_BITMAP, 500, 339, LR_LOADFROMFILE);
   gvbg= (HBITMAP)LoadImage(NULL, "gvbg.bmp", IMAGE_BITMAP, 593, 620, LR_LOADFROMFILE);
   vicbg= (HBITMAP)LoadImage(NULL, "vic.bmp", IMAGE_BITMAP, 593, 620, LR_LOADFROMFILE);
   //道具
   bookbmp = (HBITMAP)LoadImage(NULL, "book.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	 //bubblebmp
    shoebmp= (HBITMAP)LoadImage(NULL, "shoe.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	shoen= (HBITMAP)LoadImage(NULL, "shoen.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	bubblebmp = (HBITMAP)LoadImage(NULL, "bubble.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	bubblen = (HBITMAP)LoadImage(NULL, "bubblen.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	hp1 = (HBITMAP)LoadImage(NULL, "hp1.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp2 = (HBITMAP)LoadImage(NULL, "hp2.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp3 = (HBITMAP)LoadImage(NULL, "hp3.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp4 = (HBITMAP)LoadImage(NULL, "hp4.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp5 = (HBITMAP)LoadImage(NULL, "hp5.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp6 = (HBITMAP)LoadImage(NULL, "hp6.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp7 = (HBITMAP)LoadImage(NULL, "hp7.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp8 = (HBITMAP)LoadImage(NULL, "hp8.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp9 = (HBITMAP)LoadImage(NULL, "hp9.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp10= (HBITMAP)LoadImage(NULL, "hp10.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);

	hp1n = (HBITMAP)LoadImage(NULL, "hp1n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp2n = (HBITMAP)LoadImage(NULL, "hp2n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp3n = (HBITMAP)LoadImage(NULL, "hp3n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp4n = (HBITMAP)LoadImage(NULL, "hp4n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp5n = (HBITMAP)LoadImage(NULL, "hp5n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp6n = (HBITMAP)LoadImage(NULL, "hp6n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp7n = (HBITMAP)LoadImage(NULL, "hp7n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp8n = (HBITMAP)LoadImage(NULL, "hp8n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp9n = (HBITMAP)LoadImage(NULL, "hp9n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp10n = (HBITMAP)LoadImage(NULL, "hp10n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
   if (!(hwnd|| startwd))
   {
      return FALSE;
   }
    
   MoveWindow(startwd, 100, 5, 1064, 624, true);
   ShowWindow(startwd, nCmdShow);
   UpdateWindow(startwd);
  //获得dc和bitmap
   hdc = GetDC(hwnd);
   mdc = CreateCompatibleDC(hdc);
   bufdc = CreateCompatibleDC(hdc);
   bufdc_walk = CreateCompatibleDC(hdc);
   bufdc_n = CreateCompatibleDC(hdc);
   ghostdc = CreateCompatibleDC(hdc); 
   ghostdcn = CreateCompatibleDC(hdc);
   bombdc= CreateCompatibleDC(hdc);
   bgdc= GetDC(startwd);
   bgbufdc = CreateCompatibleDC(bgdc);
   bgmap = CreateCompatibleBitmap(bgdc, 1064, 624);
   SelectObject(bgbufdc, bgpic);
   gvdc= CreateCompatibleDC(hdc);
   gvdcbuf = CreateCompatibleDC(hdc);
   //gvmap= CreateCompatibleBitmap(hdc, 500, 339);
   fullmap = CreateCompatibleBitmap(hdc, 593, 620);
   BitBlt(bgdc, 0, 0, 1064, 624, bgbufdc, 0, 0, SRCCOPY);
   gvbgdc= CreateCompatibleDC(hdc);
   
   hBtnEtr = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   300, 420, 109, 40,
	   startwd,
	   (HMENU)IDB_ZERO,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   hBtnQuit = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   600, 420, 109, 40,
	   startwd,
	   (HMENU)IDB_ONE,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   SendMessage(hBtnEtr, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)btnetrbmp);
   SendMessage(hBtnQuit, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)btnextbmp);
   //生成地图
   generateMap();
   SelectObject(mdc, fullmap);
   //图片素材的保存
   
   //绘制地图和人物
   //生成ghost链表并初始化
   ghostlist.init();
   generateGhost(0);
   paintMap(hdc);
   //生成bomb链表并初始化
   bomblist.init();
   //initPeople(people);
   srand((unsigned)time(NULL));
   while (true)
   {
	   int x = ((rand()+100) % 500) / 32;
	   int y = ((rand() + 100) % 500) / 32;
	   if (map[x][y] == GRASS)
	   {
		   people.setx(x * 32);
		   people.sety(y * 32);
		   break;
	   }
   }
   paintWalk(hdc);
   initBox();
   
   /*

	   //右列箱子
	 
	   map[(row / 2) + 2][(col / 2) + 4] =
	   //下面箱子
	   map[(row / 2)][(col / 2) + 3] =
	   BOX;*/
   initItems();

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
	case WM_CREATE:
		//for (int i = 0; i<3; i++)
		//{
		/*LONG BtnStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP;

		HWND hButton = CreateWindow(TEXT("button"), "Name",
		BtnStyle,
		0, 0, 0, 0, hWnd, (HMENU)iBtnID[i],
		((LPCREATESTRUCT)lParam)->hInstance, NULL);

		SetWindowText(hButton, "Name");//设置按钮文本

		//创建字体
		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = -14;//字体的大小
		hFont = CreateFontIndirect(&lf);

		//修改字体
		SendMessage(hButton[i], WM_SETFONT, (WPARAM)hFont, 0);
		//}*/
		
		
		PlaySound(TEXT("D:\\Music\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case WM_KEYDOWN:
	{
		//按下按键，判断人物行为
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		//按空格键放炸弹
		case VK_SPACE:
		{
			//Ghost g(1000, people.x+32, people.y + 32, 100,0,10);
			//Ghost &gref = g;
			Bomb bomb;
			Bomb &bombref=bomb;
			bomb.atk += (bombplus * 20);
			if (canPutBomb(&bombref))
			{
				//ghostlist.append(g);
				bomblist.append(bomb);
				//MessageBox(hWnd, "tttttttt", "message", MB_ICONERROR);
				//paintBomb(hdc, bomb);
				map[bomb.x_axis][bomb.y_axis] = BOMBC;
				SetTimer(hWnd, 1, 100, NULL);
			}
			/*
			if(bomb.x>0&&bomb.y>0)
				MessageBox(hWnd, "tttttttt", "message", MB_ICONERROR);
			else
				MessageBox(hWnd, "ffffffff", "message", MB_ICONERROR);*/

		}
		break;
		//按上键
		case VK_UP:
		{
			//map[people.x / 32][people.y / 32] = GRASS;
			people.move(0);
			//map[people.x / 32][people.y / 32] = CHARACTER;

			if (checkCollision(people.x, people.y, 0, people.speed))
			{

				people.y += people.speed;
				//MessageBox(hWnd, "tttttttt", "message", MB_ICONERROR);
			}
		}
		break;

		case VK_DOWN:
		{
			//map[people.x / 32][people.y / 32] = GRASS;
			people.move(1);
			//map[people.x / 32][people.y / 32] = CHARACTER;
			if (checkCollision(people.x, people.y, 1, people.speed))
			{

				people.y -= people.speed;
				//MessageBox(hWnd, "tttttttt", "message", MB_ICONERROR);
			}
		}
		break;

		case VK_LEFT:
		{
			//map[people.x / 32][people.y / 32] = GRASS;
			people.move(2);
			//map[people.x / 32][people.y / 32] = CHARACTER;
			if (checkCollision(people.x, people.y, 2, people.speed))
			{

				people.x += people.speed;
				//MessageBox(hWnd, "tttttttt", "message", MB_ICONERROR);
			}
		}
		break;
		case VK_RIGHT:
		{
			//map[people.x / 32][people.y / 32] = GRASS;
			people.move(3);
			//map[people.x / 32][people.y / 32] = CHARACTER;
			if (checkCollision(people.x, people.y, 3, people.speed))
			{

				people.x -= people.speed;
				//MessageBox(hWnd, "tttttttt", "message", MB_ICONERROR);
			}
		}
		break;

		case 0x41:
		{
			//TODO:捡道具
			pickItem();
			break;
		}
		}
	
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDB_ZERO:
				ShowWindow(hWnd, SW_HIDE);
				//DestroyWindow(hWnd);
				hWnd = hwnd;
				ShowWindow(hWnd, SW_SHOW);
				MoveWindow(hwnd, 250, 35, 593, 636, true);
				UpdateWindow(hwnd);
				
				break;
			case IDB_ONE:
				DestroyWindow(hWnd);
				break;
			case IDB_TWO:
				//ShowWindow(hWnd, SW_HIDE);
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_FORMVIEW),hWnd,About );
				//DestroyWindow(hWnd);
					/*
				hWnd = startwd;
				InitInstance(hInst, SW_SHOW);
				ShowWindow(hWnd, SW_SHOW);
				UpdateWindow(startwd);*/
				break;
			case IDB_THREE:
				DestroyWindow(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
	{
		//Bomb *item = new Bomb;
		//map[item->x_axis][item->y_axis] = GRASS;
		//doHurt(item);
		//bomblist.remove(*item);
	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:

        PostQuitMessage(0);
		DeleteDC(mdc);
		DeleteDC(bufdc);
		DeleteDC(bombdc);
		for (int i = 0; i < 4; i++)
		{
			DeleteObject(girl[i]);
		}
		DeleteObject(bomb);
		DeleteObject(bombn);
		ReleaseDC(hWnd, hdc);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {

    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
