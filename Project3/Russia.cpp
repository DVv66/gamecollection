#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <windows.h>

struct Square
{
	int dir[4][4][2];
};

enum Cmd
{
	Cmd_rotate,  // ������ת
	Cmd_left,    // ��������
	Cmd_right,   // ��������
	Cmd_down     // ��������
};

Square squares[7] = {
	{ 0, -2, 0, -1, 0, 0, 1, 0, 0, -1, 1, -1, 2, -1, 0, 0, 0, -2, 1, -2, 1, -1, 1, 0, 0, 0, 1, 0, 2, 0, 2, -1 },       //  L ��
	{ 0, 0, 1, 0, 1, -1, 1, -2, 0, -1, 0, 0, 1, 0, 2, 0, 0, -2, 0, -1, 0, 0, 1, -2, 0, -1, 1, -1, 2, -1, 2, 0 },       //  L �ͣ�����
	{ 0, -1, 0, 0, 1, -1, 1, 0, 0, -1, 0, 0, 1, -1, 1, 0, 0, -1, 0, 0, 1, -1, 1, 0, 0, -1, 0, 0, 1, -1, 1, 0 },        // �� ��
	{ 0, 0, 1, -1, 1, 0, 2, 0, 1, -2, 1, -1, 1, 0, 2, -1, 0, -1, 1, -1, 1, 0, 2, -1, 0, -1, 1, -2, 1, -1, 1, 0 },      // ɽ ��
	{ 0, -3, 0, -2, 0, -1, 0, 0, 0, -3, 1, -3, 2, -3, 3, -3, 0, -3, 0, -2, 0, -1, 0, 0, 0, -3, 1, -3, 2, -3, 3, -3 },  //  | ��
	{ 0, -1, 1, -1, 1, 0, 2, 0, 0, -1, 0, 0, 1, -2, 1, -1, 0, -1, 1, -1, 1, 0, 2, 0, 0, -1, 0, 0, 1, -2, 1, -1 },      //  Z ��
	{ 0, 0, 1, -1, 1, 0, 2, -1, 1, -2, 1, -1, 2, -1, 2, 0, 0, 0, 1, -1, 1, 0, 2, -1, 1, -2, 1, -1, 2, -1, 2, 0 }       //  Z �ͣ�����
};

const double pi = acos(-1);

COLORREF tmp_line_color;
LINESTYLE tmp_line_style;
COLORREF tmp_text_color;
LOGFONT tmp_text_style;
COLORREF tmp_fill_color;

COLORREF colors[7] = { RGB(255, 0, 0), RGB(255, 165, 0), RGB(255, 255, 0), RGB(0, 128, 0), RGB(0, 255, 255), RGB(0, 0, 255), RGB(128, 0, 128) };
int mp[10][15];
int mp_tmp[10][15];
COLORREF mp_c[10][15];
COLORREF mp_c_tmp[10][15];
wchar_t score_tips[30];
wchar_t over_tips[50];

DWORD time_now;
int flag_next;
int flag_over;
int now_c_idx;
int now_s_idx;
int now_d_idx;
int next_c_idx;
int next_s_idx;
int next_d_idx;
int now_mp_x;
int now_mp_y;
int score;

void initEnvironment();
void initDatasPerRound();
void initDatasPerSquare();
void drawGameBG();
void drawSide();
//void drawLines();
void drawItem(int x, int y, COLORREF c);
void drawSquareNow();
void drawSquareNext();
void drawMap();
Cmd getCmd();
bool checkPut(int mp_x, int mp_y, int dir_idx);
void execClear();
bool checkOver();
void execCmd(Cmd cmd);
void moveRotate();
void moveLeft();
void moveRight();
void moveDown();
void recordSquareNow();

