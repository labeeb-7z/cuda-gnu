#include <stdio.h>
#include <CL/cl.h>
 
#define MAX_SOURCE_SIZE (0x100000)


typedef struct __attribute__ ((packed)) sample_struct
{
    int image_width;
    int image_height;
    float *image;
}sample_struct;



 
int main(void) {

    // loading the kernel
    FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen("kernel.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
 

    // initiating the device
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
            &device_id, &ret_num_devices);

    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
 
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL); 
    cl_kernel kernel = clCreateKernel(program, "test", &ret);






    // initialize image on host.
    float * image = (float *) malloc(9*sizeof(float));
    for(int i = 0; i < 9; i++)
        image[i] = i+1;


    // copy image to device memory
    cl_mem device_image = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            9* sizeof(float), NULL, &ret);
    ret = clEnqueueWriteBuffer(command_queue, device_image, CL_TRUE, 0,
            9* sizeof(float), image, 0, NULL, NULL);



    // initialize param on host.
    sample_struct param;
    param.image_height = 3;
    param.image_width = 3;
    param.image = (float *)device_image;


    // copy param to device memory
    cl_mem device_param = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            sizeof(param), NULL, &ret);

    clEnqueueWriteBuffer(command_queue, device_param, CL_TRUE, 0, 
        sizeof(param), &param, 0, NULL, NULL);



    //configuration
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&device_param);

    size_t global_item_size = 9;
    size_t local_item_size = 3; 

    // launch the kernel
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);



    free(image);
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    return 0;
}