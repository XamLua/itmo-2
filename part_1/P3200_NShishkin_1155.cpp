#include <stdio.h>
#include <iostream>
#include <string.h>

char symbols[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

int vertex[8];

int temp;

void clean_duones();

int main() {

	for (int i = 0; i < 8; i++){
		
		scanf("%d", &vertex[i]);

	}

	if (vertex[0] + vertex[2] + vertex[5] + vertex[7] - 
		vertex[1] - vertex[3] - vertex[4] - vertex[6]){
		printf("IMPOSSIBLE");
		return 0;
	}

	clean_duones();

	return 0;
}

void clean_duones(){

	int temp;

	for (int i = 0; i < 4; i++){
		temp = std::min(vertex[i], vertex[(i+1) % 4]);
		vertex[i] -= temp;
		vertex[(i+1) % 4] -= temp;
		for (int j = 0; j < temp; j++){
			printf("%c%c-\n", symbols[i], symbols[(i+1) % 4]);
		}
	}

	for (int i = 0; i < 4; i++){
		temp = std::min(vertex[i + 4], vertex[(i+1) % 4 + 4]);
		vertex[i + 4] -= temp;
		vertex[(i+1) % 4 + 4] -= temp;
		for (int j = 0; j < temp; j++){
			printf("%c%c-\n", symbols[i + 4], symbols[(i+1) % 4 + 4]);
		}
	}

	for (int i = 0; i < 4; i++){
		temp = std::min(vertex[i], vertex[i+4]);
		vertex[i] -= temp;
		vertex[i+4] -= temp;
		for (int j = 0; j < temp; j++){
			printf("%c%c-\n", symbols[i], symbols[i + 4]);
		}
	}

	for (int i = 0; i < 4; i++){
		if (vertex[i] != 0){
			temp = std::min(vertex[i], vertex[(i+2) % 4 + 4]);
			vertex[i] -= temp;
			vertex[(i+2) % 4 + 4] -= temp;
			for (int j = 0; j < temp; j++){
				printf("%c%c+\n", symbols[(i+1) % 4], symbols[(i+2) % 4]);
				printf("%c%c-\n", symbols[i], symbols[(i+1) % 4]);
				printf("%c%c-\n", symbols[(i+2) % 4], symbols[(i+2) % 4 + 4]);
			}
			break;
		}
	}

}