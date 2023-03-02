#include <stdio.h>
#include <stdlib.h>
#include <gnuastro/fits.h>

__global__ void gpu_kernel(float *device_array, int image_height, int image_width)
{

    //get the current block and thread id
    int bID = blockIdx.x + blockIdx.y * gridDim.x;
    int tID = bID * (blockDim.x * blockDim.y) + (threadIdx.y * blockDim.x) + threadIdx.x;

    //define the stride -> total number of threads
    int stride = blockDim.x * blockDim.y * gridDim.x * gridDim.y;


    //iterate over all pixels which are to be processed by this thread
    for (int i = tID; i < image_height * image_width; i += stride)
    {

        // get the row and column of the current pixel
        int row = tID / image_width;
        int col = tID % image_width;

        printf("pixel (%d, %d) on thread (%d, %d) on block (%d, %d) : %f\n", 
                            row, col, threadIdx.x, threadIdx.y, blockIdx.x, blockIdx.y, device_array[i]);
    }
}

int main(void)
{
    // Read the image
    gal_data_t *image;
    char *filename = "horsehead.fits", *hdu = "0";

    image = gal_fits_img_read_to_type(filename, hdu, GAL_TYPE_FLOAT32,
                                      -1, 1);

    int image_height = image->dsize[0];
    int image_width = image->dsize[1];


    // Allocate memory on the device(GPU)
    float *device_array;
    cudaMalloc((void **)&device_array, image_height * image_width * sizeof(float));
    cudaMemcpy(device_array,(float *) image->array, image_height * image_width * sizeof(float), cudaMemcpyHostToDevice);


    // define the number of threads in a block and the number of blocks in a grid
    dim3 block(32, 32);
    int block_height = image_height / block.y +1;
    int block_width = image_width / block.x +1;
    dim3 grid(block_width, block_height);


    // launch the kernel
    gpu_kernel<<<grid, block>>>(device_array, image_height, image_width);
   
    
    cudaFree(device_array);
    gal_data_free(image);
    return EXIT_SUCCESS;
}