#include <stdio.h>
#include <stdlib.h>

#include <gnuastro/fits.h>
#include <gnuastro/threads.h>

/* This structure can keep all information you want to pass onto the
 * worker function on each thread. */
struct params
{
    gal_data_t *image; /* Dataset to print values of. */
};

/* This is the main worker function which will be called by the
 * different threads. `gal_threads_params' is defined in
 * `gnuastro/threads.h' and contains the pointer to the parameter we
 * want. Note that the input argument and returned value of this
 * function always must have `void *' type. */
void *
worker_on_thread(void *in_prm)
{
    /* Low-level definitions to be done first. */
    struct gal_threads_params *tprm = (struct gal_threads_params *)in_prm;
    struct params *p = (struct params *)tprm->params;

    /* Subsequent definitions. */
    float *array = p->image->array;
    size_t i, index, *dsize = p->image->dsize;

    /* Go over all the actions (pixels in this case) that were assigned
     * to this thread. */
    for (i = 0; tprm->indexs[i] != GAL_BLANK_SIZE_T; ++i)
    {
        /* For easy reading. */
        index = tprm->indexs[i];

        /* Print the information. */
        printf("(%zu, %zu) on thread %zu: %g\n", index % dsize[1] + 1,
               index / dsize[1] + 1, tprm->id, array[index]);
    }

    /* Wait for all the other threads to finish, then return. */
    if (tprm->b)
        pthread_barrier_wait(tprm->b);
    return NULL;
}

/* High-level function (called by the operating system). */
int main(void)
{
    struct params p;
    char *filename = "horsehead.fits", *hdu = "0";
    size_t numthreads = gal_threads_number();

    /* We are using * `-1' for `minmapsize' to ensure that the image is
       read into * memory and `1' for `quietmmap' (which can also be
       zero), see the "Memory management" section in the book. */
    int quietmmap = 1;
    size_t minmapsize = -1;

    /* Read the image into memory as a float32 data type. */
    p.image = gal_fits_img_read_to_type(filename, hdu, GAL_TYPE_FLOAT32,
                                        minmapsize, quietmmap);

    /* Print some basic information before the actual contents: */
    printf("Pixel values of %s (HDU: %s) on %zu threads.\n", filename,
           hdu, numthreads);
    printf("Used to check the compiled library's capability in opening "
           "a FITS file, and also spinning-off threads.\n");

    /* A small sanity check: this is only intended for 2D arrays (to
     * print the coordinates of each pixel). */
    if (p.image->ndim != 2)
    {
        fprintf(stderr, "only 2D images are supported.");
        exit(EXIT_FAILURE);
    }
    printf("Image size: %zu x %zu\n", p.image->dsize[0], p.image->dsize[1]);

    /* Spin-off the threads and do the processing on each thread. */
    gal_threads_spin_off(worker_on_thread, &p, p.image->size, numthreads,
                         minmapsize, quietmmap);

    /* Clean up and return. */
    gal_data_free(p.image);
    return EXIT_SUCCESS;
}