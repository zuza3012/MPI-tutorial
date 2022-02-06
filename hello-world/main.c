/**
 * @file main.c
 * @author Zuzanna Wieczorek
 * @brief hello-world in MPI
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <mpi/mpi.h>

int main(int argc, char** argv){
    // mpicc main.c -o out
    // mpirun -N 4 out
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("\nHello World, I am proc %d of total %d\n",rank, size);

    MPI_Finalize();
    return 0;
}