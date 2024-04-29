#include "chess.h"

#define width  560 //240
#define heigth 560 //320

#define p1 1		//玩家1
#define p2 2		//玩家2
#define Nochess 0	//空棋
#define N  15		//棋盘格数
#define Grid_wid 	(width/(N-1)) //网格宽度
#define Chess_R  Grid_wid/2  //棋子半径

#define player_player	3		//人人
#define player_AI		4		//人机

int player = p1;	//默认黑棋先手
int chess[N][N];	//棋盘地图
int chess_num;			//总棋子数
char param = 0;

void Oninit()
{
	setfillcolor(BLACK);
	player = p1;	//默认黑棋先手
	for (int i = 0; i < N; i++)//棋盘清零
	{
		for (int j = 0; j < N; j++)
		{
			chess[i][j] = Nochess;
		}
	}
	chess_num = 0;			//总棋子数清零
}

int judge(int x, int y)
{
	return chess[x][y] ? 0 : 1;
}

int judge_win(int x, int y)
{
	int i, j, k;
	const int step[4][2] = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, -1 } };
	for (i = 0; i < 4; ++i)
	{
		const int d[2] = { -1, 1 };
		int count = 1;
		for (j = 0; j < 2; ++j)
			for (k = 1; k <= 4; ++k) {
				int row = x + k * d[j] * step[i][0];
				int col = y + k * d[j] * step[i][1];
				if (row >= 1 &&  row <= N &&
					col >= 1 &&col <= N &&
					chess[x][y] == chess[row][col])
					count += 1;
				else
					break;
			}
		if (count >= 5)
			return 1;
	}
	if (chess_num == N * N)
		Msg_restart(2);

	return 0;
}

int Chess_piece(int x1, int y1)//落子
{
	if (x1 == -1 || y1 == -1)
	{
		return 0;
	}
	if (player == p1)
		setfillcolor(BLACK);
	else
		setfillcolor(WHITE);

	if (judge(x1, y1))
	{
		solidcircle(x1 * Grid_wid, y1 * Grid_wid, Chess_R);
		chess[x1][y1] = player;
		chess_num++;
		if (judge_win(x1, y1))
		{
			Msg_restart(1);
		}
		changeplayer();
		return 1;
	}
	return 0;
}

int mod_xy(int xy)
{
	int res = (int)((double)xy / Grid_wid + 0.5);
	if (res < N && res >= 0)
	{
		return res;
	}
	else
	{
		return -1;
	}
}

void changeplayer()//玩家交换
{
	player = p1 + p2 - player;
	if (player == p1)
		setfillcolor(BLACK);
	else
		setfillcolor(WHITE);
}

void draw_checkboard()
{
	setlinecolor(BLACK);
	int i;
	for (i = 0; i < N; i++)//画地图
	{
		line(1 + i * Grid_wid, 1, 1 + i * Grid_wid, Grid_wid * (N - 1));
		line(1, 1 + i * Grid_wid, Grid_wid * (N - 1), 1 + i * Grid_wid);
	}
}