int main()
{
	initEnvironment();
	// ��ʼ��Ϸ
	while (true)
	{
		initDatasPerRound();
		while (!flag_over)
		{
			initDatasPerSquare();
			while (!flag_next)
			{
				BeginBatchDraw();
				drawGameBG();
				drawSide();
				//drawLines();
				drawMap();
				drawSquareNow();
				EndBatchDraw();
				Cmd cmd = getCmd();
				execCmd(cmd);
			}
		}
		// һ�ֽ������ͳ��
		swprintf(over_tips, 39, L"��Ϸ����\n������յ÷֣�%d\n�Ƿ�����һ�֣�", score * 100);
		if (MessageBox(GetHWnd(), over_tips, L"����һ�֣�", MB_ICONQUESTION | MB_YESNO) == IDNO)
			break;
	}

	return 0;
}

void initEnvironment()
{
	// ��������
	initgraph(600, 540);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"����˹����");
	SetWindowPos(hwnd, HWND_TOP, 700, 20, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);

	// ��ͼģʽ����
	setbkmode(TRANSPARENT);

	// ���������
	srand(time(NULL));
}

void initDatasPerRound()
{
	memset(mp, 0, sizeof(mp));
	memset(mp, 0, sizeof(mp_c));
	time_now = GetTickCount();
	next_c_idx = rand() % 7;
	next_s_idx = rand() % 7;
	next_d_idx = rand() % 4;
	flag_over = 0;
	score = 0;
}

void initDatasPerSquare()
{
	now_mp_x = 5;
	now_mp_y = -1;
	flag_next = 0;
	now_c_idx = next_c_idx;
	now_s_idx = next_s_idx;
	now_d_idx = next_d_idx;
	next_c_idx = rand() % 7;
	next_s_idx = rand() % 7;
	next_d_idx = rand() % 4;
}

void drawGameBG()
{
	// ����������Ϸ���򡢼Ʒ�����
	// ����ߴ硪��36 * 36����λ�����أ�
	// ��Ϸ�ߴ硪��10 * 15����λ�����飩
	// ��һ��������ʾ���򡪡�4 * 4����λ�����飩
	COLORREF tmp = getlinecolor();

	for (int i = 0; i < 541; ++i)
	{
		setlinecolor(RGB(135, 206, 250 - i / 5));
		line(0, 540 - i, 360, 540 - i);
	}

	setlinecolor(tmp);
}

void drawSide()
{
	tmp_line_color = getlinecolor();
	getlinestyle(&tmp_line_style);
	tmp_text_color = getlinecolor();
	gettextstyle(&tmp_text_style);

	for (int i = 0; i < 541; ++i)
	{
		setlinecolor(RGB(224, 178, 220 - i / 15));
		line(361, i, 600, i);
	}
	settextcolor(RGB(65, 105, 225));
	settextstyle(30, 0, L"���Ŀ���");
	outtextxy(360 + 48, 300, L"���ƣ���");
	outtextxy(360 + 48, 330, L"���ƣ���");
	outtextxy(360 + 48, 360, L"���Σ���");
	outtextxy(360 + 48, 390, L"���䣺��");

	setlinecolor(WHITE);
	rectangle(360 + 48, 36, 600 - 48, 36 + 144);
	drawSquareNext();
	setlinecolor(0x7FFFAA);
	rectangle(360 + 48, 36, 600 - 48, 36 + 144);

	swprintf(score_tips, 29, L"�÷֣�%d", score * 100);
	outtextxy(360 + 48, 200, score_tips);

	setlinecolor(tmp_line_color);
	setlinestyle(&tmp_line_style);
	settextcolor(tmp_text_color);
	settextstyle(&tmp_text_style);
}

//void drawLines()
//{
//	for (int i = 0; i <= 10; ++i)
//		line(36 * i, 0, 36 * i, 540);
//	for (int j = 0; j <= 15; ++j)
//		line(0, j * 36, 360, j * 36);
//
//	for (int i = 1; i < 4; ++i)
//		line(360 + 48 + i * 36, 36, 360 + 48 + i * 36, 36 + 144);
//	for (int j = 1; j < 4; ++j)
//		line(360 + 48, 36 + j * 36, 600 - 48, 36 + j * 36);
//}

