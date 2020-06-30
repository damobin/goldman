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

	int state;			//绳子是否在伸长状态
	int catchIndex;		//记录捕获的物品信息
};

struct stgoldman {
	int posx, posy;		//pos
	int width, height;	//sharp
	int coin;			//gold
};
struct STORE{
	int posx, posy;		//pos
	int width, height;	//sharp
	int flag;			//是否存在物品
	int value;			//物品价值
	int type;
};

struct HOOK{
	POS Startpos;			//钩子线起点坐标
	POS Endpos;				//钩子线终点坐标
	int ropeLens;
	CIRCLY circlepos;		//钩子终点的圆球
	Speed  speed;			//保存分量

	int angle;			//角度
	int dir;			//钩子摆动方向，在没有出勾前的自摆动
	int swing;			//钩子是否在摆动
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
	//绘制goldman背景颜色

	//载入物品
	for (int i = 0; i < STORE_NUM; i++) {
		store[i].height = 180;
		store[i].width  = 180;
		store[i].posx   = rand() % (WINDOWWIDTH - store[i].width);
		store[i].posy   = st_goldman.height + rand() % ( WINDOWHEIGHT - 2 *st_goldman.height);
		store[i].flag   = f_yes;
		store[i].value  = rand() % 100 + 100;
		store[i].type   = rand() % 3;
	}
	//初始化钩子
	hook.Startpos.posX		= st_goldman.posx + 40;
	hook.Startpos.posY		= st_goldman.posy + 100;					//绳子处于人物下边 100 右边 40
	hook.ropeLens			= 50;										//绳子长度
	hook.Endpos.posX		= hook.Startpos.posX;
	hook.Endpos.posY		= hook.Startpos.posY + hook.ropeLens;		//绳子端点绝对坐标

	hook.circlepos.circlePos.posX =	hook.Endpos.posX;				
	hook.circlepos.circlePos.posY =	hook.Endpos.posY;					//绳子末端 的 小球坐标

}
#define SCORE_POSX	20
#define SCORE_POSY	20
void drawGame()
{
	cout << "Test" << endl;
	putimage(0, 120, &imgPicture[i_bk]);
	//背景颜色填充
	setfillcolor(RGB(206, 141, 59));
	solidrectangle(0, 0, WINDOWWIDTH, 120);
	putimage(st_goldman.posx, st_goldman.posy, &imgPicture[i_soledown-1],SRCAND);
	putimage(st_goldman.posx, st_goldman.posy, &imgPicture[i_soledown],SRCPAINT  );
	
	//绘制分数面板
	char score[30] = "";
	sprintf_s(score, "分数:%06d", st_goldman.coin);
	setfillcolor(WHITE);	    //字体填充颜色
	setbkmode(TRANSPARENT);		//文本框背景填充颜色
	settextstyle(50, 0, "宋体");//字体
	outtextxy(SCORE_POSX, SCORE_POSY, score);	//输出
	//绘制钩子
	setlinecolor(BROWN);																//画线  棕色
	setlinestyle(PS_SOLID,3);															//画线  实线  3
	line(hook.Startpos.posX, hook.Startpos.posY, hook.Endpos.posX, hook.Endpos.posY);	//画线

	setfillcolor(YELLOW);
	solidcircle(hook.circlepos.circlePos.posX, hook.circlepos.circlePos.posY, 5);

	//绘制物品
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
