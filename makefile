targets: sequential_quicksort.c parallel_quicksort.c
	gcc -O2 sequential_quicksort.c -o sequential_quicksort.o
	mpicc -O2 parallel_quicksort.c -o parallel_quicksort.o