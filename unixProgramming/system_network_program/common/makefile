all:
	gcc tcp_client.c mysocket.c -g -o tcp_client
	gcc tcp_client_while_10.c mysocket.c -g -o tcp_client_while_10
	gcc tcp_client_EPOLLOUT.c mysocket.c -g -o tcp_client_EPOLLOUT
	gcc tcp_client_NONBLOCK1.c mysocket.c -g -o tcp_client_NONBLOCK1
	gcc tcp_client_NONBLOCK2.c mysocket.c -g -o tcp_client_NONBLOCK2

	
clean:
	rm -rf tcp_client tcp_client_while_10 tcp_client_EPOLLOUT tcp_client_NONBLOCK1 tcp_client_NONBLOCK2
