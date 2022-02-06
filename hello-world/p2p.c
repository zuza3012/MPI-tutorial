/**
 * @file p2p.c
 * @author Zuzanna Wieczorek
 * @brief Point to point communication with two processes
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <mpi/mpi.h>

void fill_array(int* array, int N, int rank){
    for(int i = 0; i < N; i++){
        array[i] = rank;
    }
}
void print_array(int* array, int N){
    for(int i = 0; i < N; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char** argv){
     
    int N = 100000;
    int array[N], array_recev[N];
    int size, rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // check if program runs with 2 processes
    if(size != 2 && rank == 0){
        printf("You must run profram on with two processes\n");
        return 1;
    }
    // array containing on every element rank id
    fill_array(array, N, rank);


    if( 0 == rank){
        // buffer, length od buffer + \0, data type, receiver id, tag, communicator
        MPI_Send(array, N, MPI_REAL, 1, 100, MPI_COMM_WORLD);
        printf("Sending to process 1 ... \n");

        // receive rank from process 1, tag 100
        MPI_Recv(array_recev, N, MPI_INT, 1, 100, MPI_COMM_WORLD, &status);
        printf("Receiving from process 1...\n");
        //print_array(array_recev, N);

    } else if (1 == rank){
    
        // buffer, length of buffer (can be smaller), datatype, source, tag, communicator
        MPI_Recv(array_recev, N, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        printf("Receiving from process 0 ...\n");
        //print_array(array_recev, N);

        // send rank to porcess 0, tag 100
        MPI_Send(array, N, MPI_REAL, 0,100,MPI_COMM_WORLD);
        printf("Sending to process 0 ...\n");
    }

    MPI_Finalize();
    return 0;
}