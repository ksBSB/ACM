#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 10005
#define T 205
#define M 20

struct say{
	char word[M];
}s[T];

struct talk{
	char sen[T][M];
	int cnt;
}title[T];

int n_s = 0, n_title = 0, n_ignore = 0;;
char ignore_word[T][M];

void change(char str[]){
	int len = strlen(str);
	for (int i = 0; i < len; i++){
		if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
}

int cmp(const say a, const say b){
	return strcmp(a.word, b.word) < 0;
}

void print(talk t, int k){
	for (int i = 0; i < t.cnt - 1; i++){
		if (i == k){
			for (int j = 0; j < strlen(t.sen[i]); j++)
				printf("%c", t.sen[i][j] - 32);
			printf(" ");
		}
		else 
			printf("%s ", t.sen[i]);
	}
	if (t.cnt - 1 == k){
		for (int j = 0; j < strlen(t.sen[t.cnt - 1]); j++)
			printf("%c", t.sen[t.cnt - 1][j] -32);
		printf("\n");
	}
	else
		printf("%s\n", t.sen[t.cnt - 1]);
}

void find(talk t, say a){
	for (int i = 0; i < t.cnt; i++){
		if (strcmp(t.sen[i], a.word) == 0)
			print(t, i);
	}
}

void judge(char str[]){
	for (int i = 0; i < n_ignore; i++){
		if (strcmp(ignore_word[i], str) == 0)
			return;
	}
	for (int i = 0; i < n_s; i++){
		if (strcmp(s[i].word, str) == 0)
			return;
	}
	strcpy(s[n_s++].word, str);
}

void build(char str[], int k){
	int len = strlen(str), n = 0, m = 0;
	for (int i = 0; i < len; i++){
		if (str[i] >= 'a' && str[i] <= 'z')
			title[k].sen[n][m++] = str[i];
		else{
			title[k].sen[n][m] = '\0';
			judge(title[k].sen[n]);
			m = 0;
			n++;
		}
	}
	title[k].sen[n++][m] = '\0';
	judge(title[k].sen[n - 1]);
	title[k].cnt = n;
}

int main(){
	char name[N];

	// Read.
	while (1){
		gets(ignore_word[n_ignore]);
		if (strcmp(ignore_word[n_ignore], "::") == 0)
			break;
		change(ignore_word[n_ignore]);
		n_ignore++;
	}
	while (gets(name) != NULL){
		change(name);
		build(name, n_title);
		n_title++;
	}

	// Ready.
	sort(s, s + n_s, cmp);

	// Find.
	for (int i = 0; i < n_s; i++)
		for (int j = 0; j < n_title; j++)
			find(title[j], s[i]);
	return 0;}
