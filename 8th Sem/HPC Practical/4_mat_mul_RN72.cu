/*
Title:-Write a CUDA Program for :
1. Matrix Multiplication using CUDA C
Name:-Pravin Jain
Roll NO:-72
Subject:-LP-V
*/
#include<cuda.h>
#include<stdio.h>

int main(void)
 {
    void MatrixMultiplication(float *, float *, float *, int);

    //const int Width = 5;

    float M[5*5], N[5*5], P[5*5];

    for(int i = 0; i < (5*5) ; i++)
    {
        M[i] = 5;
        N[i] = 5;
        P[i] = 0;
    }
    
 MatrixMultiplication(M, N, P, 5);

    for(int i = 0; i < (5*5) ; i++)
    {
        printf("%f \n", P[i]);
    }

    return 0;
}

//Matrix multiplication kernel - thread specification
__global__ void MatrixMulKernel(float *Md, float *Nd, float *Pd, int width)
 {
    //2D Thread ID
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    //Pvalue stores the Pd element that is computed by the thread
    float Pvalue = 0;

    for(int k = 0; k < 5 ; k++)
    {
        float Mdelement = Md[ty*5 + k];
        float Ndelement = Nd[k*5 + tx];
        Pvalue = Pvalue + (Mdelement*Ndelement);
    }

    Pd[ty*5 + tx] = Pvalue;
 }

void MatrixMultiplication(float *M, float *N, float *P, int width)
  {
    int size = 5*5*sizeof(float);

    float *Md, *Nd, *Pd;

    //Transfer M and N to device memory
    cudaMalloc((void**)&Md, size);
    cudaMemcpy(Md,M,size,cudaMemcpyHostToDevice);
    cudaMalloc((void**)&Nd, size);
    cudaMemcpy(Nd,N,size,cudaMemcpyHostToDevice);

    //Allocate P on the device
    cudaMalloc((void**)&Pd,size);

    //Setup the execution configuration
    dim3 dimBlock(5,5);
    dim3 dimGrid(1,1);

    //Launch the device computation threads!
    MatrixMulKernel<<<dimGrid,dimBlock>>>(Md,Nd,Pd,5);

    //Transfer P from device to host
    cudaMemcpy(P,Pd,size,cudaMemcpyDeviceToHost);

    //Free device matrices
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);
 }



/*
OUTPUT:

sl-sys11@slsys11-OptiPlex-3010:~$ nvcc matp.cu
sl-sys11@slsys11-OptiPlex-3010:~$ ./a.out
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
125.000000 
sl-sys11@slsys11-OptiPlex-3010:~$ 

*/

