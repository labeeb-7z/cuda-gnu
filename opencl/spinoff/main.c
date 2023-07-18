#include <stdio.h>
#include <gnuastro/fits.h>
#include <time.h>
 
#include <CL/cl.h>
 
#define MAX_SOURCE_SIZE (0x100000)



typedef struct Params
{
    cl_mem device_array;
    cl_mem device_kernel;
    cl_mem device_output;
    cl_int image_height;
    cl_int image_width;
};

 
int main(void) {
    // Create the two input vectors

 



    clock_t start_read, end_read;
    double cpu_time_used_read;

    start_read = clock();

    // reading input image and kernel
    gal_data_t *input_image = gal_fits_img_read_to_type("../test3.fits", "1", GAL_TYPE_FLOAT32, -1, -1);
    gal_data_t *kernel_image = gal_fits_img_read_kernel("../kernel.fits", "1", -1, -1);

    int image_height = input_image->dsize[0];
    int image_width = input_image->dsize[1];





    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen("opencl_conv.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
 









    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
            &device_id, &ret_num_devices);
 









    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
 
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 


        end_read = clock();
    cpu_time_used_read = ((double)(end_read - start_read)) / CLOCKS_PER_SEC;
    printf("Time taken in reading: %f\n", cpu_time_used_read);























    clock_t start_all, end_all;
    double cpu_time_used_all;

    start_all = clock();



    // Create memory buffers on the device for each vector 
    cl_mem g_input_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            image_height * image_width * sizeof(float), NULL, &ret);

    cl_mem g_kernel_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            9 * sizeof(float), NULL, &ret);


    cl_mem g_output_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            image_height * image_width * sizeof(float), NULL, &ret);
 










    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, g_input_mem_obj, CL_TRUE, 0,
            image_height * image_width * sizeof(float), input_image->array, 0, NULL, NULL);


    ret = clEnqueueWriteBuffer(command_queue, g_kernel_mem_obj, CL_TRUE, 0, 
           9 * sizeof(float), kernel_image->array, 0, NULL, NULL);
 






    end_all = clock();
    cpu_time_used_all = ((double)(end_all - start_all)) / CLOCKS_PER_SEC;
    printf("Time taken in allocation: %f\n", cpu_time_used_all);



























    clock_t start_convolve, end_convolve;
    double cpu_time_used_convolve;

    start_convolve = clock();



    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);
 



    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
 


    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "convolution", &ret);
 









    cl_int g_image_height_cl = input_image->dsize[0];
    cl_int g_image_width_cl = input_image->dsize[1];

    struct Params params;
    params.device_array = g_input_mem_obj;
    params.device_kernel = g_kernel_mem_obj;
    params.device_output = g_output_mem_obj;
    params.image_height = g_image_height_cl;
    params.image_width = g_image_width_cl;

    cl_mem g_params = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            sizeof(struct Params), NULL, &ret);

    
    clEnqueueWriteBuffer(command_queue, g_params, CL_TRUE, 0, 
        sizeof( struct Params), &params, 0, NULL, NULL);

    



    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(params), (void *)&g_params);

 








    // Execute the OpenCL kernel on the list
    size_t global_item_size = image_height*image_width; // Process the entire lists
    size_t local_item_size = 128; // Divide work items into groups of 64


    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
 



        end_convolve = clock();

    cpu_time_used_convolve = ((double)(end_convolve - start_convolve)) / CLOCKS_PER_SEC;
    printf("Time taken in convolution: %f\n", cpu_time_used_convolve);











        clock_t start_deall, end_deall;
    double cpu_time_used_deall;

    start_deall = clock();

    // Read the memory buffer C on the device to the local variable C
    float *C = (float*)malloc(sizeof(float) * image_height * image_width);
    ret = clEnqueueReadBuffer(command_queue, g_output_mem_obj, CL_TRUE, 0, 
            sizeof(float) * image_height * image_width, C, 0, NULL, NULL);
 

    end_deall = clock();
    cpu_time_used_deall = ((double)(end_deall - start_deall)) / CLOCKS_PER_SEC;
    printf("Time taken in deallocation: %f\n", cpu_time_used_deall);
 




    clock_t start_save, end_save;
    double cpu_time_used_save;

    start_save = clock();



 gal_data_t * out;
    out=gal_data_alloc((void *)C, GAL_TYPE_FLOAT32, input_image->ndim, input_image->dsize,
                         input_image->wcs, 0, input_image->minmapsize, input_image->quietmmap,
                         NULL, input_image->unit, NULL);





    fitsfile *fptr = gal_fits_img_write_to_ptr(out,"test_opencl_conv.fits");
    int status = 0;
    fits_close_file(fptr, &status); /* close the file */
    gal_data_free(out);

    end_save = clock();
    cpu_time_used_save = ((double)(end_save - start_save)) / CLOCKS_PER_SEC;
    printf("Time taken in saving: %f\n", cpu_time_used_save);





    // Display the result to the screen
    // for(i = 0; i < LIST_SIZE; i++)
    //     printf("%d + %d = %d\n", A[i], B[i], C[i]);
 




 
    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(g_input_mem_obj);
    ret = clReleaseMemObject(g_kernel_mem_obj);
    ret = clReleaseMemObject(g_output_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    return 0;
}
