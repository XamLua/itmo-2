#include <stdio.h>
#include <limits.h>
#include "list_definition.h"
#include "list_functions.h"
#include "higher_functions.h"
#include "more_functions.h"

struct list* list;
struct list* list_1;
int number = 0;
int read_count;

int main(int argc, char* argv[])
{
	//output
	read_count = scanf("%d", &number);
	list = list_create(number);
	while(getchar() != '\n'){
		read_count = scanf("%d", &number);
		list_add_front(number, &list);
	}

	foreach(list, output_space);
	printf("\n");

	foreach(list, output_new_line);

	foreach(map(square, list), output_space);
	printf("\n");

	foreach(map(cube, list), output_space);
	printf("\n");

	foreach(map(module, list), output_space);
	printf("\n");

	printf("%ld\n", foldl(0, add, list));

	printf("%ld\n", foldl(INT_MAX, min, list));

	printf("%ld\n", foldl(INT_MIN, max, list));

	foreach(iterate(1, 10, mul_two), output_space);
	printf("\n");

	save(list, "file");
	load(&list_1, "file");
	if (check(list, list_1))
		printf("%s\n", "Equal");
	else
		printf("%s\n", "Not Equal");
	printf("\n");

	serialize(list, "file");
	deserialize(&list_1, "file");
	if (check(list, list_1))
		printf("%s\n", "Equal");
	else
		printf("%s\n", "Not Equal");
	printf("\n");

	free(list);
	free(list_1);
	return 0;
}

