#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int res_1, res_2, min_x_dot;

int dots[10000], xs[10000], ys[10000];

int n;

void split();

int cmp_angle(const int &a, const int &b);

int main() {

  scanf("%d", &n);

  min_x_dot = 0;

  for (int i = 0; i < n; i++) {

    dots[i] = i;

    scanf("%d %d", &xs[i], &ys[i]);

    if (xs[dots[i]] <= xs[dots[min_x_dot]]) {
      if (xs[dots[i]] == xs[dots[min_x_dot]])
        min_x_dot = ys[dots[i]] < xs[dots[min_x_dot]] ? i : min_x_dot;
      else
        min_x_dot = i;
    }
  }

  swap(dots[0], dots[min_x_dot]);

  split();

  printf("%d %d\n", res_1 + 1, res_2 + 1);

  return 0;
}

int cmp_angle(const int &a, const int &b) {

  if (ys[a] == ys[res_1] || ys[b] == ys[res_1])
    return ys[a] > ys[b];

  if (ys[a] > ys[res_1] && ys[b] > ys[res_1])
    return (float)abs(xs[a] - xs[res_1]) / (float)abs(ys[a] - ys[res_1]) <
           (float)abs(xs[b] - xs[res_1]) / (float)abs(ys[b] - ys[res_1]);

  if (ys[a] < ys[res_1] && ys[b] < ys[res_1])
    return (float)abs(xs[a] - xs[res_1]) / (float)abs(ys[a] - ys[res_1]) >
           (float)abs(xs[b] - xs[res_1]) / (float)abs(ys[b] - ys[res_1]);

  return ys[a] > ys[b];
}

void split() {

  res_1 = dots[0];

  sort(dots + 1, dots + n, cmp_angle);

  res_2 = dots[n / 2];
}