#include "list_definition.h"
#include <stddef.h>

struct list* list_create(const int value);
void list_add_front(const int value, struct list** const list);
void list_add_back(const int value, struct list** const list);
int list_get(const size_t index, struct list* const list);
void list_free(struct list* list);
size_t list_length(struct list* const list);
struct list* list_node_at(struct list* const list, const size_t index);
long int list_sum(struct list* const list);