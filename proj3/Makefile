all: mytest.o rqueue.o
	g++ -g -Wall mytest.o rqueue.o -o mytest.out

rqueue.o: rqueue.cpp
	g++ -g -Wall -c rqueue.cpp

mytest.o: mytest.cpp
	g++ -g -Wall -c mytest.cpp
clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#[
run:
	./mytest.out

