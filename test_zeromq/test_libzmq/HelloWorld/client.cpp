#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main()
{
    printf("Connecting to hello world server…\n");
    void* context = zmq_ctx_new();
    void* requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    for (int i = 0; i < 10; i++) {
        char buffer[10] = {0};
        snprintf(buffer, sizeof(buffer), "Hello_%d", i);
        zmq_send(requester, buffer, strlen(buffer), 0);
        sleep(1);
        memset(buffer, 0, sizeof(buffer));
        zmq_recv(requester, buffer, sizeof(buffer), 0);

        printf("client recv buffer: %s\n", buffer);
    }

    zmq_close(requester);
    zmq_ctx_destroy(context);

    return 0;
}