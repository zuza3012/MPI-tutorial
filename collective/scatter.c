/**
 * @file scatter.c
 * @author Zuzanna Wieczorek
 * @brief Scatter function example
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
    if(size != 2 && root_rank == 0){
        printf("You must run program on with 2 processes\n");
        MPI_Finalize();
        return 1;
    }
    int send_buff[4];
    int recv_buff[4];

    if (rank == root_rank) {
        int data[4] = {0, 100, 200, 400};
        memcpy(send_buff, data, sizeof(data));
        printf("Values to scatter from process %d: %d, %d, %d, %d.\n", rank, send_buff[0], send_buff[1], send_buff[2], send_buff[3]);      
    } 
    // root_rank sends data: 0, 100, 200, 400 to 2 processes
    // process 0 receives first two elements from array
    // process 1 receives other two (last elements) 
    // if you want to send every one element to porcess:
    // int recv_data;
    // MPI_Scatter(send_buff, 1, MPI_INT, recv_data, 1, MPI_INT, root_rank, MPI_COMM_WORLD);

    // sending buffer, step, datatype, receiving buffer, datatype, root_rank, comm
    MPI_Scatter(send_buff, 2, MPI_INT, recv_buff, 2, MPI_INT, root_rank, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d received values = %d and %d.\n", rank, recv_buff[0], recv_buff[1]);
    
    MPI_Finalize();
    return 0;
}
