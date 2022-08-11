OBJS=vector.o
EXE=vector
# all:
# all:${OBJS}
# $(EXE): # error
$(EXE):$(OBJS)
	g++ ${OBJS} -o $(EXE)

# %.o:%.c
	# g++ -c $^ -o $@
	echo $^
	echo $@
	echo $<
	echo $(shell pwd)

-PHONY:clean
clean:
	-rm $(EXE) ${OBJS}