#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "snake.h"
using namespace std;



//游戏主函数
int main() {
	hideCursor();		//调用一次就可以隐藏光标
	Snake snake;			//包含 初始输出蛇身(3节)
	createWall();
	snake.createFood();
	while(1){
		snake.printInfo();
		snake.clearSnake();		//清除原蛇
		int direction = newDirection();	//输入方向
		int tempLen = snake.getLen();	//原长（吃前）
		snake.move(direction);		//移动
		if (snake.knockFood())	
			snake.addSnake();
		snake.printSnake();	//输出新蛇	//原置于Sleep()之前  //显示咬到自己或撞到墙的样子	//撞墙丑
		if (snake.Judge() == CONTINUE);
		else break;			//输or赢 都break, 只有continue不做操作.
		if(snake.getLen()!=tempLen)		//吃掉food->长度增加->吃前原长不等于现长度 ->>产生新food
			snake.createFood();
		Sleep(snake.getSpeed());
	}
	return 0;
}