#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int main() {
    string str;
    while (getline(cin, str)) {
	int len = str.length(), cnt = 0;
	for (int i = 0; i < len; i++) {
	    if (str[i] >= '0' && str[i] <= '9')
		cnt += str[i] - '0';
	    else if (str[i] == '!')
		printf("\n");
	    else {
		for (int j = 0; j < cnt; j++)
		    printf("%c", str[i] != 'b' ? str[i] : ' ');
		cnt = 0;
	    }
	}
	printf("\n");
    }
    return 0;
}
