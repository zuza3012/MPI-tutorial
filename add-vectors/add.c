/**
 * @file add.c
 * @author Zuzanna Wieczorek
 * @brief Adding two vectors in MPI
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <mpi/mpi.h>
#include <string.h>

void fill_array(int* array, int N){
    for(int i = 0; i < N; i++){
        array[i] = i;
    }
}
int main(int argc, char** argv){
    int N = 4; //1048576;
    int rank, size;
    int a[N], b[N], c[N];

    fill_array(a, N);
    fill_array(b, N);

    int portion = N / size;
    printf("Portion = %d\n", portion);

    MPI_Init(&argc , &argv);
    

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    double start;

    if (rank == 0) {
        start = MPI_Wtime();
        char buffer[50];
        strcpy (buffer, "I like cheese"); // our data to send
        // buffer, length od buffer + \0, data type, receiver id, tag, communicator
        MPI_Send(buffer, strlen(buffer) + 1, MPI_CHAR, 1,0,MPI_COMM_WORLD);
    } else if (rank == 1){
        start = MPI_Wtime();
        char buffer[50];
        MPI_Status status;
        // buffer, length of buffer (can be smaller), datatype, source, tag, communicator
        MPI_Probe (MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        
        // get info about incoming message
        printf ("Odbieramy komunikat od procesu nr %d z etykieta %d\n", status.MPI_SOURCE, status.MPI_TAG);
        MPI_Recv(buffer, sizeof(buffer), MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("%s", buffer);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    double stop = MPI_Wtime();
    double elapsed = stop - start;
    printf("Elapsed process %d = %f\n", rank, elapsed);
    
    
    
   
    MPI_Finalize();
    return 0;
}
