#include "mem_new.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
	printf("%d\n", sizeof("4")	);
	for (int i = 0; i < 10000; i++)
	{
		int* a = _malloc(i);
		//printf("%p\n", a);
		*a = i;
	}
	while (true){}
/*	int i;
	while(true)
		i=5;*/


/*	int* a = _malloc(20000);
	*a = 0xADDE;

	short* b = _malloc(100);

	for (int i = 0; i < 50; ++i)
	{
		*(b+i) = i;
	}

	_free(a);

	void* c = _malloc(1234);

	_malloc(50);
	void* d = _malloc(20);

	_free(d);*/

	FILE *f_in = fopen("debug.txt", "w");  
	memalloc_debug_heap(f_in, HEAP_START);
	fclose(f_in);
	
	return 0;
}