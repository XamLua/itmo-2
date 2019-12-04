#include <bitset>
#include <stdio.h>

void min_diff();

int n;
int *ws = new int[20];
int sum = 0;

int main() {

  scanf("%d\n", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &ws[i]);
    sum += ws[i];
  }
  min_diff();

  return 0;
}

void min_diff() {

  std::bitset<1000001> check;

  check[0] = 1;

  for (int i = 0; i < n; i++) {
    check |= check << ws[i];
  }

  for (int j = sum / 2; j >= 0; j--) {
    if (check[j]) {
      printf("%d", sum - 2 * j);
      break;
    }
  }
}
