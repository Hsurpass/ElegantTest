all:
	gcc epoll_LT_block.c ../../../common/mysocket.c -g -o epoll_LT_block
	gcc epoll_LT_block_EPOLLOUT.c ../../../common/mysocket.c -g -o epoll_LT_block_EPOLLOUT
	gcc epoll_LT_nonblock.c ../../../common/mysocket.c -g -o epoll_LT_nonblock

clean:
	rm -rf epoll_LT_block epoll_LT_block_EPOLLOUT epoll_LT_block_nonblock
