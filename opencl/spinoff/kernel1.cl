typedef struct __attribute__ ((packed)) Params
{
    int image_width;
    int image_height;
}Params;

__kernel void test(
	__global Params * param
)
{	

    int image_width = param->image_width;
    int image_height = param->image_height;


    int id = get_global_id(0);
    int x = id/image_width;
    int y = id%image_width;

    if (x >= image_width || y >= image_height)
        return;
    
    printf("On pixel %d, %d \t image height : %d  image width : %d\n", x, y, image_height, image_width);
}
