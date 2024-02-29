#include <cassert>
#include <cstdio>
#include <czmq.h>
#include <czmq_library.h>
#include <unistd.h>
#include <zmq.h>
#include <zsock.h>
#include <zstr.h>

int main()
{
    // Socket to talk clients
    zsock_t* responder = zsock_new(ZMQ_REP);
    int rc = zsock_bind(responder, "tcp://*:5555");
    assert(rc == 5555);

    int count = 0;
    while (1) {
        char* str = zstr_recv(responder);
        printf("server recv:  %s\n", str);
        sleep(1);

        char buffer[10] = {0};
        snprintf(buffer, sizeof(buffer), "World_%d", count++);
        zstr_send(responder, buffer);

        zstr_free(&str);
    }
    zsock_destroy(&responder);

    return 0;
}