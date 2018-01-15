/*
 * matrix.c
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
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define SINGULARITY 1e-10

double* matrix_el(double* m, size_t row, size_t col, size_t cols) {
	return m+row*cols+col;
}

const double* matrix_el_const(const double* m, size_t row, size_t col, size_t cols) {
	return m+row*cols+col;
}

void matrix_fprint(FILE* stream, const double* m, size_t rows, size_t cols) {
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			printf("% .6f ", *matrix_el_const(m, i, j, cols));
		}
		putchar('\n');
	}

	puts("");
}

matrix_det matrix_solve(const double* m, size_t dim, _Bool only_determinant) {
	/* returns final tableau and determinant 0 if matrix is singular
	 * (see SINGULARITY above) or inverse and determinant ≠ 0 if
	 * matrix is regular */

	matrix_det gj;
	double tmp, tmp2;
	size_t subst;

	gj.m = calloc(dim*2*dim, sizeof(double));
	gj.det = NAN;

	for (size_t ij = 0; ij < dim; ij++) { // initialize tableau
		memcpy(matrix_el(gj.m, ij, 0, 2*dim), matrix_el_const(m, ij, 0, dim), dim*sizeof(double));

		*matrix_el(gj.m, ij, ij+dim, 2*dim) = 1;
	}

	for (size_t j = 0; j < dim; j++) { // create upper triangular matrix
		while (fabs(tmp = *matrix_el(gj.m, j, j, 2*dim)) < SINGULARITY) {
			for (subst = j+1; subst < dim; subst++) {
				if (fabs(*matrix_el(gj.m, subst, j, 2*dim)) > SINGULARITY) break;
			}

			if (subst < dim) {
				for (size_t jj = 0; jj < 2*dim; jj++) {
					*matrix_el(gj.m, j, jj, 2*dim) += *matrix_el(gj.m, subst, jj, 2*dim);
				}

				tmp = *matrix_el(gj.m, j, j, 2*dim);
			}
			else {
				gj.det = 0; // matrix is likely singular

				return gj;
			}
		}

		for (size_t ji = j+1; ji < dim; ji++) {
			tmp2 = *matrix_el(gj.m, ji, j, 2*dim);

			memset(matrix_el(gj.m, ji, 0, 2*dim), 0, min(ji,j)*sizeof(double));

			for (size_t jij = min(ji,j); jij < 2*dim; jij++) {
				*matrix_el(gj.m, ji, jij, 2*dim) -= (tmp2/tmp) * *matrix_el(gj.m, j, jij, 2*dim);
			}
		}
	}

	gj.det = 1;

	for (size_t ij = 0; ij < dim; ij++) { // calculate determinant
		gj.det *= (tmp = *matrix_el(gj.m, ij, ij, 2*dim));

		if (!only_determinant) { // make diagonal of triangular matrix equal to 1
			for (size_t ijj = ij; ijj < 2*dim; ijj++) {
				*matrix_el(gj.m, ij, ijj, 2*dim) /= tmp;
			}
		}
	}

	if (only_determinant) return gj;

	for (size_t i = dim-2;; i--) { // create unit matrix, discard left side of tableau
		for (size_t ij = dim-1; ij > i; ij--) {
			tmp = *matrix_el(gj.m, i, ij, 2*dim);

			for (size_t ijj = dim; ijj < 2*dim; ijj++) {
				*matrix_el(gj.m, i, ijj, 2*dim) -= tmp * *matrix_el(gj.m, ij, ijj, 2*dim);
			}

		}

		if (i == 0) break;
	}

	double* gj2 = malloc(dim*dim*sizeof(double)); // return only the right side of the tableau

	for (size_t i = 0; i < dim; i++) {
		memcpy(matrix_el(gj2, i, 0, dim), matrix_el(gj.m, i, dim, 2*dim), dim*sizeof(double));
	}

	free(gj.m);
	gj.m = gj2;

	return gj;
}
