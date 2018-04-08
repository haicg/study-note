CFLAGS += -g -Wall -Werror
CC = gcc
CPP = g++
objects_c := $(patsubst %.c,%.bin,$(wildcard *.c))
objects_cpp := $(patsubst %.cpp,%.bin,$(wildcard *.cpp))
$(warning $(objects_cpp))
$(objects_c):$(wildcard *.c)
	$(CC)  $(CFLAGS) $^ -o $@
$(objects_cpp):$(wildcard *.cpp)
	$(CPP)  $(CFLAGS) $^ -o $@
all:
	echo "Everything is ok"
clean:
	rm -rf *.o
	rm  -rf device_post
