#include <stdio.h>
#include <string.h>
const int N = 30;
const int M = 10005;
int answer[N], gass[N];
int cntAnswer, cntWrong;

int main() {
    int cas;
    char str[M];
    while (scanf("%d", &cas), cas != -1) {
	// Init;
	memset(answer, 0, sizeof(answer));
	memset(gass, 0, sizeof(gass));
	cntAnswer = cntWrong = 0;

	scanf("%s", str);

	int len = strlen(str);
	for (int i = 0; i < len ; i++) {
	    if (answer[str[i] - 'a'] == 0) {
		answer[str[i] - 'a'] = 1;
		cntAnswer++;
	    }
	}

	scanf("%s", str);

	len = strlen(str);
	for (int i = 0; i < len; i++) {
	    if (gass[str[i] - 'a']) continue;
	    if (answer[str[i] - 'a'])
		cntAnswer--;
	    else
		cntWrong++;
	    gass[str[i] - 'a'] = 1;
	    if (cntAnswer == 0 || cntWrong == 7)
		break;
	}

	printf("Round %d\n", cas);
	if (cntAnswer)
	    printf("%s\n", cntWrong != 7 ? "You chickened out." : "You lose.");
	else
	    printf("You win.\n");
    }
    return 0;
}
