#include<stdio.h>
#include<string.h>
#define N 10005
char str[N];

int main(){
	char *head, *move, *end;
	int n, i;
	scanf("%d", &n);
	while (n--){
		memset(str, 0, sizeof(str));

		scanf("%s", str);

		if (!strcmp(str, "1") || !strcmp(str, "4") || !strcmp(str, "78"))
			printf("+\n");
		else if (str[ strlen(str) - 1] == '5' && str[ strlen(str) - 2] == '3')
			printf("-\n");
		else if (str[0] == '1' && str[1] == '9' && str[2] == '0')
			printf("?\n");
		else
			printf("*\n");
	}
	return 0;}
