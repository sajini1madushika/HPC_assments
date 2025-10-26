#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix *allocateMatrix(int rows, int cols) {
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
        mat->data[i] = (double *)malloc(cols * sizeof(double));
    return mat;
}

void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++)
        free(mat->data[i]);
    free(mat->data);
    free(mat);
}

int readMatricesFromFile(const char *filename, Matrix ***matrices) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("error opening file");
        return 0;
    }

    int rows, cols;
    int count = 0;
    Matrix **temp = NULL;

    while (fscanf(fp, "%d,%d", &rows, &cols) == 2) {
        Matrix *mat = allocateMatrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (fscanf(fp, "%lf,", &mat->data[i][j]) != 1) {
                    printf("error reading data for matrix %d\n", count + 1);
                    fclose(fp);
                    return count;
                }
            }
        }
        temp = realloc(temp, (count + 1) * sizeof(Matrix *));
        temp[count++] = mat;
    }

    fclose(fp);
    *matrices = temp;
    return count;
}

void writeMatrixToFile(FILE *fp, Matrix *mat) {
    fprintf(fp, "%d,%d\n", mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fprintf(fp, "%lf", mat->data[i][j]);
            if (j < mat->cols - 1) fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
}