void drawItem(int x, int y, COLORREF c)
{
	// �������
	// ʵ�ʳߴ磺32 * 32����λ�����أ�
	// �߿���ɫ����ɫ
	// Բ�ǰ뾶��4����λ�����أ�
	// �ڲ���ࣺ2����λ�����أ�
	tmp_fill_color = getfillcolor();

	const int r = 6;
	const int p = 2;

	int up_l_x = x + p + r;
	int up_r_x = x + 36 - p - r;
	int up___y = y + p;

	int down_l_x = x + p + r;
	int down_r_x = x + 36 - p - r;
	int down___y = y + 36 - p;

	int left_u_y = y + p + r;
	int left_d_y = y + 36 - p - r;
	int left___x = x + p;

	int right_u_y = y + p + r;
	int right_d_y = y + 36 - p - r;
	int right___x = x + 36 - p;

	line(up_l_x, up___y, up_r_x, up___y);
	line(down_l_x, down___y, down_r_x, down___y);
	line(left___x, left_u_y, left___x, left_d_y);
	line(right___x, right_u_y, right___x, right_d_y);
	arc(x + p, y + p, x + p + 2 * r, y + p + 2 * r, pi / 2, pi);
	arc(x + 36 - p, y + p, x + 36 - p - 2 * r, y + p + 2 * r, 0, pi / 2);
	arc(x + p, y + 36 - p, x + p + 2 * r, y + 36 - p - 2 * r, -pi, -pi / 2);
	arc(x + 36 - p, y + 36 - p, x + 36 - p - 2 * r, y + 36 - p - 2 * r, -pi / 2, 0);

	setfillcolor(c);
	floodfill(x + p + r + 1, y + p + r + 1, WHITE);

	setfillcolor(tmp_fill_color);
}

void drawSquareNow()
{
	drawItem((now_mp_x + squares[now_s_idx].dir[now_d_idx][0][0]) * 36, (now_mp_y + squares[now_s_idx].dir[now_d_idx][0][1]) * 36, colors[now_c_idx]);
	drawItem((now_mp_x + squares[now_s_idx].dir[now_d_idx][1][0]) * 36, (now_mp_y + squares[now_s_idx].dir[now_d_idx][1][1]) * 36, colors[now_c_idx]);
	drawItem((now_mp_x + squares[now_s_idx].dir[now_d_idx][2][0]) * 36, (now_mp_y + squares[now_s_idx].dir[now_d_idx][2][1]) * 36, colors[now_c_idx]);
	drawItem((now_mp_x + squares[now_s_idx].dir[now_d_idx][3][0]) * 36, (now_mp_y + squares[now_s_idx].dir[now_d_idx][3][1]) * 36, colors[now_c_idx]);
}

void drawSquareNext()
{
	int tmp_x = 360 + 48;
	int tmp_y = 36 + 108;
	COLORREF c = colors[next_c_idx];
	drawItem(tmp_x + squares[next_s_idx].dir[next_d_idx][0][0] * 36, tmp_y + squares[next_s_idx].dir[next_d_idx][0][1] * 36, c);
	drawItem(tmp_x + squares[next_s_idx].dir[next_d_idx][1][0] * 36, tmp_y + squares[next_s_idx].dir[next_d_idx][1][1] * 36, c);
	drawItem(tmp_x + squares[next_s_idx].dir[next_d_idx][2][0] * 36, tmp_y + squares[next_s_idx].dir[next_d_idx][2][1] * 36, c);
	drawItem(tmp_x + squares[next_s_idx].dir[next_d_idx][3][0] * 36, tmp_y + squares[next_s_idx].dir[next_d_idx][3][1] * 36, c);
}

void drawMap()
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 15; ++j)
			if (mp[i][j])
				drawItem(i * 36, j * 36, mp_c[i][j]);
}

Cmd getCmd()
{
	while (true)
	{
		// ָ�ʱ
		DWORD time_tmp = GetTickCount();
		if (time_tmp - time_now >= 1000)
		{
			time_now = time_tmp;
			return Cmd_down;
		}

		// ����ָ��
		if (_kbhit())
		{
			switch (_getch())
			{
			case 72:
				return Cmd_rotate;
			case 75:
				return Cmd_left;
			case 77:
				return Cmd_right;
			case 80:
				return Cmd_down;
			}
		}

		// ����CPUռ��
		Sleep(20);
	}
}

