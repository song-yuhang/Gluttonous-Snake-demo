# Gluttonous-Snake-demo
Hi,I am a sophomore，it is my first game,it have many imperfections，I wish someone could improve it，Thanks！

This is a small program made with vs. It has already realized the function: mobile eating food becomes longer, unrealized function: hit the wall and die, and when the snake encounters itself, it dies.
code:
/*
*/
#include<graphics.h>//图形界面头文件
#include<stdio.h>
#include<time.h>
#include<mmsystem.h>//多媒体设备接口 可用来做视频音乐播放
#pragma comment(lib,"winmm.lib")
#include <conio.h>
struct coor//坐标
{
	int x;
	int y;
};
typedef enum ch//方向
{
	up = 72,//固定的方向 虚拟键值
	down = 80,
	left = 75,
	right = 77,
}CH;
struct snake//蛇的信息
{
	struct coor scr[100];//包含最多100节蛇的坐标信息
	int n;				 //蛇的节数
	CH ch;				 //蛇的方向
}Snake;
struct food
{
	struct coor fcr;//
	int flag;//有没有被吃

}Food;

void GameInit();
void SnakeMove();
void DrawSnake();
void ChangeCh();
void FoodCoor();
void DrawFood();
int EatFood();
void shibai();
int main()
{
	GameInit();
	int flag = 0;
	while (1)
	{
		while(!kbhit()){
			if (flag == 0){
				FoodCoor();
				Snake.n++;
			}
			DrawFood();
			SnakeMove();
			flag = EatFood();
			Sleep(100);
			cleardevice();
		}
		ChangeCh();
		if (Snake.scr[Snake.n].x < 0 || Snake.scr[Snake.n].y< 0|| Snake.scr[Snake.n].x>640 || Snake.scr[Snake.n].y>480){
			cleardevice();
			break;
		}
	}
	void shibai();
	getchar();
	return 0;
}
void GameInit()//游戏初始化
{
	initgraph(800, 480);
	setfillcolor(LIGHTCYAN);//填充颜色
	HRGN rgn = CreateRectRgn(600,0,800,480);//分数区要剪裁
	setcliprgn(rgn);//裁剪  剪裁区外画图形看不见 只能在建材区画图
	DeleteObject(rgn);//不要占用系统内存
	solidrectangle(600,0,800,480);//
	setcolor(RED);//设置颜色
	settextstyle(25,0, L"黑体");//设置字体50  0代表大小 L是字体风格
	setbkmode(TRANSPARENT);    //透明背景风格
	outtextxy(625,50,L"贪吃蛇");//设置文字在625和100的地方输出文字
	//一种很多文字的输出
	settextstyle(15, 0, L"黑体");
	RECT rect = { 625, 100, 780, 470 };//结构体
	drawtext(_T("[游戏说明]\n这是由宋宇航于2019.10.7创建的贪吃蛇游戏,速度有点快,是时候展示技术了!\
				\n\n[控制说明]\
				\n方向键:控制方向\
				\nF5    :重新开始\
				\nESC   :结束游戏"),&rect,DT_WORDBREAK);
	
	HRGN rgn1 = CreateRectRgn(0, 0, 600, 480);//分数区要剪裁
	setcliprgn(rgn1);//裁剪  剪裁区外画图形看不见 只能在建材区画图
	DeleteObject(rgn1);//不要占用系统内存
	solidrectangle(0, 0, 600, 480);//

	PlaySound(L"", null, SND_FILENAME | SND_ASYNC | SND_LOOP);
	mciSendString(L"open D:\CloudMusic\111.mp3 alias ARNO", 0, 0, 0);
	mciSendString(L"play ARNO repeat", 0, 0, 0);//声道 采样率 数据块
	setbkcolor(RGB(220, 120, 150));
	cleardevice();


	//初始化蛇
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(0, 0, 10, 10);
	Snake.n = 1;//蛇当前节数
	Snake.scr[0].x = 0;
	Snake.scr[0].y = 0;
	Snake.ch = down;


	Food.flag = 0;//被吃状态

}//界面

//蛇动起来
void SnakeMove()//算蛇的动作
{
	
	for (int i = Snake.n; i >0; i--)
	{
		Snake.scr[i].x = Snake.scr[i - 1].x;
		Snake.scr[i].y = Snake.scr[i - 1].y;
	}
		switch (Snake.ch)
		{
		case up:
			Snake.scr[0].y -= 10;
			break;
		case down:
			Snake.scr[0].y += 10;
			break;
		case left:
			Snake.scr[0].x -= 10;
			break;
		case right:
			Snake.scr[0].x += 10;
			break;
		}
	
	DrawSnake();	
}

void DrawSnake()
{
	
	for (int i = Snake.n; i >0 ; i--)
	{
		fillrectangle(Snake.scr[i].x, Snake.scr[i].y, Snake.scr[i].x + 10, Snake.scr[i].y + 10);
	}
}

void ChangeCh()
{
	int input;
	input = getch();

	switch (input)//接受控制
	{
	case up:
		if (Snake.ch != down)
		{
			Snake.ch = up;
		}
		break;
	case down:
		if (Snake.ch != up)
		{
			Snake.ch = down;
		}
		break;
	case left:
		if (Snake.ch != right)
		{
			Snake.ch = left;
		}
		break;
	case right:
		if (Snake.ch != left)
		{
			Snake.ch = right;
		}
		break;
	}
}

void FoodCoor()
{
	srand(unsigned int(time(NULL)));
	Food.fcr.x = rand() % (600 / 10) * 10;
	Food.fcr.y = rand() % (480 / 10) * 10;

	Food.flag = 1;//被吃
}
void DrawFood()
{
	setcolor(WHITE);
	fillroundrect(Food.fcr.x, Food.fcr.y, Food.fcr.x + 10, Food.fcr.y + 10, 3, 3);
	
}

int EatFood()
{
	if (Snake.scr[0].x == Food.fcr.x&&Snake.scr[0].y == Food.fcr.y)
	{
		Snake.n++;
		Food.flag = 0;

		return Food.flag;
	}
	else{
		return 1;
	}

}
void shibai()
{
	cleardevice();
	HRGN rgn = CreateRectRgn(600, 0, 800, 480);//分数区要剪裁
	setcliprgn(rgn);//裁剪  剪裁区外画图形看不见 只能在建材区画图
	DeleteObject(rgn);//不要占用系统内存
	solidrectangle(600, 0, 800, 480);//
	setcolor(RED);//设置颜色
	settextstyle(25, 0, L"黑体");//设置字体50  0代表大小 L是字体风格
	setbkmode(TRANSPARENT);    //透明背景风格
	outtextxy(625, 50, L"贪吃蛇");//设置文字在625和100的地方输出文字
	//一种很多文字的输出
	settextstyle(15, 0, L"等线");
	RECT rect = { 625, 100, 780, 470 };//结构体
	drawtext(_T("你输了!按F5重新开始"), &rect, DT_WORDBREAK);
}
