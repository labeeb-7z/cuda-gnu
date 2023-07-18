#include <stdio.h>
#include <gnuastro/fits.h>
#include <time.h>
 
#include <CL/cl.h>
 
#define MAX_SOURCE_SIZE (0x100000)


typedef struct __attribute__ ((packed)) Params
{
    int image_width;
    int image_height;
}Params;

 
int main(void) {

    gal_data_t *input_image = gal_fits_img_read_to_type("../test3.fits", "1", GAL_TYPE_FLOAT32, -1, -1);
    gal_data_t *kernel_image = gal_fits_img_read_kernel("../kernel.fits", "1", -1, -1);
    
    FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen("kernel1.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
 





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






    Params param;

    param.image_height = input_image->dsize[0];
    param.image_width =input_image->dsize[1];

    cl_mem g_param = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            sizeof(Params), NULL, &ret);

    
    clEnqueueWriteBuffer(command_queue, g_param, CL_TRUE, 0, 
        sizeof(Params), &param, 0, NULL, NULL);

    ret = clSetKernelArg(kernel, 0, sizeof(param), (void *)&g_param);

    size_t global_item_size = input_image->dsize[0]*input_image->dsize[1];
    size_t local_item_size = 128; 


    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
 





    ret = clReleaseMemObject(g_param);
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    return 0;
}