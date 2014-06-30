#include <stdio.h>
#include <stack>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
  stack<long long> add;
  stack<long long> mul;
  long long a, sum;
  char c;
  scanf("%lld", &a);
  add.push(a);
  mul.push(a);
  while (scanf("%c", &c) == 1 && c != '\n') {
      scanf("%lld", &a);
      if (c == '+') {
    sum = add.top();
    add.pop();
    add.push(sum + a);
    mul.push(a);
      }
      else if (c == '*') {
    sum = mul.top();
    mul.pop();
    mul.push(sum * a);
    add.push(a);
      }
  }
  long long Max = 1, Min = 0;
  while (!add.empty()) {
      Max *= add.top();
      add.pop();
  }

  while (!mul.empty()) {
      Min += mul.top();
      mul.pop();
  }

  printf("The maximum and minimum are %lld and %lld.\n", Max, Min);
    }
    return 0;
}
