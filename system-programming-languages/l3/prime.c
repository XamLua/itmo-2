
int prime(long a){
	if (a <= 0) return 2;
	if (a == 1) return 0;

	for (long i = 2; i*i <= a; ++i) {
		if (a % i == 0) 
			return 0;
	}
	return 1;
}