#include <cstdio>
#include <czmq.h>
#include <czmq_library.h>
#include <unistd.h>
#include <zsock.h>
#include <zstr.h>

int main()
{
    printf("Connecting to hello world server…\n");
    zsock_t* requester = zsock_new(ZMQ_REQ);
    zsock_connect(requester, "tcp://localhost:5555");

    for (int i = 0; i < 10; i++) {
        char buffer[10] = {0};
        snprintf(buffer, sizeof(buffer), "Hello_%d", i);
        zstr_send(requester, buffer);
        sleep(1);

        char* str = zstr_recv(requester);
        printf("client recv buffer: %s\n", str);
        zstr_free(&str);
    }
    zsock_destroy(&requester);

    return 0;
}