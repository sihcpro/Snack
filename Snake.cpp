#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>

using namespace std;

/* Struct Snake */
	struct Snake						        //			72	^ 3
	{											//				|
		int xDes= 0, yDes= 0;/*Destination*/	//
		int dir = 0, pDir= 0;/*Direction*/		//	75 | 0 <-  x y	   -> 2 | 77
		int size= 1;
		Snake *next= NULL;						//				|
	};									        //			80	v 1

	typedef Snake* pSnake;						//	pointer of Snake;

/* Control game */
	typedef char aMatrix[200][75];

/* Get start */
	void makeSnake(aMatrix matrixMove, pSnake thisSnake, int xThisDes, int yThisDes, int thisDir, int preDir, int lengSnake);

/* Move snake */
	void moveSnake(aMatrix matrixMove, pSnake thisSnake, int preDir, bool head);
	void runSnake(aMatrix matrixMove, pSnake head, char key);
	void checkKey(aMatrix matrixMove, pSnake head, char &key);

/* Test Snake */
	void runSnakeFree(pSnake headSnake);

/* Game */
    bool checkNextStep(int nextMove, pSnake headSnake, aMatrix matrixMove);
    void runSnakeGame(pSnake headSnake);

/* Print out screen */
	void gotoXY(int x, int y);
	/* Print out Snake */
		void printSnakeFirst(pSnake thisSnake, bool head);
		void printSnakeNext(aMatrix matrixMove, pSnake thisSnake);
		void printHead(int thisDir);
		void printBody(int dir, int preDir);
		void clearEndSnake(int xDes, int yDes);

	/* Print out Wall */
		void printWall(aMatrix maxtrixWall, int w, int h, char wall);
		void printNameWall(string wallName, int width);
		void makeWall(string wallName, aMatrix matrixWall, int width, int hight);



/* Control key */
	/* Key input */
		const char	keyUp  	= 72;					//			72	^ 3
		const char	keyLeft	= 75;					//				|
		const char	keyRight= 77;
		const char	keyDown	= 80;					//	75 | 0 <-  x y	   -> 2 | 77

	/* Number turn Snake */
		const char	lef		= 0;					//				|
		const char	down	= 1;					//			80	v 1
		const char	righ	= 2;
		const char	up      = 3;

	/* Char print out Screen */
		const char	vertical	= -70;
		const char	horizontal	= -51;
		const char	leftDown	= -69;
		const char	leftUp		= -68;
		const char	rightDown	= -55;
		const char	rightUp		= -56;

	/* Size Default CMD */
		const int	hightCMD	= 25;
		const int	widthCMD	= 80;

class Player
{
	int longSnake= 5;
	int numPlayer= 1;
	
	Player(int numberPlayer, int longSnakeOfPlayer)
	{
		numPlayer= numberPlayer;
		longSnake= longSnakeOfPlayer;
	}
	~Player()
	{
		delete numPlayer;
		delete longSnake;
	}
}
		

void menu()
{
	cout << 
}

















