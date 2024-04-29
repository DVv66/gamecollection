
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

#define width 1042		//���ڿ��
#define height 757		//���ڸ߶�
#define pi 3.14159

#define hook_length 30		//���ӵ�צ��
#define hook_speed 25		//�����ٶ�

#define gold_count_max 10		//�����������ֵ
#define stone_count_max 7		//ʯͷ�������ֵ
#define gold_count_min 5		//����������Сֵ

#define small_gold_r 15			//С�Ž��ӵĴ�С
#define mid_gold_r 30
#define big_gold_r 100
#define small_gold_value 25		//С�Ž��ӵļ�ֵ
#define mid_gold_value 200
#define big_gold_value 500
#define small_gold_weight 1		//С�Ž��ӵ�������������Ӱ�칳�ӷ����ٶȣ�
#define mid_gold_weight 5
#define big_gold_weight 15

#define small_stone_r 10
#define mid_stone_r 20
#define big_stone_r 50
#define small_stone_value 10
#define mid_stone_value 30
#define big_stone_value 50
#define small_stone_weight 5
#define mid_stone_weight 10
#define big_stone_weight 15

#define time_limit 90		//ÿ�ص��޶�ʱ��

#define gold_color 	RGB(253, 189, 0)		//���ӵ���ɫ
#define stone_color  RGB(145,145,145)		//ʯͷ����ɫ
#pragma warning (disable:4996)

struct gold
{
	int value;
	int weight;
	int x, y;
	int r;
	bool is_be_grap = false;
}golds[gold_count_max];

struct stone
{
	int value;
	int weight;
	int x, y;
	int r;
	bool is_be_grap = false;
}stones[stone_count_max];

//���ƹ���
void draw_hook(int x, int y, float jiaodu)
{
	setlinecolor(BLACK);

	line(x, y, x - hook_length * cos(jiaodu), y + hook_length * sin(jiaodu));
	line(x, y, x - hook_length * cos(jiaodu + pi / 2), y + hook_length * sin(jiaodu + pi / 2));
}

//���ƹ��ӷ���ͷ��ص�ֱ��
void draw_hook_launch_or_recovery(int x, int y, float jiaodu, int s)
{
	setlinecolor(BLACK);

	float j = jiaodu + pi / 4;

	line(x, y, x - s * cos(j), y + s * sin(j));
}

//������������
void draw_worlds(int score, int target_score, time_t time0, time_t time1, int pass_count)
{
	settextcolor(GREEN);
	settextstyle(50, 0, _T("����"));

	TCHAR str1[15];
	_stprintf(str1, L"��Ǯ��%d", score);
	outtextxy(0, 0, str1);

	TCHAR str2[20];
	_stprintf(str2, L"Ŀ���Ǯ��%d", target_score);
	outtextxy(0, 50, str2);

	TCHAR str3[8];
	long t = time0 + time_limit - time1;
	_stprintf(str3, L"ʱ�䣺%ld", t);
	outtextxy(width - 200, 0, str3);

	TCHAR str4[8];
	_stprintf(str4, L"��%d��", pass_count);
	outtextxy(width - 150, 50, str4);

	setlinecolor(RED);
	line(0, 100, width, 100);
}

//�ж�Բ��Բ֮���Ƿ����10���ϵľ���
bool circle_meet(int x0, int y0, int r0, int x1, int y1, int r1)
{
	int a = x0 - x1;
	int b = y0 - y1;
	if (a * a + b * b + 100 <= (r0 + r1) * (r0 + r1))
		return true;
	return false;
}

//����ʯͷ�ͽ��ӵ�����ʹ�С
void creat_gold_and_stone(struct gold* golds, int gold_count, struct stone* stones, int stone_count, int pass_count)
{
	for (int i = 0; i < gold_count; i++)
	{
		int j = rand() % 7;
		switch (j)
		{
		case 0:case 1:case 2:case 3:
			golds[i].value = small_gold_value;
			golds[i].weight = small_gold_weight;
			golds[i].r = small_gold_r;
			break;
		case 4:case 5:
			golds[i].value = mid_gold_value;
			golds[i].weight = mid_gold_weight;
			golds[i].r = mid_gold_r;
			break;
		case 6:
			golds[i].value = big_gold_value;
			golds[i].weight = big_gold_weight;
			golds[i].r = big_gold_r;
			break;
		}
	}
	for (int i = 0; i < gold_count; i++)
	{
		while (1)
		{
			int j;
			golds[i].x = rand() % (width - 2 * golds[i].r + 1) + golds[i].r;
			golds[i].y = rand() % (height - 2 * golds[i].r - 201) + golds[i].r + 200;
			for (j = 0; j < i; j++)
			{
				if (circle_meet(golds[i].x, golds[i].y, golds[i].r, golds[j].x, golds[j].y, golds[j].r))
					break;
			}
			if (j == i)
				break;
		}
	}
	for (int i = 0; i < stone_count; i++)
	{
		int j = rand() % 3;
		switch (j)
		{
		case 0:
			stones[i].value = small_stone_value;
			stones[i].weight = small_stone_weight;
			stones[i].r = small_stone_r;
			break;
		case 1:
			stones[i].value = mid_stone_value;
			stones[i].weight = mid_stone_weight;
			stones[i].r = mid_gold_r;
			break;
		case 2:
			stones[i].value = big_stone_value;
			stones[i].weight = big_stone_weight;
			stones[i].r = big_stone_r;
			break;
		}
	}
	for (int i = 0; i < stone_count; i++)
	{
		while (1)
		{
			int j, k;
			stones[i].x = rand() % (width - 2 * stones[i].r + 1) + stones[i].r;
			stones[i].y = rand() % (height - 2 * stones[i].r - 201) + stones[i].r + 200;
			for (j = 0; j < i; j++)
			{
				if (circle_meet(stones[i].x, stones[i].y, stones[i].r, stones[j].x, stones[j].y, stones[j].r))
					break;
			}
			for (k = 0; k < gold_count; k++)
			{
				if (circle_meet(stones[i].x, stones[i].y, stones[i].r, golds[k].x, golds[k].y, golds[k].r))
					break;
			}
			if (j == i &&k == gold_count)
				break;
		}
	}
}

