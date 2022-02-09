# MPI-tutorial

## Useful functions

* Send buffer to receiver
~~~
MPI_Send
~~~
* Starts a standard-mode, nonblocking send. 
~~~
MPI_Isend
~~~
* sending prosecc will be finised if other process has already started receiving
~~~
MPI_Ssend
~~~
* Basic send with user-specified buffering. 
~~~
MPI_Bsend
~~~
* will send buffer if receiver has called MPI_Recv
~~~
MPI_Rsend
~~~
* Blocking test for message
~~~
MPI_Probe
~~~
* barrier
~~~
MPI_Barrier
~~~
* send data from root process to others, other execute called function
~~~
MPI_Bcast
~~~
* send data from root process to others, every receiver has personlised "job" to do
~~~
MPI_Scatter
~~~
* get data from other processes and put in in root process
~~~
MPI_Gather
~~~
* gets data from processes, operates on data and returnes the result in root_rank
~~~
MPI_Reduce
~~~

