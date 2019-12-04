#include <iostream>
using namespace std;

long long LCD(long long, long long);

int main() {
  long long a, b;
  cin >> a >> b;
  cout << LCD(a, b);
  return 0;
}

long long LCD(long long a, long long b) {

  if (a == 0)
    return b;
  if (b == 0)
    return a;

  if ((a % b) == 0)
    return b;
  else
    return LCD(b, a % b);
}