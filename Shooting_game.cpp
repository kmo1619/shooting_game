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

//������ ����ü
struct ITEM {
	int x;
	int y;
	int type;
	bool exist;
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

//������ ����
ITEM items[3];

//�Լ� ����
void ClearScreen(); //ȭ���� �����
void GameMain(int *lif, int *score, int level, int *power);	//������ü�� �����ϴ� �Լ�
void PrintScreen(int lvl, int lif, int score);	//ȭ���� �׷��ִ� �Լ�
void KeyControl();	//Ű���� �Լ�
void BulletDraw(int *power);	//�̻����� �׷��ִ� �Լ�
void PlayerDraw();	//�÷��̾� �׸��� �Լ�
void EnemyDraw();	//���׸��� �Լ�
void EnemyMove(int *life);	//�������̴� �Լ�
void ClashEnemyAndBullet(int *score, int level, int *power);	//�浹ó�� �Լ�
void ItemCreate();	//������ ���� �Լ�
void ItemDraw();	//������ �׸��� �Լ�
void ClashItemAndPlayer(int *life, int *power);	//�浹ó�� �Լ�

void main() {
	int speed = 30;	//���� �ӵ� 
	int level = 1;	//���� ���̵�
	int life = 100;	//���� ���
	int score = 0;	//���ھ�
	int power = 1;
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

	//������ �ʱ�ȭ
	for (int i = 0; i < 3; i++) {
		items[i].x = 0;
		items[i].y = 0;
		items[i].type = 0;
		items[i].exist = 0;
	}

	//�ʴ��� �ð��� �޾ƿ�
	int dwTime = GetTickCount64();
	int stTime = GetTickCount64();
	//���ӽ��� ���ѷ���
	while (true) {
		if (dwTime + speed < GetTickCount64()) {
			dwTime = GetTickCount64();
			//����� �Լ�
			ClearScreen();
			//�÷��̾ ���� �����̴� �Լ�
			GameMain(&life, &score, level, &power);
			//�׷��ִ� �Լ�
			PrintScreen(level, life, score);
		}
		if (stTime + 1000 < GetTickCount64()) {
			speed = speed - 5;
			level++;
			stTime = GetTickCount64();
			//������ ����
			ItemCreate();
			//����� �Լ�
			ClearScreen();
			//�÷��̾ ���� �����̴� �Լ�
			GameMain(&life, &score, level, &power);
			//�׷��ִ� �Լ�
			PrintScreen(level, life, score);
		}
		if (life == 0) {
			//�ܼ�â�� ����
			system("cls");
			//�迭�� �������� �־ ����
			printf("gameover");
			break;
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

void GameMain(int *life, int *score, int level, int *power)
{
	//Ű�� �Է��ϴ� �κ�
	KeyControl();
	//�̻����� �׷��ִ� �κ�
	BulletDraw(power);
	//�÷��̾ �׷��ִ� �κ�
	PlayerDraw();
	//���� ������
	EnemyMove(life);
	//���� �׷��ִ� �κ�
	EnemyDraw();
	//�̻��ϰ� �� �浹
	ClashEnemyAndBullet(score, level, power);
	//������ �׸���
	ItemDraw();
	//�÷��̾�� ������ �浹
	ClashItemAndPlayer(life, power);

}

void PrintScreen(int lvl, int life, int score)
{
	bg[YMAX-1][XMAX-1] = '\0';
	printf("%s\n", bg);
	printf("	Level = %i			life = %i				score = %i", lvl,life,score);
	
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

void BulletDraw(int *power)
{
	//�̻��� ��ü 20���߿�
	for (int i = 0; i < 20; i++) {
		//�÷��̾� �̻��� ���ư��� �ִ� ���� true
		if (playerBullet[i].fire == true) {
			//�̻����� �׸���.
			for (int j = -*power + 1; j < *power; j++) {
				if (playerBullet[i].y + j < 25 && playerBullet[i].y + j >= 0)
				bg[playerBullet[i].y + j][playerBullet[i].x - 0] = ')';
			}


			/*switch (*power) {
			case 1:
				bg[playerBullet[i].y - 0][playerBullet[i].x - 0] = ')';
				break;
			case 2:
				bg[playerBullet[i].y - 1][playerBullet[i].x - 0] = ')';
				bg[playerBullet[i].y - 0][playerBullet[i].x - 0] = ')';
				bg[playerBullet[i].y + 1][playerBullet[i].x - 0] = ')';
				break;
			case 3:
				bg[playerBullet[i].y - 2][playerBullet[i].x - 0] = ')';
				bg[playerBullet[i].y - 1][playerBullet[i].x - 0] = ')';
				bg[playerBullet[i].y - 0][playerBullet[i].x - 0] = ')';
				bg[playerBullet[i].y + 1][playerBullet[i].x - 0] = ')';
				bg[playerBullet[i].y + 2][playerBullet[i].x - 0] = ')';
				break;
			}*/
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

void EnemyMove(int *life)
{
	//���� �������� ���� �Ѵ�.
	enemyX--;

	//���� �������� �� �ð��
	if (enemyX < 2) {
		//���� �����ϰ� y�� ��ǥ�� �ٲ��ش�
		enemyX = 77;
		enemyY = (rand() % 20) + 2;
		//����� 1�� ���ش�
		*life = *life - 1;
	}
}

void ClashEnemyAndBullet(int *score, int level, int *power)
{
	//�̻����� 20�� ��ü �Ǻ�
	for (int i = 0; i < 20; i++) {
		if (playerBullet[i].fire == true) {
			//���� �̻����� y���� ����
			if (playerBullet[i].y >= (enemyY - *power + 1) && playerBullet[i].y <= (enemyY + *power - 1)) {
				//�÷��̾� �̻��� x���� ������ �Ǻ�
				//x���� ���� ũ�⸸ŭ x-1 x+1���� ���� ��ǥ�� �浹�ǰ� �Ǻ�
				if (playerBullet[i].x >= (enemyX - 1) && playerBullet[i].x <= (enemyX + 1)) {
					//�浹�Ǹ� ��y���� �ٲ��ֱ�
					enemyX = 77;
					enemyY = (rand() % 20) + 2;
					playerBullet[i].fire = false;
					//���ھ� ���
					*score = *score + 100 * level;
				}
			}
		}
	}
}

void ItemCreate() {
	for (int i = 0; i < 3; i++) {
		//�������� �غ�Ǿ��ִ� ��쿡�� ����
		if (items[i].exist == false) {
			items[i].exist = true;
			//������ ���� ����
			items[i].x = (rand() % 3) + 1;
			items[i].y = (rand() % 20) + 2;
			items[i].type = (rand() % 2);
			break;
		}
	}
}

void ItemDraw() {
	//������ �׸���
	for (int i = 0; i < 3; i++) {
		if (items[i].exist == true) {
			if (items[i].type == 1) {
				bg[items[i].y][items[i].x] = 'L';
			}
			else {
				bg[items[i].y][items[i].x] = 'P';
			}
		}
	}
}

void ClashItemAndPlayer(int *life, int *power)
{
	//�������� 3�� �Ǻ�
	for (int i = 0; i < 3; i++) {
		if (items[i].exist == true) {
			//�÷��̾�� ������ Y���� +-1���� �浹�����ϰ� �Ǻ�
			if (items[i].y >= (playerY - 1) && items[i].y <= (playerY + 1)) {
				//�÷��̾�� ������ X���� +-1���� �浹�����ϰ� �Ǻ�
				if (items[i].x >= (playerX - 1) && items[i].x <= (playerX + 1)) {
					//�浹�Ǹ� ������ ȹ���ϱ�
					if (items[i].type == 1) {
						*life = *life + 1;
					}
					else {
						if (*power < 10) {
							*power = *power + 1;
						}
						else {
							*life = *life + 1;
						}
					}
					items[i].exist = false;
				}
			}
		}
	}
}

