#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

int empty_x, empty_y;

int field[1025][1025];

int size;

int n;

int counter = 1;

void fill_square(int x1, int y1, int x2, int y2, int e_x, int e_y);

int main() {

	scanf("%d", &n);
	scanf("%d", &empty_x);
	scanf("%d", &empty_y);	

	size = pow(2, n);

	fill_square(1, 1, size, size, empty_x, empty_y);

	field[empty_x][empty_y] = 0;

	for (int i = 1; i <= size; i++){
		
		for (int j = 1; j <= size; j++){

			printf("%d ", field[i][j]);

		}

		printf("\n");
	}

	return 0;
}

void fill_square(int x1, int y1, int x2, int y2, int e_x, int e_y){

	int temp, temp_value;

	if ((x2 - x1) == 1){
		field[x1][y1] = field[x2][y1] = field[x1][y2] = field[x2][y2] = counter++;
		return;
	}

	temp = (x2 - x1)/2 + 1;

	if (e_x < x1 + temp && e_y < y1 + temp){
		fill_square(x1, y1, x1 + temp - 1, y1 + temp - 1, e_x, e_y);
		e_x = x1 + temp - 1;
		e_y = y1 + temp - 1; 
		temp_value = field[e_x][e_y];
		fill_square(x1, y1 + temp, x1 + temp - 1, y2, x1 + temp - 1, y1 + temp);
		fill_square(x1 + temp, y1, x2, y1 + temp - 1, x1 + temp, y1 + temp - 1);
		fill_square(x1 + temp, y1 + temp, x2, y2, x1 + temp, y1 + temp);
	}

	if (e_x < x1 + temp && e_y >= y1 + temp){
		fill_square(x1, y1 + temp, x1 + temp - 1, y2, e_x, e_y);
		e_x = x1 + temp - 1;
		e_y = y1 + temp; 
		temp_value = field[e_x][e_y];
		fill_square(x1, y1, x1 + temp - 1, y1 + temp - 1, x1 + temp - 1, y1 + temp - 1);
		fill_square(x1 + temp, y1, x2, y1 + temp - 1, x1 + temp, y1 + temp - 1);
		fill_square(x1 + temp, y1 + temp, x2, y2, x1 + temp, y1 + temp);
	}

	if (e_x >= x1 + temp && e_y < y1 + temp){
		fill_square(x1 + temp, y1, x2, y1 + temp - 1, e_x, e_y);
		e_x = x1 + temp;
		e_y = y1 + temp - 1; 
		temp_value = field[e_x][e_y];
		fill_square(x1, y1, x1 + temp - 1, y1 + temp - 1, x1 + temp - 1, y1 + temp - 1);
		fill_square(x1, y1 + temp, x1 + temp - 1, y2, x1 + temp - 1, y1 + temp);
		fill_square(x1 + temp, y1 + temp, x2, y2, x1 + temp, y1 + temp);
	}

	if (e_x >= x1 + temp && e_y >= y1 + temp){
		fill_square(x1 + temp, y1 + temp, x2, y2, e_x, e_y);
		e_x = x1 + temp;
		e_y = y1 + temp; 
		temp_value = field[e_x][e_y];
		fill_square(x1, y1, x1 + temp - 1, y1 + temp - 1, x1 + temp - 1, y1 + temp - 1);
		fill_square(x1, y1 + temp, x1 + temp - 1, y2, x1 + temp - 1, y1 + temp);
		fill_square(x1 + temp, y1, x2, y1 + temp - 1, x1 + temp, y1 + temp - 1);
	}
	field[x1 + temp - 1][y1 + temp - 1] =
	field[x1 + temp -1][y1 + temp] =
	field[x1 + temp][y1 + temp - 1] = 
	field[x1 + temp][y1 + temp] =
	counter++;

	field[e_x][e_y] = temp_value;


}
