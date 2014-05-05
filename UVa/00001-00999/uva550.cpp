U#include<iostream>
#include<math.h>
using namespace std;

int main(){
	int bas, b, c;
	while (cin >> bas >> b >> c){
		int cnt = 0, p = 0, sum, over = b;
		while (1){
			cnt++;
			sum = b * c + p;
			b = sum % bas;
			p = sum / bas;

			if (over == b && p == 0)
				break;
		}
		cout << cnt << endl;
	}	
	return 0;
}
