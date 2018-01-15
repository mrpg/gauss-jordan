/*
 * main.c
 *
 * (c) 2018 Max R. P. Grossmann <m@max.pm>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matrix.h"
#include "colors.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: " COLOR(RED, "%s " COLOR(BOLD, "ORDER")) "\n", argv[0]);
		exit(1);
	}
	else {
		size_t dim = atoi(argv[1]);
		double* m = calloc(dim*dim, sizeof(double));

		for (unsigned i = 0; i < dim; i++) {
			for (unsigned j = 0; j < dim; j++) {
				scanf("%lf", matrix_el(m, i, j, dim));
			}
		}


			struct timeval TIME;
			gettimeofday(&TIME, NULL);
			long b = (long)TIME.tv_sec*1000 + (long)TIME.tv_usec/1000;
		matrix_det m2 = matrix_solve(m, dim, false);
			gettimeofday(&TIME, NULL);
			long c = (long)TIME.tv_sec*1000 + (long)TIME.tv_usec/1000;

		if (m2.det != 0) {
			puts("Matrix is " COLOR(GREEN, "regular") ". Inverse:");
			matrix_fprint(stdout, m2.m, dim, dim);
		}
		else {
			puts("Matrix is " COLOR(RED, "singular") ". Final tableau:");
			matrix_fprint(stdout, m2.m, dim, 2*dim);
		}

		fprintf(stderr, "Determinant: " COLOR(GREEN, "%+.6f\n"), m2.det);
		fprintf(stderr, "t = " COLOR(RED, "%+.3f sec\n"), (double)(c-b)/1000);

		free(m);
		free(m2.m);
	}
}
