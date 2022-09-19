all:
	gcc epoll_ET_block.c ../../../common/mysocket.c -o epoll_ET_block
	g++ epoll_ET_nonblock.cpp ../../../common/mysocket.c -g -o epoll_ET_nonblock
	gcc epoll_ET_nonblock_EPOLLOUT.c ../../../common/mysocket.c -g -o epoll_ET_nonblock_EPOLLOUT

clean:
	rm -rf epoll_ET_block epoll_ET_nonblock epoll_ET_nonblock_EPOLLOUT
