#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
//macro
#define WINDOWWIDTH		1080
#define WINDOWHEIGHT	640

#define PICTURE_NUM		11
//self data struct
enum MINE {
	i_gold		= 1,
	i_money		= 3,
	i_soledown	= 5,
	i_soleup	= 7,
	i_stone		= 9,
	i_bk		= PICTURE_NUM-1,

};
struct stgoldman {
	int posx, posy;		//pos
	int width, height;	//sharp
	int coin;			//gold
};


//var declear
IMAGE imgPicture[PICTURE_NUM];
stgoldman st_goldman;

//funs declear
void initGame();
void drawGame();
int main() 
{
	initGame();
	drawGame();
	while (1);
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
}
