#include <stdio.h>
#include <mpi/mpi.h>

int main(int argc, char **argv){
    // process 0 will receive data from all other processes
    // data is a numer of senders rank
    // process 0 will print received data
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if ( 0 != rank ){
        // sending data
        int buf[1];
        buf[0] = rank;
        MPI_Send(buf, 1, MPI_INT, 0, 333,MPI_COMM_WORLD);  
         
    } else {
        // rank 0  will receive data
        
        for (int i = 1; i < size; i++){
            int buf[1];
            // MPI_INT,MPI_ANY_SOURCE can be replaced with variable i
            MPI_Recv(buf, 10, MPI_INT,MPI_ANY_SOURCE, 333, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Received %d from rank %d\n", buf[0], i);
        }
    }

    MPI_Finalize();
    return 0;
}
