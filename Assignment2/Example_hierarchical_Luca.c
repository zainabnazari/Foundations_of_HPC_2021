#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

​

​

#if defined(DEBUG)
#define dprintf(...) printf(__VA_ARGS__);
#else
#define dprintf(...)
#endif

​

typedef unsigned int uint;  //defines shortcut for unsigned integers

int Me, Ntasks;
int message( int, int, int, uint * );

int main ( int argc, char **argv ) {


  MPI_Init( &argc, &argv );

​

  MPI_Comm_size( MPI_COMM_WORLD, &Ntasks );

  MPI_Comm_rank( MPI_COMM_WORLD, &Me );

​

  uint N = ( argc > 1? atoi(*(argv+1)) : 1000000 );

  uint *data = NULL;

​

  if ( Me == 0 )

      data = (uint*)calloc( N, sizeof(int) );  //allocate the data on the heap


  message( 0, Ntasks, N, data ); // 0 identified the rank of the target of the message
                                 // N are the elements in the sent data

​

  if( data != NULL )

      free( data );



  MPI_Finalize();

  return 0;

}

​

#define TAG_N 0
#define TAG_DATA 1

​

int message( int target, int group_size, int N, uint *data )

{

  typedef struct { int N, size; } work_t;

  work_t work = { N, group_size };

  uint *mydata = data;

  int myN = N;

  int myNtasks = group_size;

​

  if ( Me != target )
  {
      MPI_Status status;
      dprintf("[@] Task %d waiting for first ping\n", Me ); //Me is the rank of the waiting proc
      fflush(stdout);
      MPI_Recv( &work, sizeof(work_t), MPI_CHAR, MPI_ANY_SOURCE, TAG_N, MPI_COMM_WORLD, &status );
      dprintf( "\t[-] Task %d has received first ping from task %d (data: %d, %d)\n", Me, status.MPI_SOURCE, work.N, work.size );

      if ( work.N > 0 ) {

          mydata = (uint*)calloc( work.N, sizeof(uint) );
          MPI_Recv( mydata, work.N, MPI_INT, status.MPI_SOURCE, TAG_DATA, MPI_COMM_WORLD, &status );
          printf( "\t[+] Task %d has received %d data from task %d; last task is %d\n",
       	  Me, work.N, status.MPI_SOURCE, Me+work.size-1 );
      }

      myN = work.N;
      myNtasks = work.size;

  }

  if ( myN > 0 )
  {
      dprintf( "\t[.] Task %d checking %d data\n", Me, myN );
      unsigned int fails = 0;
      for ( uint j=0; j<myN; j++ )
          fails += ( mydata[j] != Me );
      if ( fails )
         printf("\t\t>>> Task %d noticed %u fails in its data\n", Me, fails );

      MPI_Request *requests = NULL;
      int nreq = 0;
      if ( myNtasks > 1 )
      {

	  work_t work;

	  int n = myNtasks;

	  nreq = 1;

	  while( (n >>= 1) > 0 )

	    nreq++;

	  requests = (MPI_Request*)malloc( sizeof(MPI_Request) * nreq );

	  for( int r = 0; r < nreq; r++ )

	    requests[r] = MPI_REQUEST_NULL;

	  dprintf("\t[R] Task %d has made room for %d requests having %d tasks\n",

		  Me, nreq, myNtasks);

​



	  if ( myNtasks % 2 )

	    {

	      dprintf("[0] Task %d level %d : signalling to task %d that "

		      " it must return with no data\n",

		      Me, n, Me+myNtasks-1 );

	      work.N = 0;

	      MPI_Isend( &work, sizeof(work_t), MPI_CHAR, Me+myNtasks-1, TAG_N, MPI_COMM_WORLD, &requests[nreq-1] );

	      myNtasks--;

	    }



	  n = 0;

	  while ( myNtasks > 1 )

	    {

	      int trg = Me + myNtasks/2 + (myNtasks % 2);

	      int N_tobe_sent = myN - myN/2;

​

	      for ( int j = myN/2; j<myN; j++ )

		mydata[j] = trg;

​

	      dprintf("[*] Task %d level %d : Ntasks %d target %d "

		      "    sending %d data to target with Ntasks %d\n",

		      Me, n, myNtasks, trg,

		      N_tobe_sent, Me + myNtasks - trg); fflush(stdout);

​

	      work_t work = {N_tobe_sent, Me + myNtasks - trg };

	      MPI_Send( &work, sizeof(work_t), MPI_CHAR, trg, TAG_N, MPI_COMM_WORLD );

	      MPI_Isend( &mydata[myN/2], N_tobe_sent, MPI_INT, trg, TAG_DATA, MPI_COMM_WORLD, &requests[n] );

	      printf("[S] Task %d has sent %d data to task %d with limit %d\n",

		     Me, N_tobe_sent, trg, Me + myNtasks - trg );

​

	      myNtasks = trg - Me;

​

	      myN = myN/2;

	      n++;

​

	      dprintf("[C] Task %d continues with %d Ntasks and %u data\n",

		      Me, myNtasks, myN );

	    }

​

	  dprintf("[@] Task %d is waiting for all the %d communications to complete\n",

		  Me, nreq); fflush(stdout);

	  if( nreq > 0 )

	    {

	      MPI_Status *statuses = (MPI_Status*)malloc(sizeof(MPI_Status)*nreq);

	      MPI_Waitall( nreq, requests, statuses);



	      free( statuses );

	      free( requests );

	    }

​

	  if( mydata != data )

	    free(mydata);



        }

      else
      {
        printf("[W] Task %d is doing something on its own data\n", Me );
      }

​

    }

​

  else

    {

      dprintf("[@] Task %d is returning with no data\n", Me );

    }

​

  MPI_Barrier(MPI_COMM_WORLD);

​

  return 0;

}
