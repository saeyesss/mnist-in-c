#include <matrix-operations.h>

#include <stdio.h>
#include <stdlib.h>

// returns 1 if two matrices are compatible for add() et cetera, 0 otherwise
int check_dimensions(Matrix *m1, Matrix *m2)
{
    if (m1->rows == m2->rows && m1->cols == m2->cols)
        return 1;
    return 0;
}

// returns a new matrix with sum of corresponding elements of arg matrices
Matrix *add(Matrix *m1, Matrix *m2)
{
    if (check_dimensions(m1, m2))
    {
        Matrix *m = matrix_create(m1->rows, m1->cols);
        for (int i = 0; i < m1->rows; i++)
        {
            for (int j = 0; j < m2->cols; j++)
            {
                m->entries[i][j] = m1->entries[i][j] + m2->entries[i][j];
            }
        }
        return m;
    }
    else
    {
        printf("Dimension mismatch add: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// returns a new matrix with difference of corresponding elements of arg matrices

Matrix *subtract(Matrix *m1, Matrix *m2)
{
    if (check_dimensions(m1, m2))
    {
        Matrix *m = matrix_create(m1->rows, m1->cols);
        for (int i = 0; i < m1->rows; i++)
        {
            for (int j = 0; j < m2->cols; j++)
            {
                m->entries[i][j] = m1->entries[i][j] - m2->entries[i][j];
            }
        }
        return m;
    }
    else
    {
        printf("Dimension mismatch subtract: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// returns a new matrix with product of corresponding elements of arg matrices
Matrix *multiply(Matrix *m1, Matrix *m2)
{
    if (check_dimensions(m1, m2))
    {
        Matrix *m = matrix_create(m1->rows, m1->cols);
        for (int i = 0; i < m1->rows; i++)
        {
            for (int j = 0; j < m2->cols; j++)
            {
                m->entries[i][j] = m1->entries[i][j] * m2->entries[i][j];
            }
        }
        return m;
    }
    else
    {
        printf("Dimension mistmatch multiply: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// matrix multiplication
Matrix *dot(Matrix *m1, Matrix *m2)
{
    if (m1->cols == m2->rows)
    {
        Matrix *m = matrix_create(m1->rows, m2->cols);
        for (int i = 0; i < m1->rows; i++)
        {
            for (int j = 0; j < m2->cols; j++)
            {
                double sum = 0;
                for (int k = 0; k < m2->rows; k++)
                {
                    sum += m1->entries[i][k] * m2->entries[k][j];
                }
                m->entries[i][j] = sum;
            }
        }
        return m;
    }
    else
    {
        printf("Dimension mistmatch dot: %dx%d %dx%d\n", m1->rows, m1->cols, m2->rows, m2->cols);
        exit(1);
    }
}

// returns a new matrix with some function pointer applied to every element in the matrix
Matrix *apply(Matrix *m, (*func)(double))
{
    Matrix *mat = matrix_copy(m);
    for (int i = 0; i < m1->rows; i++)
    {
        for (int j = 0; j < m2->cols; j++)
        {
            mat->entries[i][j] = (*func)m->entries[i][j];
        }
    }
    return mat;
}

// returns a new matrix by multiplying every element of arg matrices with the scalar
Matrix *scale(Matrix *m, double n)
{
    Matrix *mat = matrix_copy(m);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[i][j] *= n;
        }
    }
    return mat;
}

// returns a new matrix by adding every element of arg matrices with the scalar
Matrix *addScalar(Matrix *m, double n)
{
    Matrix *mat = matrix_copy(m);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[i][j] += n;
        }
    }
    return mat;
}

// returns a new matrix made by exchanging the rows and columns of the arg matrix
Matrix *transpose(Matrix *m)
{
    Matrix *mat = matrix_create(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[j][i] = m->entries[i][j];
        }
    }
    return mat;
}