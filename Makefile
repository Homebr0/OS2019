all: mthread lab2

mthread: mthread.c
	cc -lpthread  mthread.c -o mthread

lab2: lab2.c
	cc -lpthread  lab2.c -o lab2

clean:
	rm -f *.o lab2 mthread
