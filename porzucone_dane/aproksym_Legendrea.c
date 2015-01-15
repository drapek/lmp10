#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* dla funkcji: pow */

#include "makespl.h" /*zawiera opis interfejsu z resztą programu*/

void /*Główna funkcja licząca aproskymacje*/
make_spl(points_t * pts, spline_t * spl) {


}

/* silnia */
int factorial (int numb) {
    return numb * factorial( numb - 1);
}

/*symbol newotna */
double newton_symbol( int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

/* liczy wartość wielomianu legendrea dla danego stopnia i danej zmiennej x. 
 * Sprawdza czy st. wielomianu > 0 i < 10 dla uzyskania oczekiwanych rezulatów */
double legendre_poly( int n, int x ) {
    if (n < 0 ) {
	   fprintf(stderr, "[ERROR] Program try count legendre poly of negtive number\n");
	   return -1;
    }
    else if (n > 10)
	   n = 10; /* aby nie robić zbyt dokładnej aproksymacji*/
    
    int i;
    double sum;
    for( sum = i = 0; i <= (int) (m/2); i++) 
	   sum += pow(-1, i) * newton_symbol(n, i) * newton_symbol(2*n - 2 * i, n) * pow(x, n - 2*i);
    return (1 / pow(2, n) ) * sum;
}
