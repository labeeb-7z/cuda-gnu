#include <CL/cl.h>



void gal_gpu_spinoff(char * source_str, char * kernel_name, int worker_size, )
{
















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
 



        // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);
 



    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
 


    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, kernel_name, &ret);
 









    cl_int image_height_cl = input_image->dsize[0];
    cl_int image_width_cl = input_image->dsize[1];



    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&input_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&kernel_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&output_mem_obj);
    ret = clSetKernelArg(kernel, 3, sizeof(cl_int), &image_height_cl);
    ret = clSetKernelArg(kernel, 4, sizeof(cl_int), &image_width_cl);
 








    // Execute the OpenCL kernel on the list
    size_t global_item_size = image_height*image_width; // Process the entire lists
    size_t local_item_size = 128; // Divide work items into groups of 64


    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
 



}