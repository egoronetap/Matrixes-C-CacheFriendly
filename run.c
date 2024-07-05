#include <stdio.h>
#include <stdlib.h>


int** allocate_2d_array(int rows, int cols) {
    int **array = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        array[i] = (int *)malloc(cols * sizeof(int));
    }

    return array;
}


void free_2d_array(int **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

void print_matrix(int **mas, int row, int col){
    for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                printf("%d ", mas[i][j]);
            }
            printf("\n");
        }
}

void scan_matrix(int **mas, int row, int col){
    for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                scanf("%d", &mas[i][j]);
            }
        }
}

void input_random(int **mas, int row, int col){
    for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mas[i][j] = rand() % 10;
            }
        }
}

void multiply_matrices(int *A, int *B, int *C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

int** readMatrixFromFile(const char* filename, int rows, int cols, int **mas) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &mas[i][j]);
        }
    }

    fclose(file);
}


void addMatrix(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int **A, int **B, int **C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;

    int **A11 = allocate_2d_array(newSize, newSize);
    int **A12 = allocate_2d_array(newSize, newSize);
    int **A21 = allocate_2d_array(newSize, newSize);
    int **A22 = allocate_2d_array(newSize, newSize);
    int **B11 = allocate_2d_array(newSize, newSize);
    int **B12 = allocate_2d_array(newSize, newSize);
    int **B21 = allocate_2d_array(newSize, newSize);
    int **B22 = allocate_2d_array(newSize, newSize);
    int **C11 = allocate_2d_array(newSize, newSize);
    int **C12 = allocate_2d_array(newSize, newSize);
    int **C21 = allocate_2d_array(newSize, newSize);
    int **C22 = allocate_2d_array(newSize, newSize);
    int **M1 = allocate_2d_array(newSize, newSize);
    int **M2 = allocate_2d_array(newSize, newSize);
    int **M3 = allocate_2d_array(newSize, newSize);
    int **M4 = allocate_2d_array(newSize, newSize);
    int **M5 = allocate_2d_array(newSize, newSize);
    int **M6 = allocate_2d_array(newSize, newSize);
    int **M7 = allocate_2d_array(newSize, newSize);
    int **AResult = allocate_2d_array(newSize, newSize);
    int **BResult = allocate_2d_array(newSize, newSize);


    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    addMatrix(A11, A22, AResult, newSize);
    addMatrix(B11, B22, BResult, newSize);
    strassen(AResult, BResult, M1, newSize);

    addMatrix(A21, A22, AResult, newSize);
    strassen(AResult, B11, M2, newSize);

    subtractMatrix(B12, B22, BResult, newSize);
    strassen(A11, BResult, M3, newSize);

    subtractMatrix(B21, B11, BResult, newSize);
    strassen(A22, BResult, M4, newSize);

    addMatrix(A11, A12, AResult, newSize);
    strassen(AResult, B22, M5, newSize);

    subtractMatrix(A21, A11, AResult, newSize);
    addMatrix(B11, B12, BResult, newSize);
    strassen(AResult, BResult, M6, newSize);

    subtractMatrix(A12, A22, AResult, newSize);
    addMatrix(B21, B22, BResult, newSize);
    strassen(AResult, BResult, M7, newSize);

    addMatrix(M1, M4, AResult, newSize);
    subtractMatrix(AResult, M5, BResult, newSize);
    addMatrix(BResult, M7, C11, newSize);

    addMatrix(M3, M5, C12, newSize);

    addMatrix(M2, M4, C21, newSize);

    subtractMatrix(M1, M2, AResult, newSize);
    addMatrix(AResult, M3, BResult, newSize);
    addMatrix(BResult, M6, C22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    free_2d_array(A11, newSize);
    free_2d_array(A12, newSize);
    free_2d_array(A21, newSize);
    free_2d_array(A22, newSize);
    free_2d_array(B11, newSize);
    free_2d_array(B12, newSize);
    free_2d_array(B21, newSize);
    free_2d_array(B22, newSize);
    free_2d_array(C11, newSize);
    free_2d_array(C12, newSize);
    free_2d_array(C21, newSize);
    free_2d_array(C22, newSize);
    free_2d_array(M1, newSize);
    free_2d_array(M2, newSize);
    free_2d_array(M3, newSize);
    free_2d_array(M4, newSize);
    free_2d_array(M5, newSize);
    free_2d_array(M6, newSize);
    free_2d_array(M7, newSize);
    free_2d_array(AResult, newSize);
    free_2d_array(BResult, newSize);
}
