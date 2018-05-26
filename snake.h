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

//���ù��λ��
void setCP(int x, int y);
//��ȡ���̷����
int newDirection();
//���ع��
void hideCursor();
//��ǽ
void createWall();



struct Position {
	int x;
	int y;
};



class Snake {
public:
	void clearSnake();
	void printSnake();

	bool knockSnake();	//food 			/******** ���� ********/
	bool knockFood();	//snake 
	bool knockSelf();	//snake 
	bool knockWall();	//snake 	

	void avoidSingle();	//food avoid	/******** ���� ********/
	void avoidWall();	//food avoid	/******** ���� ********/

	void createFood();					/******** ���� ********/
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
	Position food;	/******** ��ת�� ********/
	int speed;
	int score;
	int grade;
	int countFood;	/******** ��ת�� ********/
	int length;
	int direction;
};

