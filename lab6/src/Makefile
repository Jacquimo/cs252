CXX = gcc -std=gnu99

all: theGrapist

%.o: %.c
	echo
	@echo 'Building $@ from $<'
	$(CXX) -o $@ -c -I. $<

awesomeSauce: awesomeSauce.o
	$(CXX) -o ../$@ $@.o 

theGrapist: theGrapist.o
	$(CXX) -o ../$@ $@.o

clean: 
	rm -f *.o ../awesomeSauce ../theGrapist
