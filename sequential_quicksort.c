#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

void random_int_vector(int* v, int n){

	for (int i = 0; i < n; ++i) {
    	
    	v[i] = rand()%2*n; //generate random integers from 0 to 2*n -1
  }
}


 int main(int argc, char *argv[])
{

	clock_t t;
	
	t = clock();

	int len = pow(2, 20); //lenght of the unsorted list
	int *list = NULL;

	list = malloc(sizeof(int)*len);
		random_int_vector(list, len);

 	//  printf("Unsorted list:\n");  //print the unsorted list

	// for(int i=0; i<len; i++){

	// 	printf("%d  ", list[i]);
	// }
  	


	quicksort(list, 0, len-1);

	// printf("\n\n\nSorted list:\n");  //print the sorted list

	// for(int i=0; i<len; i++)
	// 	printf("%d  ", list[i]);


	t = clock() - t;

	double time = ((double)t)/CLOCKS_PER_SEC; // in seconds

	printf("\n\n\nThat took %f seconds\n",time);


	return 0;
}