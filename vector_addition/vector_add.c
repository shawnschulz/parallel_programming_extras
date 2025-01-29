#include <cuda.h>

void vecAdd(float* h_A, float* h_B, float* h_C, int n) {
    int size = n* sizeof(float);
    float *d_A, *d_B, *d_C;
    // Showing the error handling example for practice but should write
    // this as a macro and use for all memory allocations in a real project
    cudaError_t err = cudaMalloc( (void **) &d_A, size);
    if (err != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorStr(err), __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    cudaMemcpy( d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMalloc( (void **) &d_B, size);
    cudaMemcpy( d_B, h_B, size, cudaMemcpyHostToDevice);
    // since C is the result matrix wew copy it the other way around when we're done
    cudaMalloc( (void **) &d_C, size);

    // Kernel invocations go here

    cudaMemcpy(h_C, d_C, size, cudaMemcpyHostToDevice);

    // Free the device memory used in this function
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
