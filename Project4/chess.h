#pragma once
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>

int judge(int x, int y);
int judge_win(int x, int y);
int Chess_piece(int x, int y);
int mod_xy(int xy);
void changeplayer();
void draw_checkboard();
int chessscore(int x, int y, int worb);
void chesscomputer();
void Mouse();
void Start_Game();
void restart();
void exitgame();
void Msg_restart(int par);
