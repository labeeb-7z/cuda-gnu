struct Params
{
    float *device_array;
    float *device_kernel;
    float *device_output;
    int image_width;
    int image_height;
};

__kernel void convolution(
	__global void * param
)
{	
    struct Params *params = (struct Params *)param;

    float *device_array = params->device_array;
    float *device_kernel = params->device_kernel;
    float *device_output = params->device_output;
    int image_width = params->image_width;
    int image_height = params->image_height;


    int x = get_global_id(0);
    int y = get_global_id(1);

    //printf("On pixel %d, %d : value - %f\n", x, y, device_array[x + y * image_width]);

    
}
