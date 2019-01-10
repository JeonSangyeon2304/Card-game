#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)
#define DEC 52 // 전체 카드 숫자
int start_menu();
int game_help();
void game_score();
void Black_Jack();
void card_select(int *n, int *k);
void card_print(int *n, int *k, int num);
int win[3] = { 0 }, lose[3] = { 0 }, drow[3] = { 0 }, // 선택, 승, 무, 패 전역 선언
card_player[21] = { 0 }, card_com[21] = { 0 }, // 컴퓨터, 플레이어 카드 숫자
card[DEC] = { 0 }, // 전체 카드 숫자
pattern_player[10], pattern_com[10]; // 컴퓨터, 플레이어 패턴

void main()	{ // 메인함수
	int select;
	select = start_menu();
	switch (select)	{ // switch1 시작
	case 1:	Black_Jack();
		break;
	case 2: game_score();
		break;
	case 3: game_help();
		break;
	case 4: exit(0);
	}// switch1 종료
}// 메인함수 종료
int start_menu()	{// 시작메뉴
	system("cls");
	int select;

	printf("\n\n\t\t□□□□□□□□□□□□□□□□□□□□□\n");
	printf("\t\t□\t\tWelcome to \t\t□\n");
	printf("\t\t□\t\tCard Game!\t\t□\n");
	printf("\t\t□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("\t1. Black Jack Start\n\t2. Game Score\n\t3. Game Help\n\t4. End Game\n\t▶▶  ");
	scanf("%d", &select);

	return select;
}// 시작메뉴 종료
int game_help(){// 게임 도움말 메뉴 지금은 블랙잭만..
	system("cls");
	printf("\n\n\t이 게임은 카드를 획득하여 나오는 수의 합을 \n\t21에 가깝게 맞추는 사람이 이기는 게임입니다.\n");
	printf("\tJ, Q, K는 10으로 바꿀 수 있으며, A는 1 혹은 11로 계산합니다.\n");
	printf("\t만약 모든 수의 합이 21을 넘길 경우 패배하게 됩니다.\n\n");
	system("pause");

	return main();
}// 게임 헬프메뉴 종료

void card_select(int *n, int *k)	{
	while (card[rand() % DEC]); // 카드 52장중 택1
	card[rand() % DEC] = 1; // 뽑았으면 중복안되게 표시
	*n = (rand() % DEC) % 13 + 1; // 1~13까지
	/////////////////////// 패 문양 뽑기
	*k = (rand() % DEC) / 13; // 0: 스페이드, 1: 다이아, 2: 하트, 3: 클로버
}
void card_print(int *n, int *k, int num)	{
	if (num == 0)
	{ // 컴퓨터 패 출력
		if (*k == 0) printf("♠♠");
		else if (*k == 1) printf("◆◆");
		else if (*k == 2) printf("♥♥");
		else if (*k == 3) printf("♣♣");
	}
	if (num == 1)	{ // 플레이어 패 출력
		if (*k == 0) printf("♠");
		else if (*k == 1) printf("◆");
		else if (*k == 2) printf("♥");
		else if (*k == 3) printf("♣");

		if (*n>1 && *n <11)	printf("%d", *n);
		else if (*n == 11) printf("J");
		else if (*n == 12) printf("Q");
		else if (*n == 13) printf("K");
		else if (*n == 1) printf("A");
	}
}
void Black_Jack()	{
	system("cls");
	int count = 0, i, k = 1, sel, sum_com = 0, sum_player = 0,
		count_com = 0; // 컴퓨터는 중간에 안받을수도 있으니 따로

	srand(time(NULL));

	while (1)	{
		count++;
		printf("===============\n");
		printf("Dealer Turn: ");
		if (sum_com <= 17)	{// 딜러는 카드합이 17이 넘기 전까지 계속 받아야된다
			count_com++;
			card_select(&card_com[count], &pattern_com[count]);
			if (card_com[count_com]>10) card_com[count_com] = 10;
			else if (card_com[count_com] == 1) card_com[count_com] = 11;
			sum_com += card_com[count_com]; // 컴퓨터 패 숫자 합산
		}// 컴퓨터는 A를 항상 11로만 해야된다.
		card_print(&card_com[1], &pattern_com[1], 1); // 처음패는 보여줘야한다
		printf(" ::: ");
		for (i = 2; i <= count_com; i++)	{
			card_print(&card_com[i], &pattern_com[i], 0);
			printf(" ::: ");
		}
		puts("");
		////////////////////////////////// 딜러 턴 종료

		printf("===============\n");
		printf("Player Turn: ");
		card_select(&card_player[count], &pattern_player[count]);
		if (card_player[count]>10) card_player[count] = 10; // 영문자는 10으로 취급 
		for (i = 1; i <= count; i++)	{
			card_print(&card_player[i], &pattern_player[i], 1);
			printf(" ::: ");
		}
		puts("");
		////////////////////////////////// 플레이어 턴 종료

		if (count >= 2)	{ // 블랙잭은 기본적으로 패를 2개 받는다.
			printf("패를 더 받으시겠습니까?(1. Yes 2. No)");
			scanf("%d", &sel);

			if (sel == 2) break;
		}
	}
	for (i = 1; i <= count; i++)	{ // 플레이어 패 숫자 합산
		if (card_player[i] == 1)	{ // A는 1또는 11로 바꿀수 있다.
			printf("A를 1로하시겠습니까? 11로 하시겠습니까?(1. 1로 2. 11로) ");
			scanf("%d", &sel);
			if (sel == 1)	sum_player += 1;
			else if (sel == 2) sum_player += 11;
		}
		else sum_player += card_player[i];
	}


	printf("Dealer: %d VS Player: %d\n", sum_com, sum_player);
	/////////////////////// 블랙잭 승무패 
	if ((sum_com == 21 && sum_player == 21) || (sum_com > 21 && sum_player > 21)
		|| (sum_com == sum_player)) {
		puts("D R O W");
		drow[0]++;
	} // 둘다 21이거나 21이 넘거나 둘의 숫자가 같으면 무승부
	else if (sum_com == 21 || sum_player > 21)	{
		puts("L O S E");
		lose[0]++;
	} // 컴퓨터가 21이거나 플레이어가 21이 넘으면 패
	else if (sum_player == 21 || sum_com > 21 || sum_player > sum_com)	{
		puts("W I N");
		win[0]++;
	} // 플레이어가 21이거나 컴퓨터가 21이 넘으면 패
	else if (sum_com > sum_player)	{
		puts("L O S E");
		lose[0]++;
	}
	else if (sum_player > sum_com)	{
		puts("W I Z");
		win[0]++;
	}

	printf("게임을 더 하시겠습니까?(1. Yes 2. No) ");
	scanf("%d", &sel);
	if (sel == 1)	{
		system("cls");
		Black_Jack();
	}
	else if (sel == 2)	{
		system("cls");
		main();
	}
}

void game_score()	{
	int a;

	system("cls");
	printf("\n\n\t\t□□□□□□□□□□□□□□□□□□□□□\n");
	printf("\t\t□\t\t Your Score \t\t□\n");
	printf("\t\t□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("\t\tW I N: %d\n", win[0]);
	printf("\t\tL O S E: %d\n", lose[0]);
	printf("\t\tD R O W: %d\n\n\n", drow[0]);
	while (1)	{
		printf("\t\t1. 초기화 2. 메인메뉴\n\t\t▶▶");
		scanf("%d", &a);
		if (a == 1)	{
			win[0] = 0;
			lose[0] = 0;
			drow[0] = 0;
			game_score();
		}
		else if (a == 2) main();
		else printf("\t\t잘못 누르셨습니다. 다시 눌러주세요.\n");
	}
}