#include <algorithm>
#include <iostream>
#include <stdio.h>

using namespace std;

unsigned long long n, res = 0;

unsigned long long xs[100000], ys[100000];

void count();

int main() {

  scanf("%llu", &n);

  for (int i = 0; i < n; i++) {
    scanf("%llu %llu", &xs[i], &ys[i]);
  }

  count();

  printf("%llu\n", res);

  return 0;
}

void count() {
  sort(xs, xs + n);
  sort(ys, ys + n);
  for (unsigned long long i = 1; i <= n / 2; i++) {
    res += ((xs[i] + ys[i] - xs[i - 1] - ys[i - 1] + xs[n - i] + ys[n - i] -
             xs[n - i - 1] - ys[n - i - 1]) *
            (n - i) * i);
  }
  if (n % 2 == 0)
    res -= (xs[n / 2] + ys[n / 2] - xs[n / 2 - 1] - ys[n / 2 - 1]) * (n / 2) *
           (n / 2);

  res /= n * (n - 1) / 2;
}