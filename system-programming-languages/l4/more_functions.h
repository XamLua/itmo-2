#include <stdbool.h>
#include "list_functions.h"
#include "list_definition.h"

bool save(struct list* lst, const char* filename);
bool load(struct list** lst, const char* filename);
bool serialize(struct list* lst, const char* filename);
bool deserialize(struct list** lst, const char* filename);
void output_space(int s);
void output_new_line(int s);
int square(int s);
int cube(int s);
int module(int s);
int mul_two(int s);
int add(int a, int b);
int min(int a, int b);
int max(int a, int b);
bool check(struct list* a, struct list* b);