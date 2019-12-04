#include <stdio.h>
#include <stddef.h>
#include "scalar.h"
#include "prime.h"

const int a[] = {1, 2, 3, 4};
const int b[] = {1, 2, 3, 4};
unsigned long prime_value;
int prime_result;

int main(void){
	int i, j;
	for(i = 0, j = 0; i < 3, j < 3; i++, j++)
		printf("%d %d\n", i, j);

	printf("%ld\n", sizeof int);
	printf("%lu\n", sizeof(int));
	printf("%d\n", *a);

	size_t length = sizeof(a) / sizeof(int);

	printf("%d \n", scalar_mul(a, b, length));	

	printf("%s \n", "Enter the number:");

	if (!scanf("%lu", &prime_value)) {
		fprintf(stderr, "It's not a number\n");
		return 1;
	}

	prime_result = prime(prime_value);

	if (prime_result == 2) 
		printf("%s", "Only natural numbers are allowed\n");
	else if (prime_result)
		printf("%li is a prime value\n", prime_value);
	else
		printf("%li isn't a prime value\n", prime_value);

	return 0;
}