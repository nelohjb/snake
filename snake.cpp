#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "snake.h"
#include <time.h>
using namespace std;


//setCP()��hideCursor()ʱҪ�õ����
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);


//���ù��λ��
void setCP(int x, int y){
	/*HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);*/
	COORD setps;
	setps.X = x; setps.Y = y;
	SetConsoleCursorPosition(hCon, setps);
}
//��ȡ���̷����
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
//���ع��
void hideCursor(){
	/*HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);*/
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hCon, &info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &info);
}
//��ǽ
void createWall() {
	setCP(0, 0);
	for (int i = 0; i < WallX; i++)
		cout << "��";
	setCP(0, WallY);
	for (int i = 0; i < WallX; i++)
		cout << "��";

	for (int i = 1; i < WallY; i++) {
		setCP(0, i);
		cout << "��";
		setCP(2 * WallX - 2, i);
		cout << "��";
	}
}





//Snake ��

//��������
Snake::Snake() {
	length = 3;
	direction = RIGHT;
	speed = 550;
	score = 0;
	grade = 1;
	countFood = 0;		/******** ���� ********/
	pos[0].x = 4; pos[1].x = 6; pos[2].x = 8;
	pos[0].y = pos[1].y = pos[2].y = 4;
	/*��ʼ�� �������*/
	for (int i = 0; i < length; i++) {
		setCP(pos[i].x, pos[i].y);
		cout << "��";
	}
}
//���ӳ���
void Snake::addSnake() {
	for (int i = length - 1; i >= 0; i--) {
		pos[i + 1].x = pos[i].x;
		pos[i + 1].y = pos[i].y;
	}
	pos[0].x = lastTail.x;
	pos[0].y = lastTail.y;
	length++;
}
//������ߣ��������
void Snake::clearSnake() {
	//�����β
	setCP(pos[0].x, pos[0].y);
	cout << ' ';
}
void Snake::printSnake() {
	//�������ͷ(�������ڵ���ͷ)
	setCP(pos[length - 1].x, pos[length - 1].y);
	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | 3);//����Ϊ��ɫ 3
	cout << "��";
	setCP(pos[length - 2].x, pos[length - 2].y);	//��ǰ��ͷ���
	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | 7);//����Ϊ��ɫ 7
	cout << "��";

}
//�ƶ�
void Snake::moveU() {
	int i;
	lastTail = pos[0];	//�洢β������Ա����ӳ���ʱ�ڽ�β����
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
//snake ��ײ
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
//�ж���Ӯ
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
//�����������Ϣ  speed grade score
void Snake::printInfo() {
	//�жϲ����ݶ�
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
	setCP(2 * WallX + 2, 1); cout << "�ȼ���" << grade;
	setCP(2 * WallX + 2, 3); cout << "������" << score;
	setCP(2 * WallX + 2, 5); cout << "�ٶȣ�" << speed;

}



//food ��ײ
bool Snake::knockSnake() {
	for (int i = 0; i < length; i++) {
		if (food.x == pos[i].x && food.y == pos[i].y) //��һ��yд����x,  Hours wasted
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
	srand(unsigned(time(NULL)));		//amazing!	//����ѭ����������
	do{
		food.x = rand() % WallX;
		food.y = rand() % WallY;
		avoidSingle();
		avoidWall();
	}while (knockSnake());
		setCP(food.x, food.y);
		cout << "��";
		countFood++;                   //�������� ���ֺ͵ȼ�
}
