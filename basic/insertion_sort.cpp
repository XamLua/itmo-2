#include <iostream>
#include <time.h>

using namespace std;

//прототип функции сортировки вставками
void InsertionSort(int*, int);

int main() {
	int N;
	cin >> N; // количество элементов
	// если пригодится для отладки, генератор случайных чисел
	// srand(time(NULL)); // инициализатор генератора
	// rand()%99 + 1: сгенерирует случайное число от 1 до 99.

	int* A = new int[N]; // объявляем массив и выделяем память для него
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	InsertionSort(A, N); // вызов функции сортировки

	for (int i = 0; i < N; ++i) {
		cout << A[i] << " ";
	}
	
	delete[] A; // освобождаем память из-под массива
}

void InsertionSort(int* A, int N) {
	
	int temp;

	for (int i = 0; i < N; i++){
		
		for (int j = i; j > 0 && A[j] < A[j - 1]; j--){

			swap(A[j], A[j - 1]);
		}
	}
} 