#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "run.c"

int main(){
    // printf("Choose the way to output matrix:\n1)File\n2)Console\nInput the number: ");
    // int var1;
    // scanf("%d", &var1);

    // if (var1 < 1 || var1 > 2){
    //     printf("Incorrect number\n");
    //     return 0;
    // }


    int first_row, first_col;
    printf("Input matrix size: ");
    scanf("%d", &first_row);
    printf("\n");

    first_col = first_row;
    int **first_mat = allocate_2d_array(first_row, first_col);


    int second_row, second_col;

    second_col = second_row = first_col;
    int **second_mat = allocate_2d_array(second_row, second_col);
    int N = second_col;
    srand(time(NULL));

    int *A = (int *)malloc(N * N * sizeof(int));
    int *B = (int *)malloc(N * N * sizeof(int));
    int *C = (int *)malloc(N * N * sizeof(int));

    input_random(first_mat, first_row, first_col);
    input_random(second_mat, second_row, second_col);


    int **result = allocate_2d_array(first_col, second_row);
    for (int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			A[i*N+j]=first_mat[i][j];
			B[i*N+j]=second_mat[i][j];
		}
	}  

    clock_t start = clock();

    
    multiply_matrices(A, B, C, N);


    clock_t finish = clock();
    double timee = (double)(finish - start) / CLOCKS_PER_SEC;


    // if (var1 == 2){
    //     printf("Final matrix\n");
    //     print_matrix(result, first_col, second_row);
    // }

    // if (var1 == 1){
    //     FILE * file = fopen("output.txt", "w");
    //     for (int i = 0; i < first_col; i++){
    //         for (int j = 0; j < second_row; j++){
    //             fprintf(file, "%d ", result[i][j]);
    //         }
    //         fprintf(file, "\n");
    //     }
    // }

    free_2d_array(first_mat, first_row);
    free_2d_array(second_mat, second_row);
    free_2d_array(result, second_row);
    free(A);
    free(B);
    free(C);
    printf("%f", timee);

}