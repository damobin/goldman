#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
//macro
#define WINDOWWIDTH		1080
#define WINDOWHEIGHT	640

#define PICTURE_NUM		11
#define STORE_NUM		10
//self data struct
enum MINE {
	i_gold		= 1,
	i_money		= 3,
	i_soledown	= 5,
	i_soleup	= 7,
	i_stone		= 9,
	i_bk		= PICTURE_NUM-1,
};
enum FLAG {
	f_yes,
	f_no
};
enum STORE_TYPE {
	t_gold,
	t_money,
	t_stone
};
struct POS {
	int posX, posY;
};
struct Speed {
	int SpeedX, SpeedY;
};
struct CIRCLY {
	POS circlePos;
	int raduis;
};
struct ROPE{

	int state;			//�����Ƿ����쳤״̬
	int catchIndex;		//��¼�������Ʒ��Ϣ
};

struct stgoldman {
	int posx, posy;		//pos
	int width, height;	//sharp
	int coin;			//gold
};
struct STORE{
	int posx, posy;		//pos
	int width, height;	//sharp
	int flag;			//�Ƿ������Ʒ
	int value;			//��Ʒ��ֵ
	int type;
};

struct HOOK{
	POS Startpos;			//�������������
	POS Endpos;				//�������յ�����
	int ropeLens;
	CIRCLY circlepos;		//�����յ��Բ��
	Speed  speed;			//�������

	int angle;			//�Ƕ�
	int dir;			//���Ӱڶ�������û�г���ǰ���԰ڶ�
	int swing;			//�����Ƿ��ڰڶ�
	ROPE rope;	

};


//var declear
IMAGE imgPicture[PICTURE_NUM];
stgoldman st_goldman;
STORE store[STORE_NUM];
HOOK  hook;
//funs declear
void initGame();
void drawGame();
int main() 
{
	initGame();
	while (1) {
		drawGame();
		Sleep(10);
	}
	return 0;
}

void initGame()
{
	
	initgraph(WINDOWWIDTH, WINDOWHEIGHT);
	for(int i=0;i< PICTURE_NUM-1;i++){
		char c8ImgPath[100] = "";
		sprintf_s(c8ImgPath, "./images/%d.jpg", i);
		loadimage(&imgPicture[i], c8ImgPath);
	}
	loadimage(&imgPicture[i_bk],"./images/bk.jpg");

	st_goldman.posx   =  WINDOWWIDTH / 2 - st_goldman.width / 2;
	st_goldman.posy	  = 0;
	st_goldman.width  = 140;
	st_goldman.height = 120;
	st_goldman.coin   = 0;
	//����goldman������ɫ

	//������Ʒ
	for (int i = 0; i < STORE_NUM; i++) {
		store[i].height = 180;
		store[i].width  = 180;
		store[i].posx   = rand() % (WINDOWWIDTH - store[i].width);
		store[i].posy   = st_goldman.height + rand() % ( WINDOWHEIGHT - 2 *st_goldman.height);
		store[i].flag   = f_yes;
		store[i].value  = rand() % 100 + 100;
		store[i].type   = rand() % 3;
	}
	//��ʼ������
	hook.Startpos.posX		= st_goldman.posx + 40;
	hook.Startpos.posY		= st_goldman.posy + 100;					//���Ӵ��������±� 100 �ұ� 40
	hook.ropeLens			= 50;										//���ӳ���
	hook.Endpos.posX		= hook.Startpos.posX;
	hook.Endpos.posY		= hook.Startpos.posY + hook.ropeLens;		//���Ӷ˵��������

	hook.circlepos.circlePos.posX =	hook.Endpos.posX;				
	hook.circlepos.circlePos.posY =	hook.Endpos.posY;					//����ĩ�� �� С������

}
#define SCORE_POSX	20
#define SCORE_POSY	20
void drawGame()
{
	cout << "Test" << endl;
	putimage(0, 120, &imgPicture[i_bk]);
	//������ɫ���
	setfillcolor(RGB(206, 141, 59));
	solidrectangle(0, 0, WINDOWWIDTH, 120);
	putimage(st_goldman.posx, st_goldman.posy, &imgPicture[i_soledown-1],SRCAND);
	putimage(st_goldman.posx, st_goldman.posy, &imgPicture[i_soledown],SRCPAINT  );
	
	//���Ʒ������
	char score[30] = "";
	sprintf_s(score, "����:%06d", st_goldman.coin);
	setfillcolor(WHITE);	    //���������ɫ
	setbkmode(TRANSPARENT);		//�ı��򱳾������ɫ
	settextstyle(50, 0, "����");//����
	outtextxy(SCORE_POSX, SCORE_POSY, score);	//���
	//���ƹ���
	setlinecolor(BROWN);																//����  ��ɫ
	setlinestyle(PS_SOLID,3);															//����  ʵ��  3
	line(hook.Startpos.posX, hook.Startpos.posY, hook.Endpos.posX, hook.Endpos.posY);	//����

	setfillcolor(YELLOW);
	solidcircle(hook.circlepos.circlePos.posX, hook.circlepos.circlePos.posY, 5);

	//������Ʒ
	for (int i = 0; i < STORE_NUM; i++)	{
		if (store[i].flag == f_yes) {
			if (store[i].type == t_gold) {
				putimage(store[i].posx, store[i].posy, &imgPicture[i_gold-1],SRCAND);
				putimage(store[i].posx, store[i].posy, &imgPicture[i_gold],SRCPAINT );
			}else if(store[i].type == t_money){
				putimage(store[i].posx, store[i].posy, &imgPicture[i_money-1],SRCAND);
				putimage(store[i].posx, store[i].posy, &imgPicture[i_money],SRCPAINT );
			}else if(store[i].type == t_stone){
				putimage(store[i].posx, store[i].posy, &imgPicture[i_stone-1],SRCAND);
				putimage(store[i].posx, store[i].posy, &imgPicture[i_stone],SRCPAINT );
			}
		}
	}

}
