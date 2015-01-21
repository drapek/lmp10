#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>

typedef struct {
		int n; /*wejściowa ilośc punktów*/
		double *x;
		double *y;
} points_t;

int read_pts_failed ( FILE* inf, points_t *pts);
int free_pts ( points_t * pts );
#endif
