/**
 * @file hello2.c
 * @author Zuzanna Wieczorek
 * @brief Point to point communication
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <mpi/mpi.h>
#include <string.h>

int main(int argc, char** argv){
    // mpicc main.c -o out
    // mpirun -N 4 out
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // process 0 sends to process 1
    // process 1 receives information from process 0
    if (rank == 0) {
        char buffer[50];
        strcpy (buffer, "I like cheese"); // our data to send
        // buffer, length od buffer + \0, data type, receiver id, tag, communicator
        MPI_Send(buffer, strlen(buffer) + 1, MPI_CHAR, 1,0,MPI_COMM_WORLD);
    } else if (rank == 1){
        char buffer[50];
        MPI_Status status;
        // buffer, length of buffer (can be smaller), datatype, source, tag, communicator
        MPI_Recv(buffer, sizeof(buffer), MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("%s", buffer);
    }


    printf("\nHello World, I am proc %d of total %d\n",rank, size);

    MPI_Finalize();
    return 0;
}
