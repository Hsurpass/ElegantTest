#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main()
{
    void* context = zmq_ctx_new();
    void* responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:5555");
    assert(rc == 0);

    int count = 0;
    printf("start server...\n");
    while (1) {
        char buffer[10] = {0};
        zmq_recv(responder, buffer, 10, 0);
        printf("recv buffer: %s\n", buffer);
        count++;
        sleep(1);
        memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, sizeof(buffer), "World_%d", count);
        zmq_send(responder, buffer, strlen(buffer), 0);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);

    return 0;
}