#include <stdio.h>
#include <gnuastro/fits.h>
#include <time.h>
 
#include <CL/cl.h>
 
#define MAX_SOURCE_SIZE (0x100000)


typedef struct __attribute__ ((packed)) Params
{
    int image_width;
    int image_height;
    float *device_array;
}Params;



 
int main(void) {


    // reading input image and kernel
    gal_data_t *input_image = gal_fits_img_read_to_type("../test3.fits", "1", GAL_TYPE_FLOAT32, -1, -1);
    gal_data_t *kernel_image = gal_fits_img_read_kernel("../kernel.fits", "1", -1, -1);
    
    FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen("kernel2.cl", "r");
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


    cl_mem g_input = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            input_image->size * sizeof(float), NULL, &ret);
    ret = clEnqueueWriteBuffer(command_queue, g_input, CL_TRUE, 0,
            input_image->size* sizeof(float), (float *)input_image->array, 0, NULL, NULL);



    Params param;

    param.image_height = input_image->dsize[0];
    param.image_width = input_image->dsize[1];
    param.device_array = (float *)g_input;





    cl_mem g_param = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            sizeof(param), NULL, &ret);

    clEnqueueWriteBuffer(command_queue, g_param, CL_TRUE, 0, 
        sizeof(param), &param, 0, NULL, NULL);



    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&g_param);

    
    printf("ret = %d\n", ret);
    if(ret != CL_SUCCESS){
        switch (ret)
        {
        case CL_INVALID_KERNEL:
            printf("CL_INVALID_KERNEL\n");
            break;
        
        case CL_INVALID_ARG_INDEX:
            printf("CL_INVALID_ARG_INDEX\n");
            break;

        case CL_INVALID_ARG_VALUE:
            printf("CL_INVALID_ARG_VALUE\n");
            break;

        case CL_INVALID_MEM_OBJECT:
            printf("CL_INVALID_MEM_OBJECT\n");
            break;
        
        case CL_INVALID_SAMPLER:
            printf("CL_INVALID_SAMPLER\n");
            break;

        case CL_INVALID_ARG_SIZE:
            printf("CL_INVALID_ARG_SIZE\n");
            break;

        case CL_OUT_OF_RESOURCES:
            printf("CL_OUT_OF_RESOURCES\n");
            break;
        
        case CL_OUT_OF_HOST_MEMORY:
            printf("CL_OUT_OF_HOST_MEMORY\n");
            break;

        case CL_INVALID_EVENT_WAIT_LIST:
            printf("CL_INVALID_EVENT_WAIT_LIST\n");
            break;

        
        default:
            break;
        }
        printf("Error: Failed to set kernel arguments! %d\n", ret);
        return 0;
    }

    size_t global_item_size = input_image->size;
    size_t local_item_size = 128; 


    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
 

    printf("ret = %d\n", ret);




    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    return 0;
}