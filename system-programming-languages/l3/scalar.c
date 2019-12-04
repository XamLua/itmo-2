 #include <stddef.h>

long result = 0;

int scalar_mul(const int* a, const int* b, size_t length){

	for (size_t i = 0; i < length; ++i) 
		result += a[i] * b[i];

	return result;

}