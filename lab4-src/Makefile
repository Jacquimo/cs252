CC = gcc -g
CPP = g++ -g 

all: thr1 thr2 count count_spin hello-syscall count_recursive

thr1: thr1.cc
	g++ -o thr1 thr1.cc -lpthread

thr2: thr2.cc
	g++ -o thr2 thr2.cc -lpthread

count: count.cc
	g++  -o count count.cc -lpthread

count_spin: count_spin.cc
	g++  -o count_spin count_spin.cc -lpthread

deadlock: deadlock.cc
	$(CPP)  -o deadlock deadlock.cc -lpthread

hello-syscall: hello-syscall.c
	$(CC) -o hello-syscall hello-syscall.c

count_recursive: count_recursive.cc recmutex.c
	$(CPP) -o count_recursive count_recursive.cc recmutex.c -lpthread

clean:
	rm -f *.o thr1 thr2 count count_spin deadlock hello-syscall

