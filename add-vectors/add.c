/**
 * @file add.c
 * @author Zuzanna Wieczorek
 * @brief Adding two vectors in MPI
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <mpi/mpi.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void fill_array(float* array, int N){
    
    for(int i = 0; i < N; i++){
        array[i] = (float)rand() / (float)RAND_MAX;
        if ( i == 0 ||i == (N - 1))
            printf("%f ", array[i]);
    }
    printf("\n");
}
int main(int argc, char** argv){
    // current time as seed
    srand (time(0));

    int N = 1048576;
    int rank, size, root_rank = 0;

    MPI_Init(&argc , &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int portion_size = N / size;
    
    float *send_buff_1 = (float*) malloc(N * sizeof(float));
    float *send_buff_2 = (float*) malloc(N * sizeof(float));
    float *recv_buff_1 = (float*) malloc(portion_size * sizeof(float));
    float *recv_buff_2 = (float*) malloc(portion_size * sizeof(float));
    float *send_buff_3 = (float*) malloc(portion_size * sizeof(float));
    float *result = (float*) malloc(N * sizeof(float));

    double start, end;
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == root_rank) {
        start = MPI_Wtime();
        printf("Portion = %d\n", portion_size);
        printf("A[0] A[%d]:", N-1);
        fill_array(send_buff_1, N);
        printf("B[0] B[%d]:", N-1);
        fill_array(send_buff_2, N);    
    } 
 
    MPI_Scatter(send_buff_1, portion_size, MPI_FLOAT, recv_buff_1, portion_size, MPI_FLOAT, root_rank, MPI_COMM_WORLD);
    MPI_Scatter(send_buff_2, portion_size, MPI_FLOAT, recv_buff_2, portion_size, MPI_FLOAT, root_rank, MPI_COMM_WORLD);

    for(int i =0; i < portion_size; i++){
        send_buff_3[i] = recv_buff_1[i] + recv_buff_2[i];
    }
    MPI_Gather(send_buff_3, portion_size, MPI_FLOAT, result,portion_size,MPI_FLOAT, root_rank, MPI_COMM_WORLD );

    MPI_Barrier(MPI_COMM_WORLD);
   
    if(rank == root_rank){
        end = MPI_Wtime();
        printf("C[0]=%f \n", result[0]);
        printf("C[%d]=%f \n", N-1,result[N-1]);
        printf("Runtime = %f\n", end-start);
    }
   
    MPI_Finalize();

    free(send_buff_1);
    free(send_buff_2);
    free(send_buff_3);
    free(recv_buff_1);
    free(recv_buff_2);
    free(result);

    return 0;
}
