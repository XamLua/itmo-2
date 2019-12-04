#include "list_definition.h"

void foreach(struct list* const list, void (*f) (int));
struct list* map(int (*f) (int), struct list* const list);
struct list* map_mut(int (*f) (int), struct list* const list);
long foldl(const int, int (*f) (int, int), struct list* const list);
struct list* iterate(int s, size_t n, int (*f) (int));
