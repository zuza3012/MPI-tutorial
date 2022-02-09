/**
 * @file norm.c
 * @author Zuzanna Wieczorek
 * @brief Program calculating histogram
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
#include <math.h>

void fill_array(float* array, int N){
    
    for(int i = 0; i < N; i++){
        array[i] = (float)rand() / (float)RAND_MAX;
        if ( i == 0 ||i == (N - 1))
            printf("%f ", array[i]);
    }
    printf("\n");
}
int main(int argc, char** argv){
   
    srand (time(0));
    int N = 1024;
    int rank, size, root_rank = 0;

    MPI_Init(&argc , &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int portion_size = N / size;
    
    float *send_buff = (float*) malloc(N * sizeof(float));
    float *recv_buff = (float*) malloc(portion_size * sizeof(float));
    float result;
    
    double start, end;
    MPI_Barrier(MPI_COMM_WORLD); 

    if (rank == root_rank) {
        start = MPI_Wtime();
        printf("Portion = %d\n", portion_size);
        printf("A[0] A[%d]:\n", N-1);
        fill_array(send_buff, N);
        printf("%f %f \n", send_buff[0], send_buff[N-1]);  
    } 
 
    MPI_Scatter(send_buff, portion_size, MPI_FLOAT, recv_buff, portion_size, MPI_FLOAT, root_rank, MPI_COMM_WORLD);
    
    float local_sum = 0;
    for(int i =0; i < portion_size; i++){
        recv_buff[i] = recv_buff[i] * recv_buff[i];
        local_sum+=recv_buff[i];
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Reduce(&local_sum, &result, 1, MPI_FLOAT, MPI_SUM, root_rank, MPI_COMM_WORLD); 

    
    if(rank == root_rank){
        end = MPI_Wtime();
        printf("norm: %f \n", sqrtf(result));
        printf("Runtime = %f\n", end-start);
    }
   
    MPI_Finalize();
    free(send_buff);
    free(recv_buff);
    return 0;
}