//����ʯͷ�ͽ���
void draw_gold_and_stone(struct gold* golds, int gold_count, struct stone* stones, int stone_count)
{
	setfillcolor(gold_color);
	for (int i = 0; i < gold_count; i++)
		if (!golds[i].is_be_grap)
			fillcircle(golds[i].x, golds[i].y, golds[i].r);

	setfillcolor(stone_color);
	for (int i = 0; i < stone_count; i++)
		if (!stones[i].is_be_grap)
			fillcircle(stones[i].x, stones[i].y, stones[i].r);
}

//�жϵ��Ƿ���Բ��
bool is_circle_include_spot(int spot_x, int spot_y, int circle_x, int circle_y, int circle_r)
{
	int x = spot_x - circle_x;
	int y = spot_y - circle_y;
	return x * x + y * y <= circle_r * circle_r;
}

//�����ӵ�������ÿ��ʯͷ�ͽ��ӽ��бȽϣ��ж��Ƿ�ץ��ʯͷ�����ͬʱ��Ǳ�ץס��
int is_hook_grap_object(int x0, int y0, float jiaodu, int s, struct gold* golds, int gold_count, struct stone* stones, int stone_count)
{
	float j = jiaodu + pi / 4;
	int x1 = x0 - s * cos(j);
	int y1 = y0 + s * sin(j);
	int x2 = x1 - hook_length * cos(jiaodu);
	int y2 = y1 + hook_length * sin(jiaodu);
	int x3 = x1 - hook_length * cos(jiaodu + pi / 2);
	int y3 = y1 + hook_length * sin(jiaodu + pi / 2);
	for (int i = 0; i < gold_count; i++)
		if (!golds[i].is_be_grap&&is_circle_include_spot(x1, y1, golds[i].x, golds[i].y, golds[i].r))
		{
			golds[i].is_be_grap = true;
			return i;
		}
	for (int i = 0; i < stone_count; i++)
		if (!stones[i].is_be_grap&&is_circle_include_spot(x1, y1, stones[i].x, stones[i].y, stones[i].r))
		{
			stones[i].is_be_grap = true;
			return i + 10;
		}
	return -1;
}

//���ƹ���ץס���巵�ص��龰
void draw_hook_and_object(int x, int y, float jiaodu, int s, int object)
{
	float j = jiaodu + pi / 4;
	int x0 = x - s * cos(j);
	int y0 = y + s * sin(j);
	if (object < 10)
	{
		setfillcolor(gold_color);
		fillcircle(x0 - golds[object].r * cos(j), y0 + golds[object].r * sin(j), golds[object].r);
	}
	else
	{
		setfillcolor(stone_color);
		fillcircle(x0 - stones[object - 10].r * cos(j), y0 + stones[object - 10].r * sin(j), stones[object - 10].r);
	}

	setlinecolor(RED);
	line(x0, y0, x0 - hook_length * cos(jiaodu), y0 + hook_length * sin(jiaodu));
	line(x0, y0, x0 - hook_length * cos(jiaodu + pi / 2), y0 + hook_length * sin(jiaodu + pi / 2));
	line(x0, y0, x0 - s * cos(j), y0 + s * sin(j));
}

