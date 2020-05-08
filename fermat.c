// Author - Michael Ibeh
// This program finds the prime factors of a number
// using Fermat's method and Trial division.

#include <stdio.h>
#include <time.h>
#include <math.h>

// Checks if a given number is prime
int is_prime(long long p){

	int i;

	for(i = 2; i <= p / 2; i++)
		if(p % i == 0)
			return 0; // not prime

	return 1; // is prime
}

// Checks if a number is a perfect square
int perfect_square(long long n){

	long long rootn = sqrt(n);

	if(rootn * rootn == n)
		return 1;

	return 0;
}

int main(void){
	
	int isPrime;
	long long i = 0, j, n, x, y, x2, y2;
	double time;
	clock_t begin, end;

	while(!feof(stdin)) {

		// Read from stdin
		scanf("%lld", &n);

		if (i == n)
			break;

		printf("Trial Division:\t\t");

		begin = clock();

		// Find all Prime factors
	    for(i=2; i<=sqrt(n); i++) {

	        // Check if 'i' is a factor
	        if(n%i==0) {

	            // Check if 'i' is a Prime
	            isPrime = is_prime(i);

				// J is the other factor
				j = n / i;

				// Check if 'j' is a Prime
				isPrime = is_prime(i);

	            // If 'i' and 'j' are prime then we're good
	            if(isPrime==1) {
					end = clock();
					time = (double)(end - begin) / CLOCKS_PER_SEC;
					printf("The factors of %lld are %lld and %lld. This took %lf seconds\n", n, i, j, time);
					break;
	            }
	        }
			else {
				// if the factors are 1 and itself
				if(i == (int)sqrt(n)){
					end = clock();
					time = (double)(end - begin) / CLOCKS_PER_SEC;
					printf("The factors of %lld are 1 and %lld. This took %lf seconds\n", n, n, time);
				}
			}
	    }

		printf("Fermat:\t\t");

		// One of the factors must be at least as great as the square root of n
		x = ceil(sqrt(n));

		// n = (x+y)(x-y)
		// y^2 = x^2 - n

		begin = clock();

		while(1){

			// Setup fermat formula
			x2 = x * x;
			y2 = x2 - n;

			if(perfect_square(y2)){

				y = sqrt(y2);

				end = clock();
				time = (double)(end - begin) / CLOCKS_PER_SEC;

				printf("The factors of %lld are %lld and %lld. This took %lf seconds\n", n, (x-y), (x+y), time);
				fflush(stdout);

				break;
			}

			x++;
		}

		// Don't reread last value
		i = n;
	}

	return 0;
}
