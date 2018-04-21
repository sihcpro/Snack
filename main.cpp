#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;





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

	/* Number of Player */
        int speed           = 200;
		const int freeMove	= 0;
		const int player1	= 1;
		int lengSnake		= 20;







/* Struct Snake */
	struct Snake						        //			72	^ 3
	{											//				|
		int xDes= 0, yDes= 0;/*Destination*/	//
		int dir = 0, pDir= 0;/*Direction*/		//	75 | 0 <-  x y	   -> 2 | 77
		int size= 1;
		Snake *next= NULL;						//				|
	};									        //			80	v 1

	typedef Snake* pSnake;						//	pointer of Snake;

/* Struct Food */
	struct Food
	{
		const int value = -80;
		int xDes= 0, yDes= 0;
		int hight= hightCMD-2-2, width= widthCMD-2;
	};
	Food* food= new Food;

/* Class Player */
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
	}

	int	pNum()
	{
		return this->numPlayer;
	}

	int	pLong()
	{
		return this->longSnake;
	}

	void addLong(int addMore)
	{
		this->longSnake+= addMore;
	}
};





/* Control game */
	typedef char aMatrix[200][75];

/* Get start */
	void makeSnake(aMatrix matrixMove, pSnake thisSnake, int xThisDes, int yThisDes, int thisDir, int preDir, int lengSnake, int playerNum);

/* Move snake */
	/*void runSnake(aMatrix matrixMove, pSnake head, char key);*/
	void moveSnake(aMatrix matrixMove, pSnake thisSnake, int preDir, bool head);
	pSnake checkKey(aMatrix matrixMove, pSnake head, char &key, int &checkMove, const int player);

/* Check matrix  */
	pSnake eatFood(aMatrix matrixMove, pSnake thisSnake, int dir);
    int  checkNextStep(int dir, pSnake headSnake, aMatrix matrixMove, int playerNum);

/* Game */
	void runSnakeFree(pSnake headSnake);
    void runSnakeGame(pSnake headSnake);

/* Pause Game */
	pSnake pauseGame(aMatrix matrixMove, pSnake head, char &key, int &checkMove, const int player);

/* Food */
	void makeFood(aMatrix matrixMove, int xDes, int yDes);
	bool randomFood(aMatrix matrixMove, pSnake head);

/* Print out screen */
	void gotoXY(int x, int y);
	/* Print a String */
        void printString(string something, int width, int hight);

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

/* Translate */
    char transKeyToTurn(char keyInput);
	int  transXDes(int xDes, int dir);
	int  transYDes(int yDes, int dir);

/* Test */
	void testMatrix(aMatrix matrixMove, int width, int hight);






int main()
{
	pSnake headSnake;
	headSnake= new Snake;
    runSnakeGame(headSnake);
}







/***************************** Get start ********************************/

void makeSnake(aMatrix matrixMove, pSnake thisSnake, int xThisDes, int yThisDes, int thisDir, int preDir, int lengSnake, int playerNum)
{
    matrixMove[xThisDes][yThisDes]= playerNum;
	thisSnake->xDes= xThisDes;
	thisSnake->yDes= yThisDes;
	thisSnake->dir =  thisDir;
	thisSnake->pDir=   preDir;					//	precede direction;
	thisSnake->size= lengSnake;

	if( lengSnake == 0)
	{
		thisSnake->next= NULL;
	}
	else
	{
        thisSnake->pDir= thisDir;

		xThisDes= transXDes( xThisDes , thisDir^2 );
		yThisDes= transYDes( yThisDes , thisDir^2 );

		pSnake nextSnake;
		nextSnake= new Snake;
		thisSnake->next= nextSnake;
		makeSnake(matrixMove, nextSnake, xThisDes, yThisDes, thisDir, thisDir, lengSnake-1, playerNum);
	}
}





/****************************** Move snake ******************************/

