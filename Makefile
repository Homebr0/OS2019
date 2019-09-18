all: mthread lab2 fibb

mthread: mthread.c
	cc -lpthread  mthread.c -o mthread

lab2: lab2.c
	cc -lpthread  lab2.c -o lab2

fibb: fibb.c
	cc -lpthread  fibb.c -o fibb

clean:
	rm -f *.o lab2 mthread
