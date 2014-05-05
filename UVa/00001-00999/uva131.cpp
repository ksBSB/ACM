#include <stdio.h>
#include <string.h>

const int N = 20;
const int M = 5;
const char answer[N][2 * N] = {"highest-card", "one-pair", "two-pairs", "three-of-a-kind", "straight", "flush", "full-house", "four-of-a-kind", "straight-flush"};
const int bas_two[M] = {16, 8, 4, 2, 1};

struct Card {
    int number;
    int sex;
    char name[M];
}hand[N];

int is_number(char c) {
    if(c > '1' && c <= '9')
	return c - '0';
    else if (c == 'T')
	return 10;
    else if (c == 'J')
	return 11;
    else if (c == 'Q')
	return 12;
    else if (c == 'K')
	return 13;
    else if (c == 'A')
	return 1;
    else 
	return 0;
}

int is_sex(char c) {
    if (c == 'C')
	return 0;
    else if (c == 'D')
	return 1;
    else if (c == 'H')
	return 2;
    else if (c == 'S')
	return 3;
}

void handle(int cur, char str[]) {
    strcpy(hand[cur].name, str);
    hand[cur].number = is_number(str[0]);
    hand[cur].sex = is_sex(str[1]);
}

bool maxLink_num(int num[]) {
    for (int i = 1; i < 10; i++) {
	if (num[i] > 1)
	    return false;
	if (num[i] == 1) {
	    int flag = 1;
	    for (int j = 0; j < M; j++) {
		if (num[j + i] != 1) {
		    flag = 0;
		    break;
		}
	    }
	    if (flag)
		return true;
	}
    }

    if (num[10] == 1 && num[11] == 1 && num[12] == 1 && num[13] == 1 && num[1] == 1)
	return true;
    return false;
}

int judge(int cur) {
    int A[N], B[N], C[N];
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    memset(C, 0, sizeof(C));
    for (int i = 0; i < M; i++) {
	if (cur / bas_two[i])
	    B[i] = 0;
	else
	    B[i] = 1;
	cur = cur % bas_two[i];
    }

    int cnt = 0;
    for (int i = 0; cnt < M; i++) {
	if (!B[i]) {
	    C[hand[i].sex]++;
	    A[hand[i].number]++;
	    cnt++;
	}
    }

    // Judge color and num;
    int flag_color = 0, flag_num = 0;
    for (int i = 1; i < 14; i++) {
	if (A[i])
	    flag_num++;
    }
    for (int i = 0; i < 4; i++) {
	if(C[i])
	    flag_color++;
    }
    bool link = maxLink_num(A);
    int max = 0;
    for (int i = 1; i < 14; i++)
	if (A[i] > max)
	    max = A[i];
    //    printf("link:%d, flag_color:%d, max:%d, flag_num:%d\n", link, flag_color, max, flag_num);

    if (flag_color == 1 && link)
	return 8;
    else if (max == 4)
	return 7;
    else if (max == 3 && flag_num == 2)
	return 6;
    else if (flag_color == 1)
	return 5;
    else if (link)
	return 4;
    else if (max == 3)
	return 3;
    else if (max == 2 && flag_num == 3)
	return 2;
    else if (max == 2)
	return 1;
    else
	return 0;
}

int main() {
    int n = 0, max = 0, flag = 0;
    char str[N];
    while (1) {

	for (int i = 0; i < 10; i++) {
	    if (scanf("%s", str) != 1) {
		flag = 1;
		break;
	    }
	    handle(i, str);
	}
	if (flag)   break;

	for (int i = 0; i < 32; i++) {
	    flag = judge(i);
	    if (flag > max)
		max = flag;
	}

	// Printf;
	printf("Hand: ");
	for (int i = 0; i < 5; i++)
	    printf("%s ", hand[i].name);
	printf("Deck: ");
	for (int i = 0; i < 5; i++)
	    printf("%s ", hand[i + M].name);
	printf("Best hand: %s\n", answer[max]);

	// Init;
	memset(hand, 0, sizeof(hand));
	n = max = flag = 0;
    }
    return 0;}
