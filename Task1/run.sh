#!/bin/bash
#SBATCH --output=slurm.out
#SBATCH --nodes=1
#SBATCH --comment="fjkdl"
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=24

srun ./o
