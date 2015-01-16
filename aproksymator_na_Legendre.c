#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/* UWAGA: liczbę używanych f. bazowych można ustawić przez wartość
          zmiennej środowiskowej APPROX_BASE_SIZE
*/

/*
 * Funkcje bazowe: n - liczba funkcji, i - numer funkcji x - wspolrzedna dla ktorej obliczana jest wartosc funkcji
 */


double legendre_rek(int i, double x) {
    /*liczy na podstawie przerobnionego wzoru rekurencyjnego z wikipedii */
    if(i == 0) 
	   return 1;
    else if( i == 1) 
	   return x;
    else 
	   return ( 2 * i - 1) * x * legendre_rek(i - 1, x) / i - (i - 1) * legendre_rek(i - 2, x) / i;
}

/* Pierwsza pochodna legendre */
double
poch1_legendre(int i, double x)
{
    if(i == 0) 
	   return 0;
    else if( i == 1) 
	   return 1;
    else
	   return ( 2 * i - 1) * poch1_legendre(i - 1, x) / i - (i - 1) * poch1_legendre(i - 2, x) / i;

}

/* Druga pochodna legendre*/
double
poch2_legendre( int i, double x)
{
    if(i == 0) 
	   return 0;
    else if(i == 1) 
	   return 0;
    else if(i == 2)
	   return 3; /*bo wielomian o indeksie 2, zróżniczkowany dwukrotnie wyniesie 3*/
    else
	   return ( 2 * i - 1) * poch2_legendre(i - 1, x) / i- (i - 1) * poch2_legendre(i - 2, x) / i;

}

/* Trzecia pochodna legendre */
double
poch3_legendre(int i, double x)
{
    if(i == 0) 
	   return 0;
    else if(i == 1) 
	   return 0;
    else if(i == 2)
	   return 0;
    else if(i == 3)
	   return 15;  /*bo wielomian o indeksie 3, zróżniczkowany trzykrotnie wyniesie 15*/
    else
	   return ( 2 * i - 1) * poch3_legendre(i - 1, x) / i - (i - 1) * poch3_legendre(i - 2, x) / i;

}


void
make_spl(points_t * pts, spline_t * spl)
{

	matrix_t	 *eqs= NULL;
	double     *x = pts->x;
	double     *y = pts->y;
	double	 a = x[0]; /*a i b określają w jakim przedziale znajdują się x-y*/
	double	 b = x[pts->n - 1]; 
	int		 i, j, k;
	int		 nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
  	char		 *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv ); /*ustala którego stopnia wielomiany ma użyć*/

	eqs = make_matrix(nb, nb + 1); /*pierwsz parametr to ilość rzedów, a drugi to ilość kolumn*/

	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				/*dodaje do macierzy eqa (na mjsc o  współ wiersz=j, kol=i) kwadrat pochodnej*/
				add_to_entry_matrix(eqs, j, i, legendre_rek( i, x[k]) * legendre_rek(j, x[k]));
				
		for (k = 0; k < pts->n; k++)
			/*dodaje do macierzy eqa, ostatnią kolumnę, która zawiera wyniki równań*/
			add_to_entry_matrix(eqs, j, nb, y[k] * legendre_rek(j, x[k]));
	}

   /*oblicza równania zapisane jako macierz*/
	if (piv_ge_solver(eqs)) {
		spl->n = 0;
		return;
	}

	if (alloc_spl(spl, nb) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = a + i*(b-a)/(spl->n-1);
			xx+= 10.0*DBL_EPSILON;  // zabezpieczenie przed ulokowaniem punktu w poprzednim przedziale
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double  ck = get_entry_matrix(eqs, k, nb);
				spl->f[i]  += ck * legendre_rek  ( k, xx);
				spl->f1[i] += ck * poch1_legendre ( k, xx);
				spl->f2[i] += ck * poch2_legendre ( k, xx);
				spl->f3[i] += ck * poch3_legendre ( k, xx);
			}
		}
	}

}
