/*
 * colors.h
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

#ifndef MATRIX_H
#define MATRIX_H

#define min(a,b) ((a < b) ? a : b)

#define true 1
#define false 0

typedef struct {
	double* m;
	double det;
} matrix_det;

double* matrix_el(double* m, size_t, size_t, size_t);

const double* matrix_el_const(const double* m, size_t, size_t, size_t);

void matrix_fprint(FILE*, const double*, size_t, size_t);

matrix_det matrix_solve(const double*, size_t, _Bool);

#endif