int main()
{
	initgraph(width, height);
	setbkcolor(WHITE);
	cleardevice();
	float jiaodu = -pi / 4;		//���ӵ�ǰ��ת�ĽǶ�
	bool flag = true;
	bool is_away = false;		//�����Ƿ���
	bool is_grap_object = false;		//�����Ƿ�ץס����
	bool is_hook_out = false;		//�����Ƿ����
	bool time_flag = true;			//�Ƿ�ʱ
	int x0 = width / 2, y0 = 100;		//��������
	int hook_away_length = 0;		//�����뿪ʱ��ֱ�߳���
	int score = 0;			//��ǰ��Ǯ
	int target_score = 600;			//Ŀ���Ǯ
	int pass_count = 1;			//��ǰ�ؿ�
	int object;			//��ץס������
	srand((unsigned)time(NULL));		//�����������
	BeginBatchDraw();
	while (1)
	{
		int gold_count = rand() % 6 + 5;
		int stone_count = rand() % (10 - pass_count) + pass_count;
		time_flag = true;
		creat_gold_and_stone(golds, gold_count, stones, stone_count, pass_count);
		time_t time0 = time(NULL);
		time_t time1 = time(NULL);
		draw_gold_and_stone(golds, gold_count, stones, stone_count);
		while (time_flag)
		{
			draw_worlds(score, target_score, time0, time1, pass_count);
			draw_gold_and_stone(golds, gold_count, stones, stone_count);
			draw_hook(x0, y0, jiaodu);
			if (kbhit() &&!is_away)
			{
				char older = getch();
				if (older == 's')
				{
					is_away = true;
					BeginBatchDraw();
					while (!is_grap_object && !is_hook_out)
					{
						hook_away_length += hook_speed;
						draw_worlds(score, target_score, time0, time1, pass_count);
						draw_hook_launch_or_recovery(x0, y0, jiaodu, hook_away_length);
						draw_gold_and_stone(golds, gold_count, stones, stone_count);
						FlushBatchDraw();
						Sleep(100);
						time1 = time(NULL);
						if (time1 - time0 > time_limit)
						{
							time_flag = false;
							break;
						}
						cleardevice();
						if (x0 - hook_away_length * cos(jiaodu + pi / 4) <= 0 || x0 - hook_away_length * cos(jiaodu + pi / 4) >= width || y0 + hook_away_length * sin(jiaodu + pi / 4) >= height)
							is_hook_out = true;
						if ((object = is_hook_grap_object(x0, y0, jiaodu, hook_away_length, golds, gold_count, stones, stone_count)) != -1)
							is_grap_object = true;
					}
					if (is_hook_out)
					{
						BeginBatchDraw();
						while (is_hook_out)
						{
							hook_away_length -= hook_speed;
							draw_worlds(score, target_score, time0, time1, pass_count);
							draw_hook_launch_or_recovery(x0, y0, jiaodu, hook_away_length);
							draw_gold_and_stone(golds, gold_count, stones, stone_count);
							FlushBatchDraw();
							Sleep(100);
							time1 = time(NULL);
							if (time1 - time0 > time_limit)
							{
								time_flag = false;
								break;
							}
							cleardevice();
							if (hook_away_length <= 0)
							{
								hook_away_length = 0;
								is_away = false;
								is_hook_out = false;
								draw_worlds(score, target_score, time0, time1, pass_count);
								draw_gold_and_stone(golds, gold_count, stones, stone_count);
								draw_hook(x0, y0, jiaodu);
							}
						}
					}
					if (is_grap_object)
					{
						BeginBatchDraw();
						while (is_grap_object)
						{
							if (object < 10)
								hook_away_length -= (hook_speed - golds[object].weight);
							else
								hook_away_length -= (hook_speed - stones[object - 10].weight);
							draw_worlds(score, target_score, time0, time1, pass_count);
							draw_hook_and_object(x0, y0, jiaodu, hook_away_length, object);
							draw_gold_and_stone(golds, gold_count, stones, stone_count);
							FlushBatchDraw();
							Sleep(100);
							time1 = time(NULL);
							if (time1 - time0 > time_limit)
							{
								time_flag = false;
								break;
							}
							cleardevice();
							if (hook_away_length <= 0)
							{
								hook_away_length = 0;
								is_away = false;
								is_hook_out = false;
								is_grap_object = false;
								if (object < 10)
									score += golds[object].value;
								else
									score += stones[object - 10].value;
								draw_worlds(score, target_score, time0, time1, pass_count);
								draw_gold_and_stone(golds, gold_count, stones, stone_count);
								draw_hook(x0, y0, jiaodu);
							}
						}
					}
				}
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			}
			FlushBatchDraw();
			Sleep(100);
			time1 = time(NULL);
			if (time1 - time0 > time_limit)
			{
				time_flag = false;
				break;
			}
			cleardevice();

			if (jiaodu <= -pi / 4)
				flag = true;
			if (jiaodu >= pi * 3 / 4)
				flag = false;
			if (flag)
				jiaodu += pi / 18;
			else
				jiaodu -= pi / 18;
		}
		if (score < target_score)
			break;
		else
		{
			target_score += 600;
			pass_count++;
		}
	}
	EndBatchDraw();
	getch();
	closegraph();
}