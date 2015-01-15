#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "funkcje_do_legendre.h"

#define MIN_VAL 1 /* określa zakres losowanych wartości które będą przekazywane do funkcji w celu liczenia, np. będzie z tej liczby liczona silnia */
#define MAX_VAL 10

int los();
void test_legendre();
void test_newton();
void test_silnia();

main(int argc, char **argv) {
    int il_test, i, w;

    il_test = (argc > 1) ? atoi(argv[1]) : 10;
    if( il_test < 1 ) 
	   fprintf(stderr, "Given number is inadequate. Number of test must be grater than 0!\n");
    
    srand((int) time(NULL));
    /* main loop of testing */
    for(w = 0; w < il_test; w ++) {
	   for(i = 0; i < 12; i ++ ) {
		  test_silnia(i);
	   	  test_newton(i, i );
		  test_legendre(i, (double) (w));
		  printf("\n");
	   }
	   printf("-------------\n");
    }
    return 0;
}

/* losowanie liczby */
int
los() {
 //   return (int) (MIN_VAL +  (MAX_VAL - MIN_VAL) * ((0.1 * rand()) / RAND_MAX));
    return 3;
}

void test_legendre(int n, double x) {
    printf("n = %i\t x = %f \t legenre = %f\n", n, x, legendre_poly(n, x));
}

void test_newton(int n, int k) {
    printf("n = %i\t k = %d \t symbol_newton = %d\n", n, k, newton_symbol(n, k));
}

void test_silnia(int n) {
    printf("n = %i\t \t fatorial = %i\n", n, factorial(n));    
}

