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
#define INTERVAL  15	//���Ӽ�ļ��
#define GRID_SIZE 117   //���ӵĿ�Ⱥ͸߶�
//38 * 195
IMAGE bk;				//����
//�洢���ݵ�����
int map[ROW][COL];

int flag = 0; //�Ƿ�����һ������
//����ͼƬ��Դ
IMAGE imgs[11];
//���⴦��հ�ͼƬ
IMAGE zero;
void loadResource()
{
	loadimage(&bk,"./bk.png", 584, 734);
	loadimage(&zero,"./0.jpg", GRID_SIZE, GRID_SIZE);
	for (int i = 2, j = 0; i <= 2048; i *= 2, j++)
	{
		char imgPath[50] = { 0 };                           //�ַ�����ʽ��
		sprintf_s(imgPath, "./%d.jpg", i);           //������(����) ��ʽ�ַ���
		for (int i = 0; i < 17; i++)					    //�ַ��������Ҫ��forѭ������ӡ|������"%s"�ķ�ʽ��ӡ
		{
			printf("%c", imgPath[i]);
		}
		putchar('\n');

		//ע��: ͼƬҪһ������һ�����
		loadimage(&imgs[j],imgPath, GRID_SIZE, GRID_SIZE); //���ֽ��ַ���
	}
}

//�������2or4 2�ĸ��ʸ���
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
//������հ״����һ����
void mapFillNumber()
{
	//������������±�
	while (true)
	{
		//��β����±��ʱ�򣬿��ܻ��ظ� 0 1 0 1 ��Ȼ���ʱȽ�С�������п���
		int r = rand() % ROW;	//0 1 2 3
		int c = rand() % COL;	//0 1 2 3
		//����������� �����ж�ԭ��λ���ǲ��ǵ��� 0 ������� 0 �ŷ�������
		if (map[r][c] == 0)
		{
			map[r][c] = createNumber();
			return;
		}
	}
}
//��ʼ��
void init()
{
	//�������������
	srand(time(NULL));

	//�������һ���������ҷŵ���������ȥ map[?][?] = createNumber();
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}
}
//����
void draw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//��ÿ���������Ͻǵ����������
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
//�����ƶ�
void moveUp()
{
	/*
	�����ƶ�:����ÿ��
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
					if (temp + 1 != begin)//���temp+1��begn����ͬһ��λ��,����begin���ڵ�λ�õ������ÿ�
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
//�����ƶ�
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
//�����ƶ�
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
//�����ƶ�
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
//�ƶ�����
void move()
{
	//��ȡ���̰��� 72 80 75 77
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
	//����
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