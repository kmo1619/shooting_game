#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

//�̻��� ����ü
struct BULLET {
	int x;
	int y;
	bool fire;
};

//�迭�� ��� ��ǥ�� �����.
char bg[25][80];

//�÷��̾� ��ǥ
int playerX;
int playerY;

//�� ��ǥ
int enemyX;
int enemyY;

//�̻��� ����
BULLET playerBullet[20];

//�Լ� ����
void ClearScreen(); //ȭ���� �����
void GameMain();	//������ü�� �����ϴ� �Լ�
void PrintScreen();	//ȭ���� �׷��ִ� �Լ�
void KeyControl();	//Ű���� �Լ�
void BulletDraw();	//�̻����� �׷��ִ� �Լ�
void PlayerDraw();	//�÷��̾� �׸��� �Լ�
void EnemyDraw();	//���׸��� �Լ�
void EnemyMove();	//�������̴� �Լ�
void ClashEnemyAndBullet();	//�浹ó�� �Լ�

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