void moveSnake(aMatrix matrixMove, pSnake thisSnake, int preDir, bool head)
{
    if(thisSnake->next == NULL)
    {
        clearEndSnake(thisSnake->xDes, thisSnake->yDes);
        matrixMove[thisSnake->xDes][thisSnake->yDes]= 0;
    }

    if(head)
    {
        thisSnake->dir= preDir;
    }
    else
    {
        thisSnake->dir = thisSnake->pDir;
        thisSnake->pDir= preDir;
    }

	thisSnake->xDes= transXDes( thisSnake->xDes, thisSnake->dir);
	thisSnake->yDes= transYDes( thisSnake->yDes, thisSnake->dir);

	if(thisSnake->next != NULL)
        moveSnake(matrixMove, thisSnake->next, thisSnake->dir, false);
}


pSnake checkKey(aMatrix matrixMove, pSnake head, char &key, int &checkMove, const int player)
{
    char now= key;
    fflush(stdin);

    /* khong lay huong nguoc lai va cung huong */
    while( ( abs(now - key) != 3 || abs(now - key) != 5 || abs(now - key) == 0 ) && kbhit() )
        now = getch();

	if( now == 112 ) return pauseGame(matrixMove, head, key, checkMove, player);

    if( abs(now - key) == 3 || abs(now - key) == 5 )
    {
        key= now;
    }

	checkMove= checkNextStep(transKeyToTurn(key), head, matrixMove, player);

    if( checkMove == food->value )
        return eatFood(matrixMove, head, transKeyToTurn(key));

    if( checkMove == player )
        moveSnake(matrixMove, head, transKeyToTurn(key), true);
    return head;
}









/******************************* Check matrix ***************************/

pSnake eatFood(aMatrix matrixMove, pSnake headSnake, int dir)
{
	pSnake newHeadSnake;
	newHeadSnake= new Snake;

	newHeadSnake->xDes= transXDes(headSnake->xDes, dir);
	newHeadSnake->yDes= transYDes(headSnake->yDes, dir);
	newHeadSnake->dir = dir;

	newHeadSnake->pDir= -1;
	newHeadSnake->next= headSnake;
	newHeadSnake->size= newHeadSnake->next->size + 1;

    headSnake->pDir= newHeadSnake->dir;
    matrixMove[newHeadSnake->xDes][newHeadSnake->yDes]= matrixMove[headSnake->xDes][headSnake->yDes];

	gotoXY(13, 24);
	cout << newHeadSnake->size - lengSnake;

    randomFood(matrixMove, headSnake);
	return headSnake= newHeadSnake;
//	printSnakeNext(matrixMove, headSnake);
}

int checkNextStep(int dir, pSnake headSnake, aMatrix matrixMove, int playerNum)
{
	int xHeadDes= transXDes(headSnake->xDes, dir);
	int yHeadDes= transYDes(headSnake->yDes, dir);

	if( matrixMove[xHeadDes][yHeadDes] == freeMove )
		return playerNum;
	else if( matrixMove[xHeadDes][yHeadDes] == food->value )
		return food->value;
	else
		return 0;
}









/********************************* Food *********************************/

void makeFood(aMatrix matrixMove, int xDes, int yDes)
{
    food->xDes= xDes;
    food->yDes= yDes;
	gotoXY(food->xDes, food->yDes);
	cout << (char)food->value;
	matrixMove[food->xDes][food->yDes]= food->value;
}

bool randomFood(aMatrix matrixMove, pSnake head)
{
	srand (time(NULL));
	int randomFood = rand() % ( (food->hight) * (food->width) - head->size );
	int Count= 0;
	for(int h= 1; h <= food->hight+1; h++)
	{
		for(int w= 1; w <= food->width+1; w++)
		{
			if( matrixMove[w][h] == freeMove )
			{
				Count++;
				if( Count == randomFood )
				{
					makeFood( matrixMove, w, h);
					return true;
				}
			}
		}
	}
	return false;
}








