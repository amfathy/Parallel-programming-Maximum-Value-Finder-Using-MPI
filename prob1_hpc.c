#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc , char * argv[]){

    int numperofprocess,rank,chunk,i , idx ;
    int max,mymax,reman,ss ,*arr , *temp , start= 0 ;
    MPI_Status status;
    MPI_Init( &argc , &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numperofprocess);



    if (rank==0){

        printf( "Hello from master process");
        printf("\n");
        printf( "number of slave procees is %d ",numperofprocess);
        printf("\n");
        printf( "please enter array size");
        printf("\n");
        scanf("%d" , &ss);
        printf(  "please enter array elements");
        printf("\n");

        chunk=ss/numperofprocess;
        reman=ss%numperofprocess;


        arr = (int *)malloc(sizeof(int)*ss);
        temp = (int *)malloc(sizeof(int)*chunk);


        for ( i=0 ; i<ss ; i++){
            scanf("%d" ,&arr[i]);
        }

        for( i=0 ; i<chunk ; i++){
            temp[i]=arr[i];
        }

        mymax=temp[0];
        for(i=1;i<chunk;i++){
           if (mymax<temp[i]){
              mymax=temp[i];

                    }
            }

        for(i=1;i<numperofprocess;i++){


             MPI_Send(&ss,1,MPI_INT,i,1,MPI_COMM_WORLD);
             MPI_Send(&chunk,1,MPI_INT,i,1,MPI_COMM_WORLD);
             MPI_Send(arr,ss,MPI_INT,i,1,MPI_COMM_WORLD);

            }



   }

    else{


        MPI_Recv(&ss,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);

        arr = (int *)malloc(sizeof(int)*ss);

        MPI_Recv(&chunk,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);

        temp = (int *)malloc(sizeof(int)*chunk);

        MPI_Recv(arr,ss,MPI_INT,0,1,MPI_COMM_WORLD,&status);

        start = rank * chunk ;

        for( i=start ; i<chunk+start  ; i++){
            temp[i]=arr[i];

        }

        mymax=temp[start];
         int k = 1 ;
        for(i=start ;i<chunk+start ;i++){
           if (mymax<temp[i]){
              mymax=temp[i];
             }
        }

        MPI_Send(&mymax,1,MPI_INT,0,1,MPI_COMM_WORLD);


    }


    if (rank==0){
        //-!!

        printf( "hello from slave# %d max in my partion is %d  " , rank ,mymax  );
        printf("\n");


        max=mymax;

        for(i=1;i<numperofprocess;i++){

        MPI_Recv(&mymax,1,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,&status);


        printf( "hello from slave# %d max  in my partion is %d " , i , mymax );
        printf("\n");


        if (max<mymax){
            max=mymax;
           }
        }

        printf("Master announce the max is: %d   ", max  );
        printf("\n");
        printf("\n");

        printf(" Thanks for using our program " );
        printf("\n");
    }


    MPI_Finalize();
    return 0;
}
