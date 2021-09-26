#!/bin/bash
#SBATCH --output=slurm.out
#SBATCH --nodes=1
#SBATCH --comment="fjkdl"
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

export OMP_NUM_THREADS=8

echo "cpus per node:"
echo $SLURM_JOB_CPUS_PER_NODE

echo " --------------------- "
time ./no-vec
echo " --------------------- "
time ./vec
echo " --------------------- "
time ./for