/******************************** Game **********************************/

void runSnakeFree(pSnake headSnake)
{
   	aMatrix matrix;
	makeWall("Free run", matrix, widthCMD, hightCMD);
	makeSnake(matrix, headSnake, 30, 10, 2, 2, lengSnake, player1);
	printSnakeFirst(headSnake, true );
    char key= keyRight;
    int check;
	while( true )
	{
        Sleep(speed);
	    fflush(stdin);
		checkKey(matrix, headSnake, key, check, player1);
        printSnakeFirst(headSnake, true);
        gotoXY(79,24);
	}
}

void runSnakeGame(pSnake headSnake)
{
   	aMatrix matrix;
	makeSnake(matrix, headSnake, 30, 10, 2, 2, lengSnake, player1);
	printSnakeFirst(headSnake, true );
	makeWall("A Hunting Snake", matrix, widthCMD, hightCMD-2);
	randomFood(matrix, headSnake);

	gotoXY(0, 24);
	cout << "Your score : 0";
    char key= keyRight;
    int checkMove= 1;
	while( checkMove )
	{
        Sleep(speed);
	    fflush(stdin);
		headSnake= checkKey(matrix, headSnake, key, checkMove, player1);
        printSnakeNext(matrix, headSnake);
	}
//	testMatrix(matrix, widthCMD, hightCMD);
}









/********************************** Pause Game **************************/

pSnake pauseGame(aMatrix matrixMove, pSnake head, char &key, int &checkMove, const int player)
{
	char Pause;
	while(1)
	{
		Pause= getch();
		if( Pause == 'p' || Pause == 'P' )
			return checkKey(matrixMove, head, key, checkMove, player);
	}
}









/************************** Print out screen ****************************/

void gotoXY(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(h,c);
}

/********************* Print a string ********************/

void printString(string something, int width, int hight)
{
	gotoXY(width, hight);
	cout << something;
}




/********************* Print out Snake *******************/
void printSnakeFirst(pSnake thisSnake, bool head)
{
	if( head )
	{
		gotoXY(thisSnake->xDes, thisSnake->yDes);
        printHead(thisSnake->dir);
	}
	else
	{
		gotoXY(thisSnake->xDes, thisSnake->yDes);
        printBody(thisSnake->dir, thisSnake->pDir);
	}
	if( thisSnake->next != NULL ) printSnakeFirst(thisSnake->next, false);
}

void printSnakeNext(aMatrix matrixMove, pSnake thisSnake)
{
    gotoXY(thisSnake->xDes, thisSnake->yDes);
    printHead(thisSnake->dir);
    matrixMove[thisSnake->xDes][thisSnake->yDes]= 1;

    gotoXY(thisSnake->next->xDes, thisSnake->next->yDes);
    printBody(thisSnake->next->dir, thisSnake->next->pDir);

    gotoXY(food->xDes,food->yDes);
}

void printHead(int thisDir)
{
    if( thisDir%2 )						//	Snake vertical		Doc
    {
        if( thisDir/2 )						//	Snake move up
        {
            cout << "^";							//	Alt + 30 = ▲
        }
        else								//	Snake move down
        {
            cout << "v";							//	Alt + 31 = ▼
        }
    }
    else								//	Snake horizontal	Ngang
    {
        if( thisDir/2 )						//	Snake move right
        {
            cout << ">";							//	Alt + 16 = ►
        }
        else								//	Snake move left
        {
            cout << "<";							//	Alt + 17 = ◄
        }
	}
}