int scorejudge(int row, int col)
{
	if ((row >= 0 &&row < N) && (col >= 0 &&col < N))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int chessscore(int x, int y, int worb)   //棋盘权值函数
{
	int sumscore = 0;
	char u, d, l, r, lu, ld, ru, rd;//u上 d下 l左 r右 lu左上 ld左下 ru右上 rd右下
	int row, col, count1, count2, count3, count4;   //1横 2竖 3斜上 4斜下
	count1 = count2 = count3 = count4 = 1;
	l = r = u = d = lu = ld = ru = rd = 0;
	chess[x][y] = worb;      //模拟下棋

	//横向
	row = x, col = y + 1;
	while (chess[row][col] == worb &&scorejudge(row, col))
	{
		count1++;
		col++;
	}
	while (chess[row][col] == 0 &&scorejudge(row, col))
	{
		r++;
		col++;
	}
	row = x, col = y - 1;
	while (chess[row][col] == worb &&scorejudge(row, col))
	{
		count1++;
		col--;
	}
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		l++;
		col--;
	}


	//竖向
	row = x + 1, col = y;
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count2++;
		row++;
	}
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		d++;
		row++;
	}
	row = x - 1, col = y;
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count2++;
		row--;
	}
	while (chess[row][col] == 0 &&  scorejudge(row, col))
	{
		u++;
		row--;
	}

	//斜上
	row = x - 1, col = y + 1;
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count3++;
		col++;
		row--;
	}
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		ru++;
		col++;
		row--;
	}
	row = x + 1, col = y - 1;
	while (chess[row][col] == worb &&  scorejudge(row, col))
	{
		count3++;
		col--;
		row++;
	}
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		ld++;
		col--;
		row++;
	}


	//斜下
	row = x + 1, col = y + 1;
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count4++;
		col++;
		row++;
	}
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		rd++;
		col++;
		row++;
	}
	row = x - 1, col = y - 1;
	while (chess[row][col] == worb && scorejudge(row, col))
	{
		count4++;
		col--;
		row--;
	}
	while (chess[row][col] == 0 && scorejudge(row, col))
	{
		lu++;
		col--;
		row--;
	}

	chess[x][y] = Nochess;

	if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)//成五
	{
		return sumscore = 5000000;
	}


	if ((count1 == 4 && count2 == 4 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 4 && count3 == 4 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 4 && count4 == 4 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 4 && count3 == 4 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 4 && count4 == 4 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 4 && count4 == 4 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
		//双活四
	{
		return sumscore = 4000000;
	}


	if ((count1 == 4 && l >= 1 && r >= 1) || (count2 == 4 && u >= 1 && d >= 1) ||
		(count3 == 4 && ru >= 1 && ld >= 1) || (count4 == 4 && lu >= 1 && rd >= 1))
		//活四
	{
		return sumscore = 800000;
	}

	if ((count1 == 4 && ((l == 0 && r >= 1) || (l >= 1 && r == 0)))
		|| (count2 == 4 && ((u == 0 && d >= 1) || (u >= 1 && d == 0)))
		|| (count3 == 4 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0)))
		|| (count4 == 4 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
		sumscore = sumscore + 35000; //成四
	}

	if ((count1 == 3 && count2 == 3 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 3 && count3 == 3 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 3 && count4 == 3 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 3 && count3 == 3 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 3 && count4 == 3 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 3 && count4 == 3 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
		//双活三
	{
		return sumscore + 400000;
	}


	if ((count1 == 3 && l >= 1 && r >= 1) || (count2 == 3 && u >= 1 && d >= 1) ||
		(count3 == 3 && ru >= 1 && ld >= 1) || (count4 == 3 && lu >= 1 && rd >= 1))
		//活三
	{
		sumscore = sumscore + 60000;
		return sumscore;
	}


	if ((count1 == 2 && count2 == 2 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
		(count1 == 2 && count3 == 2 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
		(count1 == 2 && count4 == 2 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
		(count2 == 2 && count3 == 2 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
		(count2 == 2 && count4 == 2 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
		(count3 == 2 && count4 == 2 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
		//双活二
	{
		sumscore = sumscore + 20000;
	}

	if ((count1 == 2 && l >= 1 && r >= 1) || (count2 == 2 && u >= 1 && d >= 1) ||
		(count3 == 2 && ru >= 1 && ld >= 1) || (count4 == 2 && lu >= 1 && rd >= 1))
		//单活二
	{
		sumscore = sumscore + 10000;
	}
	if ((count1 == 3 && ((l == 0 && r >= 1) || (l >= 1 && r == 0)))
		|| (count2 == 3 && ((u == 0 && d >= 1) || (u >= 1 && d == 0)))
		|| (count3 == 3 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0)))
		|| (count4 == 3 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
	{
		sumscore = sumscore + 5000; //成三
	}
	return sumscore;

}

void Msg_restart(int par)
{
	int res;
	if (par == 1)
	{
		if (player == p1)
		{
			res = MessageBoxA(0, "黑棋胜,是否重开？", "五子棋", MB_YESNO | MB_SYSTEMMODAL);
			if (res == IDYES)
				restart();
			else
				exitgame();
		}
		else
		{
			res = MessageBoxA(0, "白棋胜,是否重开？", "五子棋", MB_YESNO | MB_SYSTEMMODAL);
			if (res == IDYES)
				restart();
			else
				exitgame();
		}
	}
	else
	{
		res = MessageBoxA(0, "平局,是否重开？", "五子棋", MB_YESNO | MB_SYSTEMMODAL);
		if (res == IDYES)
			restart();
		else
			exitgame();
	}
}

void chesscomputer()
{
	int i, j, cscore, cscorel, pscore, pscorel, row1, col1, row2, col2;
	cscore = pscore = 0; row1 = row2 = col1 = col2 = -1;

	//寻找最优落子位置
	if (chess_num <= 1)
	{
		srand((unsigned)time(NULL));
		do
		{
			row1 = rand() % 2 + 6;
			col1 = rand() % 2 + 6;
		} while (!judge(row1, col1));
		Chess_piece(row1, col1);
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (judge(i, j))
				{
					cscorel = chessscore(i, j, p1);
					if (cscorel > cscore)
					{
						cscore = cscorel;
						row1 = i;
						col1 = j;
					}
					pscorel = chessscore(i, j, p2);
					if (pscorel > pscore)
					{
						pscore = pscorel;
						row2 = i;
						col2 = j;
					}
				}
			}
		}
		if (row1 == -1 && col1 == -1 && row2 == -1 && col2 == -1)//没找到最优解 平局
		{
			Msg_restart(2);
		}
		else
		{
			if (chess_num == 3)
			{
				Chess_piece(row2, col2);
			}
			else
			{
				if (cscore > pscore)
				{
					Chess_piece(row1, col1);
				}
				else
				{
					Chess_piece(row2, col2);
				}
			}
		}
	}
}

void Mouse()//鼠标移动
{
	if (param == player_player)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN://左键按下
				int x1 = mod_xy(msg.x);
				int y1 = mod_xy(msg.y);
				Chess_piece(x1, y1);
				break;
			}
		}
	}
	else
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN://左键按下
				int x1 = mod_xy(msg.x);
				int y1 = mod_xy(msg.y);
				if (Chess_piece(x1, y1))
				{
					chesscomputer();
				}
				break;
			}
		}
	}
}

void Start_Game()
{
	initgraph(width, heigth);//初始化窗口
	setbkcolor(RGB(249, 214, 91));//设置背景色
	cleardevice();
	draw_checkboard();
	Oninit();
	int res = MessageBoxA(0, "人机模式", "模式", MB_YESNO | MB_SYSTEMMODAL);
	if (res == IDYES)
	{
		param = player_AI;
	}
	else
	{
		param = player_player;
	}
}

void restart()
{
	Oninit();
	cleardevice();
	draw_checkboard();
	while (1)
	{
		//chesscomputer();
		Mouse();
	}
}

void exitgame()
{
	closegraph();
	exit(0);
}

void main()
{
	Start_Game();
	while (1)
	{
		Mouse();
	}
}

