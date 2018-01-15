gauss-jordan
============

This is a naive implementation of the Gauss/Jordan algorithm to invert matrices.
It is reasonably fast and can invert a 2000×2000 matrix in 8.5 seconds. However,
there are faster programs out there. This program was designed to have a very
low memory footprint.

The determinant is calculated with no additional cost during the matrix
inversion.

Compilation
-----------

> make

Usage
-----

Run the program using

> ./matrix [order of matrix]

Then enter the matrix to be inverted. For example, you could do the following:

> ./matrix 3 < example.txt

The matrix in *example.txt* will be inverted and its determinant will be shown.
We also supply a singular matrix in *example2.txt*. If the matrix is singular,
the final Gauss/Jordan tableau is returned. From this final tableau, it follows
trivially that the matrix does not have full rank and as such is not invertible.

Matrices are always entered "by row", to borrow a term from R. For example, the
matrix in the file *example.txt* has the first row 4, 2, 8.

Notes
-----

Due to the diceyness of the == operator as it relates to floating-point numbers,
if the absolute value of a diagonal element is less than 10⁻¹⁰ and there is no
suitable row below it to alleviate the problem using elementary row operations,
the matrix is considered to be singular. You are invited to change this
threshold using line 30 of *matrix.c*.
