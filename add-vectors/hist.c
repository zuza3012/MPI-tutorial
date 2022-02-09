/**
 * @file hist.c
 * @author Zuzanna Wieczorek
 * @brief 
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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


void read_from_file(int *array){
    FILE* file;
    int bufferLength = 255;
    char buffer[bufferLength];
    file = fopen("in.txt", "r");

    int counter = 0;
    while(fgets(buffer, bufferLength, file)) {
        array[counter] = atoi(buffer);
        counter++;
    }
}
int main(int argc, char** argv){
    

    srand (time(0));
    int N = 100;
    int rank, size, root_rank = 0;

    MPI_Init(&argc , &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int portion_size = N / size;
    
    int *send_buff = (int*) malloc(N * sizeof(int));
    int *recv_buff = (int*) malloc(portion_size * sizeof(int));
    float result;
    
    double start, end;
    MPI_Barrier(MPI_COMM_WORLD); 

    if (rank == root_rank) {
        read_from_file(send_buff);        
        
        for(int i = 0; i < N; i++){
            printf("%d\n", send_buff[i]);
        }
        start = MPI_Wtime();
        //printf("Portion = %d\n", portion_size);
        //printf("A[0] A[%d]:\n", N-1);
        
    } 
 
   for(int i = 0; i < portion_size; i++){
       
   }
    
    if(rank == root_rank){
        end = MPI_Wtime();
        
        printf("Runtime = %f\n", end-start);
    }
   
    MPI_Finalize();
    free(send_buff);
    free(recv_buff);
    return 0;
}
