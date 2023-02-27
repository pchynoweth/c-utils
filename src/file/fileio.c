#include <fcntl.h>
#include <libaio.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("test.txt", 0);
    if (fd != -1) {
        io_context_t ctx = 0;
        if (io_setup(1, &ctx) == 0) {
            char buf[32] = { 0 };
            struct iocb cb = { 0 };
            cb.aio_lio_opcode = IO_CMD_PREAD;
            cb.u.c.buf = buf;
            cb.u.c.nbytes = sizeof(buf) - 1;
            cb.aio_fildes = fd;
            struct iocb* cbs[1] = { &cb }; 
            if (io_submit(ctx, 1, cbs) >= 0) {
                struct io_event event = { 0 };
                if (io_getevents(ctx, 1, 1, &event, NULL)) {
                    printf("%s\n", buf);
                }
            }

            io_destroy(ctx);
        }
        close(fd);
    }

    return 0;
}