void execCmd(Cmd cmd)
{
	switch (cmd)
	{
	case Cmd_down:
		moveDown();
		break;
	case Cmd_left:
		moveLeft();
		break;
	case Cmd_right:
		moveRight();
		break;
	case Cmd_rotate:
		moveRotate();
		break;
	}
}

bool checkPut(int mp_x, int mp_y, int dir_idx)
{
	int sq_x[4];
	int sq_y[4];
	for (int i = 0; i < 4; ++i)
	{
		sq_x[i] = mp_x + squares[now_s_idx].dir[dir_idx][i][0];
		sq_y[i] = mp_y + squares[now_s_idx].dir[dir_idx][i][1];
	}

	// ������Խ�硢�·�Խ�硢�ظ�ռ��
	for (int i = 0; i < 4; ++i)
	{
		if (sq_x[i] < 0 || sq_x[i] > 9 || sq_y[i] > 14)
			return false;
		if (sq_y[i] < 0) // �������Ϸ���
			continue;
		if (mp[sq_x[i]][sq_y[i]])
			return false;
	}
	return true;
}

void execClear()
{
	memset(mp_tmp, 0, sizeof(mp_tmp));
	memset(mp_c_tmp, 0, sizeof(mp_c_tmp));
	int cnt_j = 14;
	for (int j = 14; j >= 0; --j)
	{
		int cnt = 0;
		for (int i = 0; i < 10; ++i)
			if (mp[i][j])
				++cnt;
		if (cnt != 10)
		{
			for (int i = 0; i < 10; ++i)
			{
				mp_tmp[i][cnt_j] = mp[i][j];
				mp_c_tmp[i][cnt_j] = mp_c[i][j];
			}
			--cnt_j;
		}
		else
			++score;
	}
	for (int j = 0; j < 15; ++j)
		for (int i = 0; i < 10; ++i)
		{
			mp[i][j] = mp_tmp[i][j];
			mp_c[i][j] = mp_c_tmp[i][j];
		}
}

bool checkOver()
{
	for (int i = 0; i < 10; ++i)
		if (mp[i][0])
			return true;
	return false;
}

void moveRotate()
{
	// ����ʣ��������״��������ת��������ת״̬
	for (int i = 1; i <= 3; ++i)
		if (checkPut(now_mp_x, now_mp_y, (now_d_idx + i) % 4))
		{
			now_d_idx = (now_d_idx + i) % 4;
			break;
		}
}

void moveLeft()
{
	// �����ܷ�����
	if (checkPut(now_mp_x - 1, now_mp_y, now_d_idx))
		--now_mp_x;
}

void moveRight()
{
	// �����ܷ�����
	if (checkPut(now_mp_x + 1, now_mp_y, now_d_idx))
		++now_mp_x;
}

void moveDown()
{
	// �����ܷ�����
	if (checkPut(now_mp_x, now_mp_y + 1, now_d_idx))
	{
		++now_mp_y;
		return;
	}
	// ����������˵����鷽�顰�������ˣ�ִ�����²���
	// 1����ʾ���Կ�ʼ��һ������
	// 2���������¼��map��ͼ��
	// 3���ж��Ƿ��������
	// 4���ж����к���Ϸ�Ƿ����
	flag_next = 1;
	recordSquareNow();
	execClear();
	if (checkOver())
		flag_over = 1;
}

void recordSquareNow()
{
	int sq_x[4];
	int sq_y[4];
	for (int i = 0; i < 4; ++i)
	{
		sq_x[i] = now_mp_x + squares[now_s_idx].dir[now_d_idx][i][0];
		sq_y[i] = now_mp_y + squares[now_s_idx].dir[now_d_idx][i][1];
	}
	for (int i = 0; i < 4; ++i)
		if (sq_y[i] >= 0)
		{
			mp[sq_x[i]][sq_y[i]] = 1;
			mp_c[sq_x[i]][sq_y[i]] = colors[now_c_idx];
		}
}
