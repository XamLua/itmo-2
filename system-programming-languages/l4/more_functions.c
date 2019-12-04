#include <stdbool.h>
#include <stdio.h>
#include "list_functions.h"
#include "list_definition.h"

bool save(struct list* lst, const char* filename){

	size_t length;
	size_t i;
	FILE* file = fopen(filename, "w");
	if(file){
		length = list_length(lst);
		for (int i = 0; i < length; i++) 
			fprintf(file, "%d ", list_get(i, lst));
		fclose(file);
		return true;
	} 
	else{
		fclose(file);
		printf("Error occurs while file opening");
		return false;
	}
}

bool load(struct list** lst, const char* filename){

	FILE* file = fopen(filename, "r");
	int value;
	fscanf(file, "%d", &value);
	*lst = list_create(value);
	while (!feof(file) && fscanf(file, "%d", &value) == 1){
		list_add_back(value, lst);
	}
	fclose(file);
	return true;

}

bool serialize(struct list* lst, const char* filename){

	size_t length;
	size_t i;
	int value;
	FILE* file = fopen(filename, "wb");
	if(file){
		length = list_length(lst);
		for (int i = 0; i < length; i++){ 
			value = list_get(i, lst);
			fwrite(&value, sizeof(int), 1, file);
		}
		fclose(file);
		return true;
	} 
	else{
		fclose(file);
		printf("Error occurs while file opening");
		return false;
	}

}

bool deserialize(struct list** lst, const char* filename){

	FILE* file = fopen(filename, "r");
	int value;
	fread(&value, sizeof(int), 1, file);
	*lst = list_create(value);
	while (!feof(file) && fread(&value, sizeof(int), 1, file) == 1)
		list_add_back(value, lst);
	fclose(file);
	return true;

}

void output_space(int s){
	fprintf(stdout, "%d ", s);
	fflush(stdout);
}

void output_new_line(int s){
	fprintf(stdout, "%d\n", s);
	fflush(stdout);
}

int square(int s){
	return s*s;
}

int cube(int s){
	return s*s*s;
}

int module(int s){
	if (s > 0)
		return s;
	else
		return -s;
}

int mul_two(int s){
	return 2*s;
}

int add(int a, int b){
	return a+b;
}

int min(int a, int b){
	if (a < b)
		return a;
	else
		return b;
}

int max(int a, int b){
	if (a > b)
		return a;
	else
		return b;
}

bool check(struct list* a, struct list* b){
	size_t i;
	size_t length = list_length(a);

	if (length != list_length(b))
		return false;

	for (i = 0; i < length; i++){
		if (list_get(i, a) != list_get(i, b))
			return false;
	}
	
	return true;
}