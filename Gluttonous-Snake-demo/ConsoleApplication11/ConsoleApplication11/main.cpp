/*
*/
#include<graphics.h>//ͼ�ν���ͷ�ļ�
#include<stdio.h>
#include<time.h>
#include<mmsystem.h>//��ý���豸�ӿ� ����������Ƶ���ֲ���
#pragma comment(lib,"winmm.lib")
#include <conio.h>



struct coor//����
{
	int x;
	int y;
};
typedef enum ch//����
{
	up = 72,//�̶��ķ��� �����ֵ
	down = 80,
	left = 75,
	right = 77,
}CH;
struct snake//�ߵ���Ϣ
{
	struct coor scr[100];//�������100���ߵ�������Ϣ
	int n;				 //�ߵĽ���
	CH ch;				 //�ߵķ���
}Snake;

struct food
{
	struct coor fcr;//
	int flag;//��û�б���

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
	//initgraph(640, 480);//��ʼ��ͼ�ν��� 640 480
	//rectangle(320,240,330,250);//���ϽǺ����½�����
	//circle(320,240,200);//���� �뾶
		//roundrect(320,240,420,340,100,50);//Բ�Ǿ��� ����320,240,420,340  ����50�뾶
	//int x=320, y=60;
	//int iSpeed = 0;
	//while (1)
	//{
	//	circle(x, y, 50);//
	//	Sleep(100);
	//	y += iSpeed++;
	//	if (y<50 || y>480)
	//	{
	//		iSpeed = -iSpeed;
	//	}
	//	cleardevice();
	//	
	//}


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


//��Ϸ��ʼ��
void GameInit()//
{
	initgraph(800, 480);
	setfillcolor(LIGHTCYAN);//�����ɫ
	HRGN rgn = CreateRectRgn(600,0,800,480);//������Ҫ����
	setcliprgn(rgn);//�ü�  �������⻭ͼ�ο����� ֻ���ڽ�������ͼ
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(600,0,800,480);//
	setcolor(RED);//������ɫ
	settextstyle(25,0, L"����");//��������50  0�����С L��������
	setbkmode(TRANSPARENT);    //͸���������
	outtextxy(625,50,L"̰����");//����������625��100�ĵط��������
	//һ�ֺܶ����ֵ����
	settextstyle(15, 0, L"����");
	RECT rect = { 625, 100, 780, 470 };//�ṹ��
	drawtext(_T("[��Ϸ˵��]\n�����������2019.10.7������̰������Ϸ,�ٶ��е��,��ʱ��չʾ������!\
				\n\n[����˵��]\
				\n�����:���Ʒ���\
				\nF5    :���¿�ʼ\
				\nESC   :������Ϸ"),&rect,DT_WORDBREAK);
	
	HRGN rgn1 = CreateRectRgn(0, 0, 600, 480);//������Ҫ����
	setcliprgn(rgn1);//�ü�  �������⻭ͼ�ο����� ֻ���ڽ�������ͼ
	DeleteObject(rgn1);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(0, 0, 600, 480);//

	//PlaySound(L"", null, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//mciSendString(L"open D:\CloudMusic\111.mp3 alias ARNO", 0, 0, 0);
	//mciSendString(L"play ARNO repeat", 0, 0, 0);//���� ������ ���ݿ�
	setbkcolor(RGB(220, 120, 150));
	cleardevice();


	//��ʼ����
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(0, 0, 10, 10);
	Snake.n = 1;//�ߵ�ǰ����
	Snake.scr[0].x = 0;
	Snake.scr[0].y = 0;
	Snake.ch = down;


	Food.flag = 0;//����״̬

}//����

//�߶�����
void SnakeMove()//���ߵĶ���
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

	switch (input)//���ܿ���
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

	Food.flag = 1;//����
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
	HRGN rgn = CreateRectRgn(600, 0, 800, 480);//������Ҫ����
	setcliprgn(rgn);//�ü�  �������⻭ͼ�ο����� ֻ���ڽ�������ͼ
	DeleteObject(rgn);//��Ҫռ��ϵͳ�ڴ�
	solidrectangle(600, 0, 800, 480);//
	setcolor(RED);//������ɫ
	settextstyle(25, 0, L"����");//��������50  0�����С L��������
	setbkmode(TRANSPARENT);    //͸���������
	outtextxy(625, 50, L"̰����");//����������625��100�ĵط��������
	//һ�ֺܶ����ֵ����
	settextstyle(15, 0, L"����");
	RECT rect = { 625, 100, 780, 470 };//�ṹ��
	drawtext(_T("������!��F5���¿�ʼ"), &rect, DT_WORDBREAK);
}