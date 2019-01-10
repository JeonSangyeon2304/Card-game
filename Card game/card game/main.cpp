#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)
#define DEC 52 // ��ü ī�� ����
int start_menu();
int game_help();
void game_score();
void Black_Jack();
void card_select(int *n, int *k);
void card_print(int *n, int *k, int num);
int win[3] = { 0 }, lose[3] = { 0 }, drow[3] = { 0 }, // ����, ��, ��, �� ���� ����
card_player[21] = { 0 }, card_com[21] = { 0 }, // ��ǻ��, �÷��̾� ī�� ����
card[DEC] = { 0 }, // ��ü ī�� ����
pattern_player[10], pattern_com[10]; // ��ǻ��, �÷��̾� ����

void main()	{ // �����Լ�
	int select;
	select = start_menu();
	switch (select)	{ // switch1 ����
	case 1:	Black_Jack();
		break;
	case 2: game_score();
		break;
	case 3: game_help();
		break;
	case 4: exit(0);
	}// switch1 ����
}// �����Լ� ����
int start_menu()	{// ���۸޴�
	system("cls");
	int select;

	printf("\n\n\t\t����������������������\n");
	printf("\t\t��\t\tWelcome to \t\t��\n");
	printf("\t\t��\t\tCard Game!\t\t��\n");
	printf("\t\t����������������������\n\n");
	printf("\t1. Black Jack Start\n\t2. Game Score\n\t3. Game Help\n\t4. End Game\n\t����  ");
	scanf("%d", &select);

	return select;
}// ���۸޴� ����
int game_help(){// ���� ���� �޴� ������ ���踸..
	system("cls");
	printf("\n\n\t�� ������ ī�带 ȹ���Ͽ� ������ ���� ���� \n\t21�� ������ ���ߴ� ����� �̱�� �����Դϴ�.\n");
	printf("\tJ, Q, K�� 10���� �ٲ� �� ������, A�� 1 Ȥ�� 11�� ����մϴ�.\n");
	printf("\t���� ��� ���� ���� 21�� �ѱ� ��� �й��ϰ� �˴ϴ�.\n\n");
	system("pause");

	return main();
}// ���� �����޴� ����

void card_select(int *n, int *k)	{
	while (card[rand() % DEC]); // ī�� 52���� ��1
	card[rand() % DEC] = 1; // �̾����� �ߺ��ȵǰ� ǥ��
	*n = (rand() % DEC) % 13 + 1; // 1~13����
	/////////////////////// �� ���� �̱�
	*k = (rand() % DEC) / 13; // 0: �����̵�, 1: ���̾�, 2: ��Ʈ, 3: Ŭ�ι�
}
void card_print(int *n, int *k, int num)	{
	if (num == 0)
	{ // ��ǻ�� �� ���
		if (*k == 0) printf("����");
		else if (*k == 1) printf("�ߡ�");
		else if (*k == 2) printf("����");
		else if (*k == 3) printf("����");
	}
	if (num == 1)	{ // �÷��̾� �� ���
		if (*k == 0) printf("��");
		else if (*k == 1) printf("��");
		else if (*k == 2) printf("��");
		else if (*k == 3) printf("��");

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
		count_com = 0; // ��ǻ�ʹ� �߰��� �ȹ������� ������ ����

	srand(time(NULL));

	while (1)	{
		count++;
		printf("===============\n");
		printf("Dealer Turn: ");
		if (sum_com <= 17)	{// ������ ī������ 17�� �ѱ� ������ ��� �޾ƾߵȴ�
			count_com++;
			card_select(&card_com[count], &pattern_com[count]);
			if (card_com[count_com]>10) card_com[count_com] = 10;
			else if (card_com[count_com] == 1) card_com[count_com] = 11;
			sum_com += card_com[count_com]; // ��ǻ�� �� ���� �ջ�
		}// ��ǻ�ʹ� A�� �׻� 11�θ� �ؾߵȴ�.
		card_print(&card_com[1], &pattern_com[1], 1); // ó���д� ��������Ѵ�
		printf(" ::: ");
		for (i = 2; i <= count_com; i++)	{
			card_print(&card_com[i], &pattern_com[i], 0);
			printf(" ::: ");
		}
		puts("");
		////////////////////////////////// ���� �� ����

		printf("===============\n");
		printf("Player Turn: ");
		card_select(&card_player[count], &pattern_player[count]);
		if (card_player[count]>10) card_player[count] = 10; // �����ڴ� 10���� ��� 
		for (i = 1; i <= count; i++)	{
			card_print(&card_player[i], &pattern_player[i], 1);
			printf(" ::: ");
		}
		puts("");
		////////////////////////////////// �÷��̾� �� ����

		if (count >= 2)	{ // ������ �⺻������ �и� 2�� �޴´�.
			printf("�и� �� �����ðڽ��ϱ�?(1. Yes 2. No)");
			scanf("%d", &sel);

			if (sel == 2) break;
		}
	}
	for (i = 1; i <= count; i++)	{ // �÷��̾� �� ���� �ջ�
		if (card_player[i] == 1)	{ // A�� 1�Ǵ� 11�� �ٲܼ� �ִ�.
			printf("A�� 1���Ͻðڽ��ϱ�? 11�� �Ͻðڽ��ϱ�?(1. 1�� 2. 11��) ");
			scanf("%d", &sel);
			if (sel == 1)	sum_player += 1;
			else if (sel == 2) sum_player += 11;
		}
		else sum_player += card_player[i];
	}


	printf("Dealer: %d VS Player: %d\n", sum_com, sum_player);
	/////////////////////// ���� �¹��� 
	if ((sum_com == 21 && sum_player == 21) || (sum_com > 21 && sum_player > 21)
		|| (sum_com == sum_player)) {
		puts("D R O W");
		drow[0]++;
	} // �Ѵ� 21�̰ų� 21�� �Ѱų� ���� ���ڰ� ������ ���º�
	else if (sum_com == 21 || sum_player > 21)	{
		puts("L O S E");
		lose[0]++;
	} // ��ǻ�Ͱ� 21�̰ų� �÷��̾ 21�� ������ ��
	else if (sum_player == 21 || sum_com > 21 || sum_player > sum_com)	{
		puts("W I N");
		win[0]++;
	} // �÷��̾ 21�̰ų� ��ǻ�Ͱ� 21�� ������ ��
	else if (sum_com > sum_player)	{
		puts("L O S E");
		lose[0]++;
	}
	else if (sum_player > sum_com)	{
		puts("W I Z");
		win[0]++;
	}

	printf("������ �� �Ͻðڽ��ϱ�?(1. Yes 2. No) ");
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
	printf("\n\n\t\t����������������������\n");
	printf("\t\t��\t\t Your Score \t\t��\n");
	printf("\t\t����������������������\n\n");
	printf("\t\tW I N: %d\n", win[0]);
	printf("\t\tL O S E: %d\n", lose[0]);
	printf("\t\tD R O W: %d\n\n\n", drow[0]);
	while (1)	{
		printf("\t\t1. �ʱ�ȭ 2. ���θ޴�\n\t\t����");
		scanf("%d", &a);
		if (a == 1)	{
			win[0] = 0;
			lose[0] = 0;
			drow[0] = 0;
			game_score();
		}
		else if (a == 2) main();
		else printf("\t\t�߸� �����̽��ϴ�. �ٽ� �����ּ���.\n");
	}
}