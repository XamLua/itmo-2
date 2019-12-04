#include <iostream>
#include <time.h>

using namespace std;

// прототипы функций
void merge(int *, int, int);
void mergeRec(int *, int, int);
int N;

int main() {
  cin >> N; // количество входных элементов
  // если пригодится для отладки, генератор случайных чисел
  // srand(time(NULL)); // инициализатор генератора
  // rand()%99 + 1: сгенерирует случайное число от 1 до 99.

  int *A = new int[N];
  for (int i = 0; i < N; i++) {
    cin >> A[i]; // заполнение массива
  }
  mergeRec(A, 0, N - 1); // вызов сортировки

  for (int i = 0; i < N; i++) {
    cout << A[i] << " "; // печать
  }
  delete[] A; // освободили память
  return 0;
}

void mergeRec(int *A, int left, int right) {
  // рекурсивный вызов разделения, затем вызов слияния
  // необходимо реализовать
  if (left == right)
    return;
  mergeRec(A, left, (left + right) / 2);
  mergeRec(A, (left + right) / 2 + 1, right);
  merge(A, left, right);
}

void merge(int *A, int left, int right) {
  // процедура для слияния A[left .. mid] и A[mid+1 .. right];
  // необходимо реализовать

  int middle = (left + right) / 2;

  int *temp = new int[right - left + 1];

  int i = 0, j = 0;

  while (i + left <= middle && middle + 1 + j <= right) {

    if (A[i + left] < A[middle + 1 + j]) {

      temp[i + j] = A[i + left];
      i++;
    } else {
      temp[i + j] = A[middle + 1 + j];
      j++;
    }
  }

  while (i + left <= middle) {
    temp[i + j] = A[i + left];
    i++;
  }

  while (j + middle + 1 <= right) {
    temp[i + j] = A[middle + 1 + j];
    j++;
  }

  for (int k = 0; k < i + j; k++) {

    A[left + k] = temp[k];
  }

  delete[] temp;
};