#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "funkcje_do_legendre.h"

/* silnia */
int factorial (int numb) {
	if(numb <= 1 ) return 1;
    return numb * factorial( numb - 1);
}

/*symbol newotna */
double newton_symbol( int n, int k) {
    if( n >= k )
	   return factorial(n) / (factorial(k) * factorial(n - k));
    else {
	   fprintf(stderr, "[ERROR] Newton Symbol: condition n >= k is not fulfilled\n");
    }
}

/* liczy wartość wielomianu legendrea dla danego stopnia i danej zmiennej x. 
 * Sprawdza czy st. wielomianu > 0 i < 10 dla uzyskania oczekiwanych rezulatów */
double legendre_poly( int n, double x ) {
    if (n < 0 ) {
	   fprintf(stderr, "[ERROR] Program try count legendre poly of negtive number\n");
	   return -1;
    }
    else if (n > 11)
	   n = 11; /* aby nie robić zbyt dokładnej aproksymacji*/
    
    int i;
    double sum;
    for( sum = i = 0; i <= (int) (n/2); i++) 
	   sum += pow(-1, i) * newton_symbol(n, i) * newton_symbol(2*n - 2 * i, n) * pow(x, n - 2*i);

    return (1 / pow(2, n) ) * sum;
}
