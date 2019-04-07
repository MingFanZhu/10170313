// 跳马问题.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

//棋盘点类
class Point
{
public:
	//构造函数
	Point(int a = 0, int b = 0)
	{
		x = a;
		y = b;
	}

	//跳跃（改变点的值）
	void Change(int a, int b)
	{
		x += a;
		y += b;
	}

	//运算符重载“==”
	bool operator ==(Point temp)
	{
		if (x == temp.x&&y == temp.y)
			return true;
		else
			return false;
	}

	//运算符重载“=”
	Point operator =(Point temp)
	{
		Point pt(temp.x, temp.y);
		return pt;
	}

	int x;
	int y;
};

#define mapsize 4//棋盘大小
int num = 0;//存储路径数目
bool beg = true;//标记是否是开始，主要避免起始点判断为到达终点的情况
Point temp1;//存储起始点
list <Point> roads;//包含点的容器
int jump[8][2] = { {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };//跳跃的方向

//判断点是否落在棋盘内
bool In(Point horse)
{
	if ((horse.x < mapsize&&horse.x>=0) && (horse.y < mapsize&&horse.y>=0))
		return true;
	else
		return false;
}

//格式化输出路径
void PrintRoads(list <Point> roads)
{
	for (list <Point>::iterator it = roads.begin(); it != roads.end(); it++)
	{
		cout << "(" << it->x + 1 << "," << it->y + 1 << ") ";
	}
}

//递归函数
int Jump(Point horse,Point temp,int _x,int _y,int points[][mapsize])
{
	horse.Change(_x, _y);//跳跃（_x,_y）

	//判断是否出界，出界则回退并退出递归
	if (In(horse) == false)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	//判断是否跳回了起始点，是则输出路径并退出递归
	if (beg == false && horse == temp)
	{
		num++;
		cout << "road:" << num << " ";
		PrintRoads(roads);
		cout << "(" << temp.x + 1 << "," << temp.y + 1 << ")" << endl;
		horse.Change(-_x, -_y);
		return 0;
	}
	//判断是否到达了路径上的点，是则回退并退出递归，不是则在棋盘上标记这一点
	if (points[horse.x][horse.y] == 1)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	else
		points[horse.x][horse.y] = 1;

	beg = false;
	roads.push_back(horse);//在路径中加入新点

	int points1[mapsize][mapsize];
	for (int i = 0; i < 8; i++)
	{
		for (int x = 0; x < mapsize; x++)
			for (int y = 0; y < mapsize; y++)
				points1[x][y] = points[x][y];//记录现在的棋盘上的路径经过的点
		Jump(horse, temp, jump[i][0], jump[i][1],points1);//进入新的方向进行跳跃
	}

	roads.pop_back();//尝试完所有方向后将现在的点从路径中删除
	horse.Change(-_x, -_y);//回退到上一个点
	return 0;
}

//输出的棋盘从1开始，程序运行时从0开始数，包括马的坐标
int main()
{
	int x, y = 0;
	cout << "请给出起始点x和y(本程序棋盘为坐标从1至4的正方形棋盘)";
	cin >> x >> y;
	Point horse(0, 0);
	horse.x = x-1;
	horse.y = y-1;
	Point temp = horse;
	temp1 = horse;
	int points[mapsize][mapsize] = { 0 };
	Jump(horse, temp, 0, 0, points);
    return 0;
}