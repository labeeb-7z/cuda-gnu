#include <stdio.h>
#include "test.h"

int main()
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int c[10] = {0};
    int n = 10;
    int device = 1;
    multiply(a, b, c, n, device);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");
}

nvcc -Xcompiler -fPIC -o mat_mul.o -c kernels/mat_mul.cu
/bin/bash ../libtool  --tag=CC   --mode=link gcc  -Wall -O3  -pthread -version-info 18:0:0 -L/usr/local/lib -lwcs -R/usr/local/lib -L/usr/local/lib -lcfitsio -R/usr/local/lib -lz -L/usr/local/lib -lgsl -L/usr/local/lib -lgslcblas -lm -R/usr/local/lib -lm  -lc -no-undefined  -o libgnuastro.la -rpath /usr/local/lib  wcsdistortion.lo arithmetic.lo arithmetic-and.lo arithmetic-bitand.lo arithmetic-bitlsh.lo arithmetic-bitor.lo arithmetic-bitrsh.lo arithmetic-bitxor.lo arithmetic-divide.lo arithmetic-eq.lo arithmetic-ge.lo arithmetic-gt.lo arithmetic-le.lo arithmetic-lt.lo arithmetic-minus.lo arithmetic-modulo.lo arithmetic-multiply.lo arithmetic-ne.lo arithmetic-or.lo arithmetic-plus.lo arithmetic-set.lo array.lo binary.lo blank.lo box.lo checkset.lo color.lo convolve.lo cosmology.lo data.lo ds9.lo eps.lo fit.lo fits.lo git.lo interpolate.lo jpeg.lo kdtree.lo label.lo list.lo match.lo options.lo pdf.lo permutation.lo pointer.lo polygon.lo qsort.lo dimension.lo speclines.lo statistics.lo table.lo tableintern.lo threads.lo tiff.lo tile.lo tile-internal.lo timing.lo txt.lo type.lo units.lo warp.lo wcs.lo ../bootstrapped/lib/libgnu.la cuda.o mat_add.o mat_mul.o -lpthread 

