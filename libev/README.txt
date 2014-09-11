CC=arm-arago-linux-gnueabi-gcc ./configure --host=arm-linux --prefix=/home/build_share/ipc1/Source/ipnc/src/utils/libev/

make

make install


notice:

ev.c:1220:3: error: #error "memory fences not defined for your architecture, please report"


/* if your architecture doesn't need memory fences, e.g. because it is
 * single-cpu/core, or if you use libev in a project that doesn't use libev
 * from multiple threads, then you can define ECB_AVOID_PTHREADS when compiling
 * libev, in which cases the memory fences become nops.
 * alternatively, you can remove this #error and link against libpthread,
 * which will then provide the memory fences.
 */
