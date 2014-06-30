#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 100005
#define M 20

char num[N][M];
char str[100];

char change(char c){
	switch(c){
		case 'A': case 'B': case 'C':  case '2':
			return '2';
		case 'D': case 'E': case 'F':  case '3':
			return '3';
		case 'G': case 'H': case 'I':  case '4':
			return '4';
		case 'J': case 'K': case 'L':  case '5':
			return '5';
		case 'M': case 'N': case 'O':  case '6':
			return '6';
		case 'P': case 'R': case 'S':  case '7':
			return '7';
		case 'T': case 'U': case 'V':  case '8':
			return '8';
		case 'W': case 'X': case 'Y':  case '9':
			return '9';
		case '1':
			return '1';
		case '0':
			return '0';
		default:
			return '\0';
	}	
}	

int cmp(const void *a, const void *b){
	char *x = (char *)a;
	char *y = (char *)b;
	return strcmp(x, y);
}

void print(char a[], int bo){
	for (int j = 0; j < 7; j++){
		if (j == 3)
			printf("-");
		printf("%c", a[j]);
	}
	printf(" %d\n", bo);
}

int main(){
	int t, n;
	char c;
	scanf("%d", &t);
	while (t--){
		// Init.
		memset(num, 0, sizeof(num));

		// Read.
		scanf("%d%*c", &n);
		for (int i = 0; i < n; i++){
			int m = 0;
			memset(str, 0, sizeof(str));
			gets(str);
			int l = strlen(str);
			for (int j = 0; j < l; j++){
				if ( change(str[j]) != '\0')
					str[m++] = change(str[j]);
			}
			str[m] = '\0';
			strcpy(num[i], str);
		}

		qsort(num, n, sizeof(num[0]), cmp);

		int leap = 0, bo = 0;

		for (int i = 1; i <= n; i++){
			if (strcmp(num[i], num[i - 1]) != 0){
				if (i - bo > 1){
					leap++;
					print(num[i - 1], i - bo);
				}
				bo = i;
			}
		}

		if (leap == 0)
			printf("No duplicates.\n");
		if (t)
			printf("\n");
	}
	return 0;}