*** Warning: Linking the shared library libgnuastro.la against the non-libtool
*** objects  cuda.o mat_add.o mat_mul.o is not portable!
libtool: link: rm -fr  .libs/libgnuastro.a .libs/libgnuastro.la .libs/libgnuastro.lai .libs/libgnuastro.so .libs/libgnuastro.so.18 .libs/libgnuastro.so.18.0.0
libtool: link: gcc -shared  -fPIC -DPIC  .libs/wcsdistortion.o .libs/arithmetic.o .libs/arithmetic-and.o .libs/arithmetic-bitand.o .libs/arithmetic-bitlsh.o .libs/arithmetic-bitor.o .libs/arithmetic-bitrsh.o .libs/arithmetic-bitxor.o .libs/arithmetic-divide.o .libs/arithmetic-eq.o .libs/arithmetic-ge.o .libs/arithmetic-gt.o .libs/arithmetic-le.o .libs/arithmetic-lt.o .libs/arithmetic-minus.o .libs/arithmetic-modulo.o .libs/arithmetic-multiply.o .libs/arithmetic-ne.o .libs/arithmetic-or.o .libs/arithmetic-plus.o .libs/arithmetic-set.o .libs/array.o .libs/binary.o .libs/blank.o .libs/box.o .libs/checkset.o .libs/color.o .libs/convolve.o .libs/cosmology.o .libs/data.o .libs/ds9.o .libs/eps.o .libs/fit.o .libs/fits.o .libs/git.o .libs/interpolate.o .libs/jpeg.o .libs/kdtree.o .libs/label.o .libs/list.o .libs/match.o .libs/options.o .libs/pdf.o .libs/permutation.o .libs/pointer.o .libs/polygon.o .libs/qsort.o .libs/dimension.o .libs/speclines.o .libs/statistics.o .libs/table.o .libs/tableintern.o .libs/threads.o .libs/tiff.o .libs/tile.o .libs/tile-internal.o .libs/timing.o .libs/txt.o .libs/type.o .libs/units.o .libs/warp.o .libs/wcs.o  cuda.o mat_add.o mat_mul.o  -Wl,--whole-archive ../bootstrapped/lib/.libs/libgnu.a -Wl,--no-whole-archive  -Wl,-rpath -Wl,/usr/local/lib -L/usr/local/lib -lwcs -lcfitsio -lz /usr/local/lib/libgsl.so /usr/local/lib/libgslcblas.so -lm -lc -lpthread  -O3 -pthread   -pthread -Wl,-soname -Wl,libgnuastro.so.18 -o .libs/libgnuastro.so.18.0.0
libtool: link: (cd ".libs" && rm -f "libgnuastro.so.18" && ln -s "libgnuastro.so.18.0.0" "libgnuastro.so.18")
libtool: link: (cd ".libs" && rm -f "libgnuastro.so" && ln -s "libgnuastro.so.18.0.0" "libgnuastro.so")
libtool: link: (cd .libs/libgnuastro.lax/libgnu.a && ar x "/home/labeeb/github/gnuastro/lib/../bootstrapped/lib/.libs/libgnu.a")
libtool: link: ar cr .libs/libgnuastro.a  wcsdistortion.o arithmetic.o arithmetic-and.o arithmetic-bitand.o arithmetic-bitlsh.o arithmetic-bitor.o arithmetic-bitrsh.o arithmetic-bitxor.o arithmetic-divide.o arithmetic-eq.o arithmetic-ge.o arithmetic-gt.o arithmetic-le.o arithmetic-lt.o arithmetic-minus.o arithmetic-modulo.o arithmetic-multiply.o arithmetic-ne.o arithmetic-or.o arithmetic-plus.o arithmetic-set.o array.o binary.o blank.o box.o checkset.o color.o convolve.o cosmology.o data.o ds9.o eps.o fit.o fits.o git.o interpolate.o jpeg.o kdtree.o label.o list.o match.o options.o pdf.o permutation.o pointer.o polygon.o qsort.o dimension.o speclines.o statistics.o table.o tableintern.o threads.o tiff.o tile.o tile-internal.o timing.o txt.o type.o units.o warp.o wcs.o  .libs/libgnuastro.lax/libgnu.a/asnprintf.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-ba.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-eexst.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-fmtstream.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-fs-xinl.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-help.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-parse.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-pin.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-pv.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-pvh.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-argp-xinl.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-basename-lgpl.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-c-ctype.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-chdir-long.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-cloexec.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dup-safer-flag.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dup-safer.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dynarray_at_failure.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dynarray_emplace_enlarge.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dynarray_finalize.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dynarray_resize.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-dynarray_resize_clear.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-exitfail.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-fcntl.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-fd-hook.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-fd-safer-flag.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-fd-safer.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-filenamecat-lgpl.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-getopt.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-getopt1.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-getprogname.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-hard-locale.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-localcharset.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-lock.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-malloca.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-math.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbchar.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbrtowc.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbschr.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbspbrk.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbsspn.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbstok_r.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-mbuiter.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-nproc.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-openat-die.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-openat-proc.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-pipe-safer.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-save-cwd.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-setlocale_null.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-sockets.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-stat-time.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-strnlen1.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-sys_socket.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-threadlib.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-time.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-unistd.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-wctype-h.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-width.o .libs/libgnuastro.lax/libgnu.a/libgnu_la-xsize.o .libs/libgnuastro.lax/libgnu.a/mktime.o .libs/libgnuastro.lax/libgnu.a/printf-args.o .libs/libgnuastro.lax/libgnu.a/printf-parse.o .libs/libgnuastro.lax/libgnu.a/vasnprintf.o 
libtool: link: ranlib .libs/libgnuastro.a
libtool: link: rm -fr .libs/libgnuastro.lax
libtool: link: ( cd ".libs" && rm -f "libgnuastro.la" && ln -s "../libgnuastro.la" "libgnuastro.la" )
/bin/bash ../libtool  --tag=CC   --mode=link gcc  -Wall -O3  -pthread -version-info 18:0:0  -o libgnuastro_make.la -rpath /usr/local/lib makeplugin.lo libgnuastro.la -lpthread 
libtool: link: rm -fr  .libs/libgnuastro_make.a .libs/libgnuastro_make.la .libs/libgnuastro_make.lai .libs/libgnuastro_make.so .libs/libgnuastro_make.so.18 .libs/libgnuastro_make.so.18.0.0 .libs/libgnuastro_make.so.18.0.0T
libtool: link: gcc -shared  -fPIC -DPIC  .libs/makeplugin.o   -Wl,-rpath -Wl,/home/labeeb/github/gnuastro/lib/.libs -Wl,-rpath -Wl,/usr/local/lib ./.libs/libgnuastro.so -lpthread  -O3 -pthread   -pthread -Wl,-soname -Wl,libgnuastro_make.so.18 -o .libs/libgnuastro_make.so.18.0.0
libtool: link: (cd ".libs" && rm -f "libgnuastro_make.so.18" && ln -s "libgnuastro_make.so.18.0.0" "libgnuastro_make.so.18")
libtool: link: (cd ".libs" && rm -f "libgnuastro_make.so" && ln -s "libgnuastro_make.so.18.0.0" "libgnuastro_make.so")
libtool: link: ar cr .libs/libgnuastro_make.a  makeplugin.o
libtool: link: ranlib .libs/libgnuastro_make.a
libtool: link: ( cd ".libs" && rm -f "libgnuastro_make.la" && ln -s "../libgnuastro_make.la" "libgnuastro_make.la" )
(base) labeeb@pop-os:~/github/gnuastro/lib$ sudo make install
make[1]: Entering directory '/home/labeeb/github/gnuastro/lib'
 /usr/bin/mkdir -p '/usr/local/lib'
 /bin/bash ../libtool   --mode=install /usr/bin/install -c   libgnuastro.la libgnuastro_make.la '/usr/local/lib'
