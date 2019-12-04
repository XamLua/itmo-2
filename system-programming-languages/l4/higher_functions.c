#include "list_functions.h"
#include "list_definition.h"
#include <stdio.h>

void foreach(struct list* const list, void (*f) (int)){

	size_t length = list_length(list);
	size_t i;
	for(i = 0; i < length; i++){
		f(list_get(i, list));
	}

}

struct list* map(int (*f) (int), struct list* const list){

	struct list* new_list = list_create(f(list->value));
	size_t i;
	size_t length = list_length(list);	
	for (i = 1; i < length; i++){
		list_get(i, list);
		list_add_back(f(list_get(i, list)), &new_list);
	}
	return new_list;

}

struct list* map_mut(int (*f) (int), struct list* const list){

	struct list* new_list = list_create(f(list->value));
	size_t i;
	struct list* temp_element;
	size_t length = list_length(list);
	list->value = f(list->value);
	for (i = 1; i < length; i++){
		temp_element = list_node_at(list, i);
		temp_element->value = f(temp_element->value); 
		list_add_back(list_get(i, list), &new_list);
	}
	return new_list;

}

long foldl(const int acm, int (*f) (int, int), struct list* const list){

	long temp_acm = acm;
	size_t i;
	size_t length = list_length(list);
	for (i = 0; i < length; i++)
		temp_acm = f(list_get(i, list), temp_acm);
	return temp_acm;

}

struct list* iterate(int s, size_t n, int (*f) (int)){

	struct list* list = list_create(s);
	size_t i;
	int temp_value = s;
	for (i = 0; i < n; i++){
		temp_value = f(temp_value);
		list_add_back(temp_value, &list);
	}
	return list;
}
