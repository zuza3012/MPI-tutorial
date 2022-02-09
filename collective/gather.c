/**
 * @file gather.c
 * @author Zuzanna Wieczorek
 * @brief Gather function example
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <mpi/mpi.h>
#include <string.h>


int main(int argc, char** argv){

    int rank, size;
    int root_rank = 0;
    MPI_Init(&argc , &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // check if program runs with 2 processes
    if(size != 4 && root_rank == 0){
        printf("You must run program on with 4 processes\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }
    int send_buff[2] = { rank, rank };
    int recv_buff[8];

    MPI_Gather (send_buff, 2, MPI_INT, recv_buff, 2, MPI_INT, root_rank, MPI_COMM_WORLD);

    if (rank == root_rank) {

        for (int i = 0; i < 8; i++) {
            printf ("recvbuf[%d] = %d  \n", i, recv_buff[i]);
        }  
    } 

    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Finalize();
    return 0;
}
