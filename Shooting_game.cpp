#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

//미사일 구조체
struct BULLET {
	int x;
	int y;
	bool fire;
};

//배열로 배경 좌표를 만든다.
char bg[25][80];

//플레이어 좌표
int playerX;
int playerY;

//적 좌표
int enemyX;
int enemyY;

//미사일 갯수
BULLET playerBullet[20];

//함수 설계
void ClearScreen(); //화면을 지운다
void GameMain();	//게임전체를 관리하는 함수
void PrintScreen();	//화면을 그려주는 함수
void KeyControl();	//키관련 함수
void BulletDraw();	//미사일을 그려주는 함수
void PlayerDraw();	//플레이어 그리는 함수
void EnemyDraw();	//적그리는 함수
void EnemyMove();	//적움직이는 함수
void ClashEnemyAndBullet();	//충돌처리 함수

void main() {


}

void ClearScreen()
{
}

void GameMain()
{
}

void PrintScreen()
{
}

void KeyControl()
{
}

void BulletDraw()
{
}

void PlayerDraw()
{
}

void EnemyDraw()
{
}

void EnemyMove()
{
}

void ClashEnemyAndBullet()
{
}
