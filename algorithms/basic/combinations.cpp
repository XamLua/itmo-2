#include <iostream>
using namespace std;

int Combin(int, int);

int main() {
  int N, K;
  cin >> N >> K;
  cout << Combin(N, K);
  return 0;
}

int Combin(int N, int K) {

  if (N == 0)
    return 0;

  if (K == 0 || N == K)
    return 1;

  return Combin(N - 1, K) + Combin(N - 1, K - 1);
}