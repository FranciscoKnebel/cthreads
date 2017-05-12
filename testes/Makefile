CC=gcc
LIB_DIR=../lib

all: testcFila

testcFila: testcFila.c $(LIB_DIR)/libcthread.a
	$(CC) -o testcFila testcFila.c -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf testcFila *.o *~
