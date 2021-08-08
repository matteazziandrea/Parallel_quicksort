#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>



int partition(int list[], int lo, int up){

	int ind = (int) (lo + up)/2;
	int p = list[ind];

  	int i = lo - 1;
  	int j = up + 1;

  	while(1){

    	do{
      	
      	i += 1;
    	
    	}while(list[i] < p);

    	do{
      
      		j -= 1;
    
    	}while(list[j] > p);

    if(i >= j)
    	return j;

    int buffer = list[i];
    list[i] = list[j];
    list[j] = buffer;
  }
}


void quicksort(int list[], int lo, int up){

  if(lo < up){
    
  	int p = partition(list, lo, up);
    quicksort(list, lo, p);
    quicksort(list, p + 1, up);
  }
}


void merge(int a[], int m, int b[], int n, int sorted[]) {
  int i, j, k;

  j = k = 0;

  for (i = 0; i < m + n;) {
    if (j < m && k < n) {
      if (a[j] < b[k]) {
        sorted[i] = a[j];
        j++;
      }
      else {
        sorted[i] = b[k];
        k++;
      }
      i++;
    }
    else if (j == m) {
      for (; i < m + n;) {
        sorted[i] = b[k];
        k++;
        i++;
      }
    }
    else {
      for (; i < m + n;) {
        sorted[i] = a[j];
        j++;
        i++;
      }
    }
  }
}


void random_int_vector(int* v, int n){

	for (int i = 0; i < n; ++i) {
    	
    	v[i] = rand()%2*n; //generate random integers from 0 to 2*n - 1
  }
}


void arr_copy(int arr[], int sub[], int p, int len){

	for(int i=0; i<len; i++){

		sub[i] = arr[i+p];
	}
}


int main(int argc, char *argv[]) {

  int rank, size;	
  const int root = 0; // the master rank that holds A to begin with
  int tag = 1234;

  double t0, t1, time;

  
  MPI_Init(&argc, &argv);

  t0 = MPI_Wtime ();
 

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);	


	int len = pow(2, 20); //lenght of the unsorted list
	int *list = NULL;

  if (rank == root) {

    // creates and fill with random values an array of int
    list = malloc(sizeof(int)*len);
		random_int_vector(list, len);

    // printf("Unsorted list:\n"); //print the unsorted list

		// for(int i=0; i<len; i++){

		// 	printf("%d  ", list[i]);
		// }

  	}

	int count = len/size; 
 	int *localList = malloc(sizeof(int)*count);


 	MPI_Scatter(list, count, MPI_INT, localList, count, MPI_INT, root, MPI_COMM_WORLD);

  quicksort(localList, 0, count-1);

   

  if(rank == root){
        
    int buffer[len];

    MPI_Gather(localList, count, MPI_INT, buffer, count, MPI_INT, root, MPI_COMM_WORLD);


    int *a = malloc(count*sizeof(int));
  	int *b = malloc(count*sizeof(int));
  	int *sorted = malloc(2*count*sizeof(int));

		arr_copy(buffer, a, 0, count);

    	
    for(int i = 1; i<size; i++){

      arr_copy(buffer, b, i*count, count);

    	merge(a, i*count, b, count, sorted);

    	a = sorted;

    	sorted = malloc((2+i)*count*sizeof(int));


    }

    //  printf("\n\n\nSorted list:\n");  //print the sorted list

    // for(int i=0; i<len; i++){
		
		// printf("%d  ", a[i]);
  	
    //  }

	
	}
        
  else{
        
     MPI_Gather(localList, count, MPI_INT, NULL, 0, MPI_INT, root, MPI_COMM_WORLD);

  }


  t1 = MPI_Wtime ();
  time = (t1 - t0);

  printf("\n\n\nProcessor %d took %f seconds\n",rank,time);

  
  MPI_Finalize();
  return 0;

}
