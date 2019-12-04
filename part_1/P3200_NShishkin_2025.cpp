#include <stdio.h>

unsigned long long fights(int n, int k);

int T, n, k;

int main() {

  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &k);
    printf("%llu\n", fights(n, k));
  }
  return 0;
}

unsigned long long fights(int n, int k) {

  unsigned long long result = 0;
  int small_teams_members = n / k;
  int small_teams_number = k - n % k;
  int big_teams_members = (n / k) + 1;
  int big_teams_number = n % k;

  result += small_teams_members * small_teams_members *
            (small_teams_number * (small_teams_number - 1) / 2);
  result += big_teams_members * big_teams_members *
            (big_teams_number * (big_teams_number - 1) / 2);
  result += small_teams_number * big_teams_number * small_teams_members *
            big_teams_members;

  return result;
}
