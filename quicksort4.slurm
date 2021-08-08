#!/bin/bash
#SBATCH --job-name MPI_quicksort
#SBATCH --output out_%j.txt
#SBATCH --error errors_%j.txt
#SBATCH --mail-user andrea.matteazzi.2@studenti.unipd.it
#SBATCH --mail-type ALL
#SBATCH --ntasks 4
#SBATCH --partition allgroups
#SBATCH --time 12:00:00
#SBATCH --mem 50G

spack load intel-parallel-studio@professional.2019.4
mpirun -np 4 ./parallel_quicksort.o