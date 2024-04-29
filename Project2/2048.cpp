#include <iostream>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include<cstdlib>
//#include <windows.h>
using namespace std;
int map[4][4];
int num;
int score = 0;
int if_neednew = 0;
IMAGE img[12];
int imgnum[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int is_over = 0;
void loadresourse()
{
    ;
}
void left()
{
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (k = 0, j = 1; j < 4; j++)
        {
            if (map[i][j] > 0)
            {
                if (map[i][k] == map[i][j])
                {
                    map[i][k] = 2 * map[i][k];
                    map[i][j] = 0;
                    if_neednew = 1;
                }
                else if (map[i][k] == 0)
                {
                    map[i][k] = map[i][j];
                    map[i][j] = 0;
                    if_neednew = 1;
                }
                else
                {
                    map[i][++k] = map[i][j];
                }
                if (k != j)
                {
                    map[i][j] = 0;
                    if_neednew = 1;
                }
            }
        }

    }
}
void right()
{
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (k = 3, j = 2; j >= 0; j--)
        {
            if (map[i][j] > 0)
            {
                if (map[i][k] == map[i][j])
                {
                    map[i][k] = 2 * map[i][k];
                    map[i][j] = 0;
                    if_neednew = 1;
                }
                else if (map[i][k] == 0)
                {
                    map[i][k] = map[i][j];
                    map[i][j] = 0;
                    if_neednew = 1;
                }
                else
                {
                    map[i][--k] = map[i][j];
                }
                if (k != j)
                {
                    map[i][j] = 0;
                    if_neednew = 1;
                }
            }
        }

    }
}
void up()
{
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (k = 0, j = 1; j < 4; j++)
        {
            if (map[j][i] > 0)
            {
                if (map[k][i] == map[j][i])
                {
                    map[k][i] = 2 * map[k][i];
                    map[j][i] = 0;
                    if_neednew = 1;
                }
                else if (map[k][i] == 0)
                {
                    map[k][i] = map[j][i];
                    map[j][i] = 0;
                    if_neednew = 1;
                }
                else
                {
                    map[++k][i] = map[j][i];
                }
                if (k != j)
                {
                    map[j][i] = 0;
                    if_neednew = 1;
                }
            }
        }

    }
}
void down()
{
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (k = 3, j = 2; j >= 0; j--)
        {
            if (map[j][i] > 0)
            {
                if (map[k][i] == map[j][i])
                {
                    map[k][i] = 2 * map[k][i];
                    map[j][i] = 0;
                    if_neednew = 1;
                }
                else if (map[k][i] == 0)
                {
                    map[k][i] = map[j][i];
                    map[j][i] = 0;
                    if_neednew = 1;
                }
                else
                {
                    map[--k][i] = map[j][i];
                }
                if (k != j)
                {
                    map[j][i] = 0;
                    if_neednew = 1;
                }
            }
        }

    }
}
int get_num()
{
    int null = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (map[i][j] == 0)
                null++;
    return null;
}
int add_srand_num()
{
    int null = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (map[i][j] == 0)
                null++;
    int fla = 0;
    int n = rand() % null + 1;
    srand((unsigned int)time(0));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (map[i][j] == 0)
            {
                n--;
                if (n == 0)
                {
                    int k = (rand() % 5 == 0 ? 4 : 2);

                    map[i][j] = k;
                    return 0;

                }
            }

}
void set_game()
{
    int n;
    n = rand() % 16;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            map[i][j] = (n-- == 0 ? 2 : 0);
        }
}
int check()
{

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (map[i][j] == map[i][j + 1] || map[j + 1][i] == map[j][i])
                return 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (map[i][j] == 0)
                return 1;


    return 0;



}
//void clear()
//{
//    COORD pos = { 0, 0 };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//    CONSOLE_CURSOR_INFO info = { 1, 0 };
//    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &amp;info);
//}
int needleft()
{
    if (num == 0)
        return 1;
    for (int i = 0; i < 4; i++)
        if (map[i][0] == 0)
            return 1;
    for (int i = 0; i < 4; i++)
        for (int j = 3; j >= 0; j--)
        {
            if (!map[i][j])
            {
                int k = j;
                for (k = j; k >= 0; k--)
                {

                    if (map[i][k] == 0)
                        return 1;

                }
            }
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (map[i][j] == map[i][j + 1])
                return 1;
    return 0;
}
int needright()
{
    if (get_num() == 0)
        return 1;
    for (int i = 0; i < 4; i++)
        if (map[i][3] == 0)
            return 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (!map[i][j])
            {
                int k = j;
                for (k = j; k < 4; k++)
                {

                    if (map[i][k] == 0)
                        return 1;

                }
            }
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (map[i][j] == map[i][j + 1])
                return 1;
    return 0;
}
int needup()
{
    if (get_num() == 0)
        return 1;
    for (int i = 0; i < 4; i++)
        if (map[0][i] == 0)
            return 1;
    for (int i = 0; i < 4; i++)
        for (int j = 3; j >= 0; j--)
        {
            if (!map[j][i])
            {
                int k = j;
                for (k = j; k >= 0; k--)
                {

                    if (map[k][i] == 0)
                        return 1;

                }
            }

        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (map[j + 1][i] == map[j][i])
                return 1;
    return 0;
}
int needdown()
{
    if (get_num() == 0)
        return 1;
    for (int i = 0; i < 4; i++)
        if (map[3][i] == 0)
            return 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (!map[j][i])
            {
                int k = j;
                for (k = j; k < 4; k++)
                {

                    if (map[k][i] == 0)
                        return 1;

                }
            }

        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (map[j + 1][i] == map[j][i])
                return 1;
    return 0;
}
int main()
{
    srand((unsigned int)time(0));
    set_game();
    initgraph(550, 700);
    IMAGE background;
    IMAGE shoukuan;
    setbkcolor(RGB(164, 253, 187));
    settextcolor(RGB(197, 135, 33));
    settextstyle(35, 0, _T("楷体"));

    cleardevice();
    outtextxy(10, 300, _T("按任意键后按上下左右键开始游戏"));
    outtextxy(20, 600, _T("您的鼓励是我最大的动力【doge】"));
    outtextxy(0, 0, _T("抵制不良游戏"));
    outtextxy(0, 35, _T("拒绝盗版游戏"));
    outtextxy(0, 70, _T("注意自我保护"));
    outtextxy(320, 0, _T("谨防受骗上当"));
    outtextxy(320, 35, _T("适度游戏益脑"));
    outtextxy(320, 70, _T("沉迷游戏伤身"));
    //loadimage(&background, _T("D:/vs2019/Project/Project2/background.jpg"));
    //loadimage(&shoukuan, _T("D:/vs2019/Project/Project2/shoukuan.jpg"));
    //putimage(220, 0, &background);
    //putimage(150, 400, &shoukuan);
    _getch();
    clearrectangle(10, 300, 700, 700);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 20);
    setlinecolor(RGB(154, 96, 65));
    /* line(60, 100, 60, 540);
     line(50, 530, 500, 530);
     line(60, 530, 500, 530);
     line(60, 100, 60, 530);*/
    loadimage(&img[0], _T("D:/vs2019/Project/Project2/0.jpg"));
    loadimage(&img[1], _T("D:/vs2019/Project/Project2/2.jpg"));
    loadimage(&img[2], _T("D:/vs2019/Project/Project2/4.jpg"));
    loadimage(&img[3], _T("D:/vs2019/Project/Project2/8.jpg"));
    loadimage(&img[4], _T("D:/vs2019/Project/Project2/16.jpg"));
    loadimage(&img[5], _T("D:/vs2019/Project/Project2/32.jpg"));
    loadimage(&img[6], _T("D:/vs2019/Project/Project2/64.jpg"));
    loadimage(&img[7], _T("D:/vs2019/Project/Project2/128.jpg"));
    loadimage(&img[8], _T("D:/vs2019/Project/Project2/256.jpg"));
    loadimage(&img[9], _T("D:/vs2019/Project/Project2/512.jpg"));
    loadimage(&img[10], _T("D:/vs2019/Project/Project2/1024.jpg"));
    loadimage(&img[11], _T("D:/vs2019/Project/Project2/2048.jpg"));

    int nn = check();
    while (nn != 0)
    {
        score = 0;
        num = get_num();

        if_neednew = 0;

        int cmd = _getch();
        switch (cmd)
        {
        case 'a':
        case 75:
            if (needup())
                up();
            break;
        case 's':
        case 80:
            if (needright())
                right();
            break;
        case 'w':
        case 72:
            if (needleft())
                left();
            break;
        case 'd':
        case 77:
            if (needdown())
                down();
            break;
        default:continue;
        }
        /*int k=0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (map[i][j] == 0)
                    k++;*/
        if (if_neednew)
            add_srand_num();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                int x = 105 * i + 60;
                int y = 108 * j + 150;
                for (int p = 0; p < 12; p++)
                    if (imgnum[p] == map[i][j])
                        putimage(x, y, &img[p]);
            }

        nn = check();
        settextcolor(RGB(252, 48, 12));
        settextstyle(60, 0, _T("楷体"));
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                score += map[i][j];
        TCHAR s[5];
        _stprintf_s(s, _T("%d"), score);
        outtextxy(50, 600, _T("当前得分："));
        outtextxy(300, 600, s);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (map[i][j] == 2048)
                {
                    outtextxy(200, 350, _T("你赢了"));
                    break;
                }
    }

    outtextxy(200, 350, _T("你输了"));

    _getch();
    closegraph();
    return 0;

}


