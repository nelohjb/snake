#pragma once

#define maxlen 104
#define WallX 40
#define WallY 24

#define LOSE 1
#define WIN 2
#define CONTINUE 3

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//设置光标位置
void setCP(int x, int y);
//读取键盘方向键
int newDirection();
//隐藏光标
void hideCursor();
//造墙
void createWall();



struct Position {
	int x;
	int y;
};



class Snake {
public:
	void clearSnake();
	void printSnake();

	bool knockSnake();	//food 		/******** 待改 ********/
	bool knockFood();	//snake 
	bool knockSelf();	//snake 
	bool knockWall();	//snake 	

	void avoidSingle();	//food avoid	/******** 待改 ********/
	void avoidWall();	//food avoid	/******** 待改 ********/

	void createFood();			/******** 待改 ********/
	int Judge();
	void printInfo();

	void moveU();
	void moveD();
	void moveL();
	void moveR();
	void move(int direct = 0);
	/******************************/
	Snake();
	int getLen() { return length; }
	int getSpeed() { return speed; }
	void addSnake();
private:
	Position pos[maxlen];
	Position lastTail;
	Position food;			/******** 待改 ********/
	int speed;
	int score;
	int grade;
	int countFood;			/******** 待改 ********/
	int length;
	int direction;
};

