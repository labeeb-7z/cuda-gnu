typedef struct __attribute__ ((packed)) Params
{
    int image_width;
    int image_height;
    float * image;
}Params;

__kernel void test(
	__global Params * param
)
{	

    int image_width = param->image_width;
    int image_height =  param->image_height;
    float * image = param->image;

    int id = get_global_id(0);
    int x = id/image_width;
    int y = id%image_width;

    int re =  printf("On pixel %d, %d \t image height : %d  image width : %d\n", x, y, image_height, image_width);
    printf("re int: %d\n", re);
    re= printf("On pixel %d, %d \t image height : %d  image width : %d \t pixel value : %f\n", x, y, image_height, image_width, image[x*image_width + y]);
    printf("re array: %d\n", re);
}
