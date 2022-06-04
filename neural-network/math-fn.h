#pragma once

#include "../matrix/matrix-core.h"

double sigmoid(double input);
Matrix *sigmoidPrime(Matrix *m);
Matrix *softMax(Matrix *m);