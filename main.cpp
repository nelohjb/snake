#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "snake.h"
using namespace std;



//��Ϸ������
int main() {
	hideCursor();		//����һ�ξͿ������ع��
	Snake snake;			//���� ��ʼ�������(3��)
	createWall();
	snake.createFood();
	while(1){
		snake.printInfo();
		snake.clearSnake();		//���ԭ��
		int direction = newDirection();	//���뷽��
		int tempLen = snake.getLen();	//ԭ������ǰ��
		snake.move(direction);		//�ƶ�
		if (snake.knockFood())	
			snake.addSnake();
		snake.printSnake();	//�������	//ԭ����Sleep()֮ǰ  //��ʾҧ���Լ���ײ��ǽ������	//ײǽ��
		if (snake.Judge() == CONTINUE);
		else break;			//��orӮ ��break, ֻ��continue��������.
		if(snake.getLen()!=tempLen)		//�Ե�food->��������->��ǰԭ���������ֳ��� ->>������food
			snake.createFood();
		Sleep(snake.getSpeed());
	}
	return 0;
}