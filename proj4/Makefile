all: mytest.o person.o hash.o
	g++ -Wall mytest.o person.o hash.o -o mytest.out

person.o: person.cpp
	g++ -g -Wall -c person.cpp

hash.o: hash.cpp
	g++ -g -Wall -c hash.cpp

mytest.o: mytest.cpp
	g++ -g -Wall -c mytest.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#[
run:
	./mytest.out

