#include <iostream>
#include <limits.h>
#include <stdio.h>

int part_sum;

int mins;

int temp;

int maxs = INT_MIN;

int N;

int res;

int main() {

  scanf("%d", &N);

  for (int i = 1; i <= N; i++) {

    scanf("%d", &temp);

    part_sum += temp;

    if (part_sum < mins) {
      mins = part_sum;
      maxs = INT_MIN;
    }

    if (part_sum > maxs) {
      maxs = part_sum;
      res = std::max(maxs - mins, res);
    }
  }

  printf("%d\n", (res > 0) ? res : 0);

  return 0;
}