#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define XMAX 100
#define YMAX 25

//�̻��� ����ü
struct BULLET {
	int x;
	int y;
	bool fire;
};

//�迭�� ��� ��ǥ�� �����.
char bg[YMAX][XMAX];

//�÷��̾� ��ǥ
int playerX;
int playerY;

//�� ��ǥ
int enemyX;
int enemyY;

//�̻��� ����
BULLET playerBullet[21];

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
	//�����Լ� �غ�
	srand((unsigned)time(NULL));
	//�÷��̾� ��ǥ ��ġ
	playerX = 1;
	playerY = YMAX/2;

	//�� ��ǥ ��ġ
	enemyX = 77;
	enemyY = 12;

	//�÷��̾� �̻��� �ʱ�ȭ
	for (int i = 0; i < 20; i++) {
		playerBullet[i].x = 0;
		playerBullet[i].y = 0;
		playerBullet[i].fire = false;
	}

	//�ʴ��� �ð��� �޾ƿ�
	int dwTime = GetTickCount64();

	//���ӽ��� ���ѷ���
	while (true) {
		//0.015�� ������
		if (dwTime + 15 < GetTickCount64()) {
			dwTime = GetTickCount64();
			//����� �Լ�
			ClearScreen();
			//�÷��̾ ���� �����̴� �Լ�
			GameMain();
			//�׷��ִ� �Լ�
			PrintScreen();
		}
	}
}

void ClearScreen()
{
	//�ܼ�â�� ����
	system("cls");
	//�迭�� �������� �־ ����
	for (int y = 0; y < YMAX; y++) {
		for (int x = 0; x < XMAX; x++) {
			bg[y][x] = ' ';
		}
	}
}

void GameMain()
{
	//Ű�� �Է��ϴ� �κ�
	KeyControl();
	//�̻����� �׷��ִ� �κ�
	BulletDraw();
	//�÷��̾ �׷��ִ� �κ�
	PlayerDraw();
	//���� ������
	EnemyMove();
	//���� �׷��ִ� �κ�
	EnemyDraw();
	//�̻��ϰ� �� �浹
	ClashEnemyAndBullet();

}

void PrintScreen()
{
	bg[YMAX-1][XMAX-1] = '\0';
	printf("%s", bg);
}

void KeyControl()
{
	char pressKey;

	//Ű�� �ԷµǸ� �����
	if (_kbhit()) {
		pressKey = _getch();	//Ű�� �ԷµǾ� ������ ����
		switch (pressKey) {
		case 72:
			//���� ����Ű
			if (playerY == 1)
				break;
			playerY--;
			break;
			/*playerY--;
			if (playerY < 1)
				playerY = 1;
			break;*/
		case 75:
			//���� ����Ű
			if (playerX == 1)
				break;
			playerX--;
			break;
		case 77:
			//������ ����Ű
			if (playerX == XMAX-2)
				break;
			playerX++;
			break;
		case 80:
			//�Ʒ��� ����Ű
			if (playerY == YMAX-2)
				break;
			playerY++;
			break;
		case 32:
			//�����̽���
			for (int i = 0; i < 20; i++) {
				//�̻����� �غ�Ǿ��ִ� ������ ��쿡�� �߻簡��
				if (playerBullet[i].fire == false) {
					playerBullet[i].fire = true;
					//�÷��̾� �տ��� �̻����� ���
					playerBullet[i].x = playerX + 5;
					playerBullet[i].y = playerY;
					//�ѹ߸� �߻��ϱ�
					break;
				}
			}
			break;
		}
	}
}

void BulletDraw()
{
	//�̻��� ��ü 20���߿�
	for (int i = 0; i < 20; i++) {
		//�÷��̾� �̻��� ���ư��� �ִ� ���� true
		if (playerBullet[i].fire == true) {
			//�̻����� �׸���.
			bg[playerBullet[i].y][playerBullet[i].x - 1] = '-';
			bg[playerBullet[i].y][playerBullet[i].x - 0] = '>';
			//�̻��� ������ +1
			playerBullet[i].x++;
			if (playerBullet[i].x > XMAX-1) {
				//�̻��� �غ���·� ��ȯ
				playerBullet[i].fire = false;
			}
		}
	}
}

void PlayerDraw()
{
	//�÷��̾� �׸���
	bg[playerY - 1][playerX - 1] = '-';
	bg[playerY - 1][playerX + 0] = '>';
	bg[playerY + 0][playerX - 1] = '>';
	bg[playerY + 0][playerX + 0] = '=';
	bg[playerY + 0][playerX + 1] = '>';
	bg[playerY + 1][playerX - 1] = '-';
	bg[playerY + 1][playerX + 0] = '>';
}

void EnemyDraw()
{
	//�� �׸���
	bg[enemyY][enemyX - 2] = '<';
	bg[enemyY][enemyX - 1] = '-';
	bg[enemyY][enemyX - 0] = 'O';
	bg[enemyY][enemyX + 1] = '-';
	bg[enemyY][enemyX + 2] = '>';
}

void EnemyMove()
{
	//���� �������� ���� �Ѵ�.
	enemyX--;

	//���� �������� �� �ð��
	if (enemyX < 2) {
		//���� �����ϰ� y�� ��ǥ�� �ٲ��ش�
		enemyX = 77;
		enemyY = (rand() % 20) + 2;
	}
}

void ClashEnemyAndBullet()
{
	//�̻����� 20�� ��ü �Ǻ�
	for (int i = 0; i < 20; i++) {
		if (playerBullet[i].fire == true) {
			//���� �̻����� y���� ����
			if (playerBullet[i].y == enemyY) {
				//�÷��̾� �̻��� x���� ������ �Ǻ�
				//x���� ���� ũ�⸸ŭ x-1 x+1���� ���� ��ǥ�� �浹�ǰ� �Ǻ�
				if (playerBullet[i].x >= (enemyX - 1) && playerBullet[i].x <= (enemyX + 1)) {
					//�浹�Ǹ� ��y���� �ٲ��ֱ�
					enemyX = 77;
					enemyY = (rand() % 20) + 2;
					playerBullet[i].fire = false;
				}
			}
		}
	}
}
