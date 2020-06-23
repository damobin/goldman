#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
//macro
#define WINDOWWIDTH		1080
#define WINDOWHEIGHT	640

#define PICTURE_NUM		11

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
		sprintf(c8ImgPath, "./images/%d.jpg", i);
		loadimage(&imgPicture[i], c8ImgPath);
	}

}
void drawGame()
{

	
}