libtool: install: /usr/bin/install -c .libs/libgnuastro.so.18.0.0 /usr/local/lib/libgnuastro.so.18.0.0
libtool: install: (cd /usr/local/lib && { ln -s -f libgnuastro.so.18.0.0 libgnuastro.so.18 || { rm -f libgnuastro.so.18 && ln -s libgnuastro.so.18.0.0 libgnuastro.so.18; }; })
libtool: install: (cd /usr/local/lib && { ln -s -f libgnuastro.so.18.0.0 libgnuastro.so || { rm -f libgnuastro.so && ln -s libgnuastro.so.18.0.0 libgnuastro.so; }; })
libtool: install: /usr/bin/install -c .libs/libgnuastro.lai /usr/local/lib/libgnuastro.la
libtool: warning: relinking 'libgnuastro_make.la'
libtool: install: (cd /home/labeeb/github/gnuastro/lib; /bin/bash "/home/labeeb/github/gnuastro/libtool"  --tag CC --mode=relink gcc -Wall -O3 -pthread -version-info 18:0:0 -o libgnuastro_make.la -rpath /usr/local/lib makeplugin.lo libgnuastro.la -lpthread )
libtool: relink: gcc -shared  -fPIC -DPIC  .libs/makeplugin.o   -Wl,-rpath -Wl,/usr/local/lib -L/usr/local/lib -lgnuastro -lpthread  -O3 -pthread   -pthread -Wl,-soname -Wl,libgnuastro_make.so.18 -o .libs/libgnuastro_make.so.18.0.0
libtool: install: /usr/bin/install -c .libs/libgnuastro_make.so.18.0.0T /usr/local/lib/libgnuastro_make.so.18.0.0
libtool: install: (cd /usr/local/lib && { ln -s -f libgnuastro_make.so.18.0.0 libgnuastro_make.so.18 || { rm -f libgnuastro_make.so.18 && ln -s libgnuastro_make.so.18.0.0 libgnuastro_make.so.18; }; })
libtool: install: (cd /usr/local/lib && { ln -s -f libgnuastro_make.so.18.0.0 libgnuastro_make.so || { rm -f libgnuastro_make.so && ln -s libgnuastro_make.so.18.0.0 libgnuastro_make.so; }; })
libtool: install: /usr/bin/install -c .libs/libgnuastro_make.lai /usr/local/lib/libgnuastro_make.la
libtool: install: /usr/bin/install -c .libs/libgnuastro.a /usr/local/lib/libgnuastro.a
libtool: install: chmod 644 /usr/local/lib/libgnuastro.a
libtool: install: ranlib /usr/local/lib/libgnuastro.a
libtool: install: /usr/bin/install -c .libs/libgnuastro_make.a /usr/local/lib/libgnuastro_make.a
libtool: install: chmod 644 /usr/local/lib/libgnuastro_make.a
libtool: install: ranlib /usr/local/lib/libgnuastro_make.a
libtool: finish: PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin:/sbin" ldconfig -n /usr/local/lib
----------------------------------------------------------------------
Libraries have been installed in:
   /usr/local/lib

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the '-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the 'LD_RUN_PATH' environment variable
     during linking
   - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to '/etc/ld.so.conf'

See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------
 /usr/bin/mkdir -p '/usr/local/lib/pkgconfig'
 /usr/bin/install -c -m 644 gnuastro.pc '/usr/local/lib/pkgconfig'
 /usr/bin/mkdir -p '/usr/local/include/gnuastro'
 /usr/bin/install -c -m 644 gnuastro/config.h ../lib/gnuastro/arithmetic.h ../lib/gnuastro/array.h ../lib/gnuastro/binary.h ../lib/gnuastro/blank.h ../lib/gnuastro/box.h ../lib/gnuastro/color.h ../lib/gnuastro/convolve.h ../lib/gnuastro/cosmology.h ../lib/gnuastro/data.h ../lib/gnuastro/dimension.h ../lib/gnuastro/ds9.h ../lib/gnuastro/eps.h ../lib/gnuastro/fit.h ../lib/gnuastro/fits.h ../lib/gnuastro/git.h ../lib/gnuastro/interpolate.h ../lib/gnuastro/jpeg.h ../lib/gnuastro/kdtree.h ../lib/gnuastro/label.h ../lib/gnuastro/list.h ../lib/gnuastro/match.h ../lib/gnuastro/pdf.h ../lib/gnuastro/permutation.h ../lib/gnuastro/pointer.h ../lib/gnuastro/polygon.h ../lib/gnuastro/qsort.h ../lib/gnuastro/speclines.h ../lib/gnuastro/statistics.h ../lib/gnuastro/table.h ../lib/gnuastro/threads.h ../lib/gnuastro/tiff.h ../lib/gnuastro/tile.h ../lib/gnuastro/txt.h ../lib/gnuastro/type.h ../lib/gnuastro/units.h ../lib/gnuastro/warp.h ../lib/gnuastro/wcs.h ../lib/gnuastro/gpu.h '/usr/local/include/gnuastro'
make[1]: Leaving directory '/home/labeeb/github/gnuastro/lib'