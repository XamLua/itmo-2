#include <iostream>
using namespace std;

double Power(double, int);

int main() {
  double X;
  int N;
  cin >> X >> N;
  cout << Power(X, N);
  return 0;
}

double Power(double X, int N) {

  if (N == 0)
    return 1;

  if (N < 0)
    return 1 / Power(X, -N);

  if (N % 2 == 0)
    return Power(X, N / 2) * Power(X, N / 2);

  return X * Power(X, N - 1);
}
