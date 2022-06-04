#pragma once

#include "matrix-core.h"

Matrix *add(Matrix *m1, Matrix *m2);
Matrix *subtract(Matrix *m1, Matrix *m2);
Matrix *multiply(Matrix *m1, Matrix *m2);
Matrix *dot(Matrix *m1, Matrix *m2);
Matrix *apply(Matrix *m1, double (*func)(double));
Matrix *scale(Matrix *m, double n);
Matrix *addScalar(Matrix *m, double n);
Matrix *transpose(Matrix *m);