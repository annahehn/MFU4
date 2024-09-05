#!/bin/bash -l  
#SBATCH --job-name=wB97X2TZclxe20
#SBATCH --time=24:00:00
#SBATCH --nodes=512
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=3
#SBATCH --cpus-per-task=4
#SBATCH --partition=normal
#SBATCH --constraint=gpu
#SBATCH --account=s1195
#SBATCH --hint=nomultithread

#the cp2k exectuable was compiled with this arch file

module add daint-gpu
module rm PrgEnv-cray
module add PrgEnv-gnu
module rm gcc
module add gcc/9.3.0
module add cray-fftw/3.3.8.10
module add cudatoolkit

source /scratch/snx3000/ahehn/cp2k_master_9nov/tools/toolchain/install/setup

#source /scratch/snx3000/ahehn/cp2k_march14/arch/CRAY-XC50-gnu.psmp

#the next 2 lines are there to use the GPU version of libsci (can be commented)
#module load cray-libsci/20.09.1
module load cray-libsci_acc
#module load cray-libsci/20.09.1

#export MPICH_OFI_STARTUP_CONNECT=1
#export OMP_PROC_BIND=close
#export OMP_PLACES=cores
#export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
#ulimit -s unlimited
#export CRAY_CUDA_MPS=1
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
ulimit -s unlimited
export CRAY_CUDA_MPS=1
#
#set -o errexit
#set -o nounset
#set -o pipefail

srun /scratch/snx3000/ahehn/cp2k_master_9nov/exe/CRAY-XC50-gnu/cp2k.psmp -i input_WB97X2_TZbasis.inp -o WB97X2_TZbasis.out