void printBody(int dir, int preDir)
{
    if( dir%2 == preDir%2 )				//	Snake move straight		Thang
    {
        if( dir%2 )							//	Snake vertical		Doc
        {
            cout << vertical;
        }
        else								//	Snake horizontal	Ngang
        {
            cout << horizontal;
        }
    }
    else								//	Snake turn				Queo
    {
        dir= dir^2;

        if( dir*preDir == 0 )				//	A direction is left
        {
			if( dir + preDir == 1 )				//	A direction is down
			{
				cout << leftDown;
			}
			else								//	A direction is up
			{
				cout << leftUp;
			}
        }
        else								//	A direction i s right
        {
			if( dir + preDir -2 == 1 )			//	A direction is down
			{
				cout << rightDown;
			}
			else								//	A direction is up
			{
				cout << rightUp;
			}
        }
	}
}

void clearEndSnake(int xDes, int yDes)
{
    gotoXY(xDes, yDes);
    cout << " ";
    gotoXY(food->xDes,food->yDes);
}

/******************** Print out Wall *********************/

void printWall(aMatrix maxtrixWall, int w, int h, char wall)
{
	gotoXY(w, h);
	maxtrixWall[w][h]= wall;
	cout << wall;
}

void printNameWall(string wallName, int width)
{
	int toX= width/2 - wallName.size()/2 - 1;
    printString(" "+wallName+" ", toX, 0);
}

void makeWall(string wallName, aMatrix matrixWall, int width, int hight)
{
	for(int w= 1; w < width-1; w++)			//	make horizontal wall
	{
		printWall( matrixWall, w,       0, horizontal);
		printWall( matrixWall, w, hight-1, horizontal);
	}
	for(int h= 1; h < hight-1; h++)			//	make vertical wall
	{
		printWall( matrixWall, 0      , h, vertical);
		printWall( matrixWall, width-1, h, vertical);
	}
	{										//	make 4 corner
		printWall( matrixWall,       0,       0, rightDown);
		printWall( matrixWall,       0, hight-1, rightUp);
		printWall( matrixWall, width-1, hight-1, leftUp);
		printWall( matrixWall, width-1,       0, leftDown);
	}
	printNameWall(wallName, width);
}









/****************************** Translate *******************************/

char transKeyToTurn(char keyInput)
{
	switch( keyInput )
	{
		case keyUp:		return up;
		case keyDown:	return down;
		case keyLeft:	return lef;
		case keyRight:	return righ;
	}
}

int  transXDes(int xDes, int dir)
{
	switch(dir)
	{
		case lef:		return xDes-1;
		case righ:		return xDes+1;
		default:		return xDes;
	}
}

int  transYDes(int yDes, int dir)
{
	switch(dir)
	{
		case up:		return yDes-1;
		case down:		return yDes+1;
		default:		return yDes;
	}
}







/********************************* Test *********************************/

void testMatrix(aMatrix matrixMove, int width, int hight)
{
	gotoXY(0, 25);
    for(int h= 1; h < hight-3; h++)
	{
	    cout << " ";
        for(int w= 1; w < width-1; w++)
		{
			cout << (int)matrixMove[w][h];
		}
		cout << endl;
	}
}





/*	Had update by transXDes and transYDes

if( thisDir%2 )						//	Snake vertical		Doc
{
	if( thisDir/2 )						//	Snake move up
	{
		yThisDes++;
	}
	else								//	Snake move down
	{
		yThisDes--;
	}
}
else								//	Snake horizontal	Ngang
{
	if( thisDir/2 )						//	Snake move right
	{
		xThisDes--;
	}
	else								//	Snake move left
	{
		xThisDes++;
	}
}
*/



/*	Don't need

void runSnake(aMatrix matrixMove, pSnake head, char key)
{
    switch(key)
    {
        case keyUp:									            //	go up
            moveSnake(matrixMove, head, up,		true);	break;
        case keyLeft:								            //	go left
            moveSnake(matrixMove, head, lef,	true);	break;
        case keyRight:								            //	go right
            moveSnake(matrixMove, head, righ,	true);	break;
        case keyDown:								            //	go down
            moveSnake(matrixMove, head, down,	true);	break;
        default:
            break;
    }
}
*/
