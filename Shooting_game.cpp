#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define XMAX 100
#define YMAX 25

//미사일 구조체
struct BULLET {
	int x;
	int y;
	bool fire;
};

//배열로 배경 좌표를 만든다.
char bg[YMAX][XMAX];

//플레이어 좌표
int playerX;
int playerY;

//적 좌표
int enemyX;
int enemyY;

//미사일 갯수
BULLET playerBullet[21];

//함수 설계
void ClearScreen(); //화면을 지운다
void GameMain(int *lif, int *score, int level);	//게임전체를 관리하는 함수
void PrintScreen(int lvl, int lif, int score);	//화면을 그려주는 함수
void KeyControl();	//키관련 함수
void BulletDraw();	//미사일을 그려주는 함수
void PlayerDraw();	//플레이어 그리는 함수
void EnemyDraw();	//적그리는 함수
void EnemyMove(int *life);	//적움직이는 함수
void ClashEnemyAndBullet(int *score, int level);	//충돌처리 함수

void main() {
	int speed = 50;	//게임 속도 
	int level = 1;	//게임 난이도
	int life = 3;	//남은 목숨
	int score = 0;	//스코어
	//랜덤함수 준비
	srand((unsigned)time(NULL));
	//플레이어 좌표 위치
	playerX = 1;
	playerY = YMAX/2;

	//적 좌표 위치
	enemyX = 77;
	enemyY = 12;

	//플레이어 미사일 초기화
	for (int i = 0; i < 20; i++) {
		playerBullet[i].x = 0;
		playerBullet[i].y = 0;
		playerBullet[i].fire = false;
	}

	//초단위 시간을 받아옴
	int dwTime = GetTickCount64();
	int stTime = GetTickCount64();
	//게임실행 무한루프
	while (true) {
		if (dwTime + speed < GetTickCount64()) {
			dwTime = GetTickCount64();
			//지우는 함수
			ClearScreen();
			//플레이어나 적이 움직이는 함수
			GameMain(&life, &score, level);
			//그려주는 함수
			PrintScreen(level, life, score);
		}
		if (stTime + 10000 < GetTickCount64()) {
			speed = speed - 5;
			level++;
			stTime = GetTickCount64();
		}
		if (life == 0) {
			//콘솔창을 지움
			system("cls");
			//배열에 공백으로 넣어서 지움
			printf("gameover");
			break;
		}
	}
}

void ClearScreen()
{
	//콘솔창을 지움
	system("cls");
	//배열에 공백으로 넣어서 지움
	for (int y = 0; y < YMAX; y++) {
		for (int x = 0; x < XMAX; x++) {
			bg[y][x] = ' ';
		}
	}
}

void GameMain(int *life, int *score, int level)
{
	//키를 입력하는 부분
	KeyControl();
	//미사일을 그려주는 부분
	BulletDraw();
	//플레이어를 그려주는 부분
	PlayerDraw();
	//적의 움직임
	EnemyMove(life);
	//적을 그려주는 부분
	EnemyDraw();
	//미사일과 적 충돌
	ClashEnemyAndBullet(score, level);

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

	//키가 입력되면 잡아줌
	if (_kbhit()) {
		pressKey = _getch();	//키가 입력되어 변수에 저장
		switch (pressKey) {
		case 72:
			//위쪽 방향키
			if (playerY == 1)
				break;
			playerY--;
			break;
			/*playerY--;
			if (playerY < 1)
				playerY = 1;
			break;*/
		case 75:
			//왼쪽 방향키
			if (playerX == 1)
				break;
			playerX--;
			break;
		case 77:
			//오른쪽 방향키
			if (playerX == XMAX-2)
				break;
			playerX++;
			break;
		case 80:
			//아래쪽 방향키
			if (playerY == YMAX-2)
				break;
			playerY++;
			break;
		case 32:
			//스페이스바
			for (int i = 0; i < 20; i++) {
				//미사일이 준비되어있는 상태인 경우에만 발사가능
				if (playerBullet[i].fire == false) {
					playerBullet[i].fire = true;
					//플레이어 앞에서 미사일을 쏘기
					playerBullet[i].x = playerX + 5;
					playerBullet[i].y = playerY;
					//한발만 발사하기
					break;
				}
			}
			break;
		}
	}
}

void BulletDraw()
{
	//미사일 전체 20개중에
	for (int i = 0; i < 20; i++) {
		//플레이어 미사일 날아가고 있는 상태 true
		if (playerBullet[i].fire == true) {
			//미사일을 그린다.
			bg[playerBullet[i].y][playerBullet[i].x - 1] = '-';
			bg[playerBullet[i].y][playerBullet[i].x - 0] = '>';
			//미사일 앞으로 +1
			playerBullet[i].x++;
			if (playerBullet[i].x > XMAX-1) {
				//미사일 준비상태로 전환
				playerBullet[i].fire = false;
			}
		}
	}
}

void PlayerDraw()
{
	//플레이어 그리기
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
	//적 그리기
	bg[enemyY][enemyX - 2] = '<';
	bg[enemyY][enemyX - 1] = '-';
	bg[enemyY][enemyX - 0] = 'O';
	bg[enemyY][enemyX + 1] = '-';
	bg[enemyY][enemyX + 2] = '>';
}

void EnemyMove(int *life)
{
	//적은 왼쪽으로 오게 한다.
	enemyX--;

	//적이 왼쪽으로 다 올경우
	if (enemyX < 2) {
		//적을 랜덤하게 y쪽 좌표를 바꿔준다
		enemyX = 77;
		enemyY = (rand() % 20) + 2;
		*life = *life - 1;
	}
}

void ClashEnemyAndBullet(int *score, int level)
{
	//미사일이 20개 전체 판별
	for (int i = 0; i < 20; i++) {
		if (playerBullet[i].fire == true) {
			//적과 미사일의 y값이 같고
			if (playerBullet[i].y == enemyY) {
				//플레이어 미사일 x값이 같은지 판별
				//x값은 적의 크기만큼 x-1 x+1까지 세개 좌표로 충돌되게 판별
				if (playerBullet[i].x >= (enemyX - 1) && playerBullet[i].x <= (enemyX + 1)) {
					//충돌되면 적y값을 바꿔주기
					enemyX = 77;
					enemyY = (rand() % 20) + 2;
					playerBullet[i].fire = false;
					*score = *score + 100 * level;
				}
			}
		}
	}
}
