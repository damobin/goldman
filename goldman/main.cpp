#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
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



//self data struct
IMAGE imgPicture[PICTURE_NUM];
//var declear

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
}
void drawGame()
{
	putimage(0, 120, &imgPicture[i_bk]);
	
}
