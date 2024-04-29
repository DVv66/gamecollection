#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>	
#include<math.h>
#include<conio.h>
#include <graphics.h>
#include"tools.h"
#define ROW 4
#define COL 4	
#define INTERVAL  15	//格子间的间隔
#define GRID_SIZE 117   //格子的宽度和高度
//38 * 195
IMAGE bk;				//背景
//存储数据的数组
int map[ROW][COL];

int flag = 0; //是否生成一个数字
//定义图片资源
IMAGE imgs[11];
//特殊处理空白图片
IMAGE zero;
void loadResource()
{
	loadimage(&bk,"./bk.png", 584, 734);
	loadimage(&zero,"./0.jpg", GRID_SIZE, GRID_SIZE);
	for (int i = 2, j = 0; i <= 2048; i *= 2, j++)
	{
		char imgPath[50] = { 0 };                           //字符串格式化
		sprintf_s(imgPath, "./%d.jpg", i);           //缓冲区(数组) 格式字符串
		for (int i = 0; i < 17; i++)					    //字符数组必须要用for循环做打印|不能用"%s"的方式打印
		{
			printf("%c", imgPath[i]);
		}
		putchar('\n');

		//注意: 图片要一个挨着一个输出
		loadimage(&imgs[j],imgPath, GRID_SIZE, GRID_SIZE); //多字节字符集
	}
}

//随机产生2or4 2的概率更高
int createNumber()
{
	if (rand() % 10 != 0)
	{
		return  2;
	}
	else
	{
		return 4;
	}
}
//给数组空白处填充一个数
void mapFillNumber()
{
	//随机产生两个下标
	while (true)
	{
		//多次产生下标的时候，可能会重复 0 1 0 1 虽然概率比较小但还是有可能
		int r = rand() % ROW;	//0 1 2 3
		int c = rand() % COL;	//0 1 2 3
		//避免出现问题 首先判断原来位置是不是等于 0 如果等于 0 才放入数据
		if (map[r][c] == 0)
		{
			map[r][c] = createNumber();
			return;
		}
	}
}
//初始化
void init()
{
	//设置随机数种子
	srand(time(NULL));

	//随机产生一个数，并且放到数组里面去 map[?][?] = createNumber();
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}
}
//绘制
void draw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//把每个格子左上角的坐标求出来
			int x = k * GRID_SIZE + (k + 1) * INTERVAL + 38 - 18;
			int y = i * GRID_SIZE + (i + 1) * INTERVAL + 195 - 17;
			switch (map[i][k]) {
			case 0:
				drawImg(x, y, &zero);
				break;
			case 2:
				drawImg(x, y, &imgs[0]);
				break;
			case 4:
				drawImg(x, y, &imgs[1]);
				break;
			case 8:
				drawImg(x, y, &imgs[2]);
				break;
			case 16:
				drawImg(x, y, &imgs[3]);
				break;
			case 32:
				drawImg(x, y, &imgs[4]);
				break;
			case 64:
				drawImg(x, y, &imgs[5]);
				break;
			case 128:
				drawImg(x, y, &imgs[6]);
				break;
			case 256:
				drawImg(x, y, &imgs[7]);
				break;
			case 512:
				drawImg(x, y, &imgs[8]);
				break;
			case 1024:
				drawImg(x, y, &imgs[9]);
				break;
			case 2048:
				drawImg(x, y, &imgs[10]);
				break;
			}
		}
		printf("\n");
	}
}
//向上移动
void moveUp()
{
	/*
	向上移动:遍历每列
	*/
	for (int i = 0; i < COL; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
					temp++;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)//如果temp+1和begn不在同一个位置,就让begin所在的位置的数字置空
					{
						map[begin][i] = 0;
					}
					temp++;
				}
				flag = 1;
			}
		}
	}
}
//向下移动
void moveDown()
{
	for (int i = 0; i < COL; i++)
	{
		int temp = ROW - 1;
		for (int begin = ROW - 2; begin >= 0; begin--)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
					temp--;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if ((temp - 1) != begin)
					{
						map[begin][i] = 0;
					}
					temp--;
				}
				flag = 1;
			}
		}
	}
}
//向左移动
void moveLeft()
{
	for (int i = 0; i < COL; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
					temp++;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
					temp++;
				}
				flag = 1;
			}
		}
	}
}
//向右移动
void moveRight()
{
	for (int i = 0; i < ROW; i++)
	{
		int temp = COL - 1;
		for (int begin = COL - 2; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
					temp--;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
					temp--;
				}
				flag = 1;
			}
		}
	}
}
//移动格子
void move()
{
	//获取键盘按键 72 80 75 77
	int key = _getch();
	switch (key)
	{
	case 'W':
	case 'w':
	case 72:
		moveUp();
		break;
	case 80:
		moveDown();
		break;
	case 75:
		moveLeft();
		break;
	case 77:
		moveRight();
		break;
	}
	if (flag == 1)
	{
		mapFillNumber();
		flag = 0;
	}
}
int main()
{
	//窗口
	initgraph(584, 734, EW_SHOWCONSOLE);

	init();
	loadResource();


	drawImg(0, 0, &bk);
	while (true)
	{
		draw();
		move();
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				printf("%d", map[i][j]);
			}
			printf("\n");
		}
	}
	getchar();
	return 0;
}