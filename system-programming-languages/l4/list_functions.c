#include "list_definition.h"
#include <malloc.h>

struct list* list_create(const int value){

	struct list* new = (struct list*) malloc(sizeof(struct list));
	new->value = value;
	new->next = NULL;
	return new;

}

void list_add_front(const int value, struct list** const list){

	struct list* element = (struct list*) malloc(sizeof(struct list));

	element->value = value;
	element->next = *list;
	*list = element;

}

void list_add_back(const int value, struct list** const list){

	struct list* element = (struct list*) malloc(sizeof(struct list));
	struct list* temp_element = *list;
	element->value = value;
	element->next = NULL;
	while(temp_element->next != NULL)
		temp_element = temp_element->next;
	temp_element->next = element;

}

struct list* list_node_at(struct list* const list, const size_t index){

	size_t temp_index = index;
	struct list* temp_element = list;
	while(temp_index > 0 && temp_element != NULL){
		temp_element = temp_element->next;
		temp_index--;
	}
	if (temp_index != 0)
		return NULL;
	else
		return temp_element;

}

int list_get(const size_t index, struct list* const list){

	struct list* element = list_node_at(list, index);
	if(element == NULL)
		return 0;
	else
		return element->value;

}

void list_free(struct list* list){

	struct list* temp_element_1 = list;
	struct list* temp_element_2;

	while (temp_element_1 != NULL){
		temp_element_2 = temp_element_1->next;
		free(temp_element_1);
		temp_element_1 = temp_element_2;
	}

	list = NULL;

}

size_t list_length(struct list* const list){

	struct list* temp_element = list;
	size_t length = 0;
	while(temp_element != NULL){
		temp_element = temp_element->next;
		length++;
	}
	return length;

}

long int list_sum(struct list* const list){

	struct list* temp_element = list;
	long int sum = 0;
	while(temp_element != NULL)
		sum += temp_element->value;
	return sum;

}