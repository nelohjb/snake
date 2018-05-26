#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "snake.h"
#include <time.h>
using namespace std;


//setCP()和hideCursor()时要用到这个
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);


//设置光标位置
void setCP(int x, int y){
	/*HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);*/
	COORD setps;
	setps.X = x; setps.Y = y;
	SetConsoleCursorPosition(hCon, setps);
}
//读取键盘方向键
int newDirection() {
	if (GetAsyncKeyState(VK_UP))
		return UP;
	else if (GetAsyncKeyState(VK_DOWN))
		return DOWN;
	else if (GetAsyncKeyState(VK_LEFT))
		return LEFT;
	else if (GetAsyncKeyState(VK_RIGHT))
		return RIGHT;
	else return 0;
}
//隐藏光标
void hideCursor(){
	/*HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);*/
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hCon, &info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &info);
}
//造墙
void createWall() {
	setCP(0, 0);
	for (int i = 0; i < WallX; i++)
		cout << "▉";
	setCP(0, WallY);
	for (int i = 0; i < WallX; i++)
		cout << "▉";

	for (int i = 1; i < WallY; i++) {
		setCP(0, i);
		cout << "▉";
		setCP(2 * WallX - 2, i);
		cout << "▉";
	}
}





//Snake 类

//析构函数
Snake::Snake() {
	length = 3;
	direction = RIGHT;
	speed = 550;
	score = 0;
	grade = 1;
	countFood = 0;		/******** 待改 ********/
	pos[0].x = 4; pos[1].x = 6; pos[2].x = 8;
	pos[0].y = pos[1].y = pos[2].y = 4;
	/*初始化 输出蛇身*/
	for (int i = 0; i < length; i++) {
		setCP(pos[i].x, pos[i].y);
		cout << "◆";
	}
}
//增加长度
void Snake::addSnake() {
	for (int i = length - 1; i >= 0; i--) {
		pos[i + 1].x = pos[i].x;
		pos[i + 1].y = pos[i].y;
	}
	pos[0].x = lastTail.x;
	pos[0].y = lastTail.y;
	length++;
}
//清除旧蛇，输出新蛇
void Snake::clearSnake() {
	//清除蛇尾
	setCP(pos[0].x, pos[0].y);
	cout << ' ';
}
void Snake::printSnake() {
	//输出新蛇头(就是现在的蛇头)
	setCP(pos[length - 1].x, pos[length - 1].y);
	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | 3);//设置为蓝色 3
	cout << "◆";
	setCP(pos[length - 2].x, pos[length - 2].y);	//将前蛇头变白
	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | 7);//设置为白色 7
	cout << "◆";

}
//移动
void Snake::moveU() {
	int i;
	lastTail = pos[0];	//存储尾巴左边以备增加长度时在结尾增加
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].y--;
	direction=UP;
}
void Snake::moveD() {
	int i;
	lastTail = pos[0];
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].y++;
	direction=DOWN;
}
void Snake::moveL() {
	int i;
	lastTail = pos[0];
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].x -= 2;
	direction=LEFT;
}
void Snake::moveR() {
	int i;
	lastTail = pos[0];
	for (i = 0; i < length - 1; i++) {
		pos[i] = pos[i + 1];
	}
	pos[i].x += 2;
	direction=RIGHT;
}
void Snake::move(int direct ) {
	if (direct == 0)
		move(direction);
	if (direct == UP)
		if (direction == DOWN)
			moveD();
		else
			moveU();
	if (direct == DOWN)
		if (direction == UP)
			moveU();
		else
			moveD();
	if (direct == LEFT)
		if (direction == RIGHT)
			moveR();
		else
			moveL();
	if (direct == RIGHT)
		if (direction == LEFT)
			moveL();
		else
			moveR();
}
//snake 碰撞
bool Snake::knockFood() {
	if ((pos[length - 1].x == food.x) && (pos[length - 1].y == food.y)) {
		return 1;
	}
	else if ((pos[length - 2].x == food.x) && (pos[length - 2].y == food.y))
		return 1;
	else
		return 0;
}
bool Snake::knockSelf() {
	for (int i = 0; i < length - 1; i++) 
		if (pos[i].x == pos[length - 1].x && pos[i].y == pos[length - 1].y)
			return 1;
	return 0;
}
bool Snake::knockWall() {
	if (pos[length - 1].x <= 0 || pos[length - 1].y <= 0 || pos[length - 1].x >= (2*WallX) || pos[length - 1].y >= WallY )
		return 1;
	return 0;
}
//判断输赢
int Snake::Judge() {
	//LOSE
	if (knockSelf() || knockWall()) {
		setCP(2 * WallX + 2, WallY - 4);
		cout << "Sorry! You lose!";
		setCP(2 * WallX + 2, WallY);

		return LOSE;
	}
	//WIN
	if (length == maxlen) {
		setCP(2 * WallX + 2, WallY - 4);
		cout << "Congratulations! You win!" << endl;
		setCP(2 * WallX + 2, WallY);

		return WIN;
	}
	return CONTINUE;

}
//设置与输出信息  speed grade score
void Snake::printInfo() {
	//判断策略暂定
	score = 10 * (countFood - 1);	//1000
	if (score >= 1000)	 grade = 10;
	else if (score >= 800)grade = 9;
	else if (score >= 650)grade = 8;
	else if (score >= 500)grade = 7;
	else if (score >= 350)grade = 6;
	else if (score >= 250)grade = 5;
	else if (score >= 150)grade = 4;
	else if (score >= 100)grade = 3;
	else if (score >= 50) grade = 2;
	speed = 600 - 50 * grade;
	setCP(2 * WallX + 2, 1); cout << "等级：" << grade;
	setCP(2 * WallX + 2, 3); cout << "分数：" << score;
	setCP(2 * WallX + 2, 5); cout << "速度：" << speed;

}



//food 碰撞
bool Snake::knockSnake() {
	for (int i = 0; i < length; i++) {
		if (food.x == pos[i].x && food.y == pos[i].y) //第一个y写成了x,  Hours wasted
			return 1;
	}
	return 0;
}
//food avoid
void Snake::avoidSingle() {
	if (food.x % 2 != 0)food.x++;
}
void Snake::avoidWall() {
	if (food.x <= 2) food.x += 4;
	if (food.x >= WallX - 2) food.x -= 4;
	if (food.y <= 2) food.y += 4;
	if (food.y >= WallY - 2) food.y -= 4;
}
//food
void Snake::createFood() {
	srand(unsigned(time(NULL)));		//amazing!	//放在循环体外快多了
	do{
		food.x = rand() % WallX;
		food.y = rand() % WallY;
		avoidSingle();
		avoidWall();
	}while (knockSnake());
		setCP(food.x, food.y);
		cout << "●";
		countFood++;                   //用来计算 积分和等级
}
