#include<stdio.h>
#include<string.h>
#define N 30
#define M 105

char str[M], tem[M];
int num[N], bo[N];

int count(char n, char c){
	if (c == '+')
		return num[n - 'a' + 1];
	else
		return num[n - 'a' + 1] * (-1);
}

int main(){
	while (gets(str) != NULL){
		// Init.
		for (int i = 1; i <= 26; i++)
			num[i] = i;
		memset(bo, 0, sizeof(bo));
		int n = strlen(str), k = 0;
		for (int i = 0; i < n; i++){
			if (str[i] == ' ')
				continue;
			tem[k++] = str[i];
		}
		tem[k] ='\0';
		n = k;
		// Handle Prefix.
		for (int i = 0; i < n; i++){
			if (tem[i] >= 'a' && tem[i] <= 'z'){
				bo[tem[i] - 'a' + 1] = 1;
				if(i){
					if(tem[i - 1] == '+' && tem[i - 2] == '+'){
						tem[i - 1] = tem[i - 2] = '0';
						num[tem[i] - 'a' + 1]++;
					}
					else if (tem[i - 1] == '-' && tem[i - 2] == '-'){
						tem[i - 1] = tem[i - 2] = '0';
						num[tem[i] - 'a' + 1]--;
					}
				}
			}
		}

		// Count value.
		int sum = 0;
		char * move = tem, c = '+';
		while (1){
			if (*move == '\0')
				break;

			if (*move >= 'a' && *move <= 'z')
				sum = sum + count(*move, c);

			if (*move == '+' && *(move + 1) != '+' && *(move - 1) != '+')
				c = '+';
			if (*move == '-' && *(move + 1) != '-' && *(move - 1) != '-')
				c = '-';
			move++;
		}

		// Handle suffix.
		for (int i = 0; i < n; i++){
			if (tem[i] >= 'a' && tem[i] <= 'z'){
				if (n - i > 2){
					if (tem[i + 1] == '+' && tem[i + 2] == '+')
						num[tem[i] - 'a' + 1]++;
					if (tem[i + 1] == '-' && tem[i + 2] == '-')
						num[tem[i] - 'a' + 1]--;
				}
			}
		}

		// Printf.
		printf("Expression: ");
		puts(str);
		printf("    value = %d\n", sum);
		for (int i = 1; i <= 26; i++){
			if (bo[i])
				printf("    %c = %d\n", 'a' + i - 1, num[i]);
		}
	}
	return 0;}
