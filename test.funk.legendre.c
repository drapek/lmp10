#include <stdio.h>
#include <math.h>

double
legendre(int i, double x)
{
   /*wersja licząca na 100 % dobre wielomiany*/
    switch(i) {
	    case 0: return 1.0;
	    case 1: return x;
	    case 2: return (3 * x * x - 1) / 2;
	    case 3: return (5 * pow(x, 3) - 3 * x) / 2 ;
	    case 4: return (35 * pow(x, 4) - 30 * x * x + 3) / 8;
	    case 5: return (63 * pow(x, 5) - 70 * pow(x, 3) + 15 * x) / 8;
	    case 6: return (231 * pow(x, 6)- 315 * pow(x, 4) + 105 * x * x - 5) / 16;
	    case 7: return (429 * pow(x, 7) - 693 * pow(x, 5) + 315 * pow(x, 3) - 35 * x ) / 16;
	    case 8: return (6435 * pow(x, 8) - 12012 * pow(x, 6) + 6930 * pow(x, 4) - 1260 * x * x + 35) / 128;
	    case 9: return (12155 * pow(x, 9) - 25740 * pow(x, 7) + 18018 * pow(x, 5) - 4620 * (x, 3) + 315 * x) / 128;
	   case 10: return (46189 * pow(x, 10) - 109395 * pow(x, 8) + 90090 * pow(x, 6) - 30030 * pow(x, 4) + 3465 * x * x - 63) / 256;
	   case 11: return (88179 * pow(x, 11) - 230945 * pow(x, 9) + 218790 * pow(x, 7) - 90090 * pow(x, 5) + 15015 * pow(x, 3) - 693 * x) / 256;
	   default: return 1.0; // tak w razie czego...
    }
 }

double legendre_rek(int i, double x) {
    /*liczy na podstawie przerobnionego wzoru rekurencyjnego z wikipedii */
    if(i == 0) 
	   return 1;
    else if( i == 1) 
	   return x;
    else 
	   return ( 2 * i - 1) * x * legendre_rek(i - 1, x) / i - (i - 1) * legendre_rek(i - 2, x) / i;
}

int
main(int argc, char **argv) {
    int i, x;
    /*obsługa parametrów wejściowych*/
    x = (argc > 1 ? atoi(argv[1]) : 1); /*określa wartość x */

    /*pętla porównująca funkcie legendre i legendre_rek*/
    for(i = 0; i < 12; i++) {
	   double legen     = legendre(i, x);
	   double legen_rek =  legendre_rek(i, x);

	   printf("Legen = %f\t legen_rek = %f\t [%s] \n", legen, legen_rek, legen == legen_rek ? "OK" : "#ERR#");	   
    }

    return 0;
}
