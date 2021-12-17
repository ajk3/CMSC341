all: mytest.o dtree.o utree.o
	g++ -Wall mytest.o dtree.o utree.o -o mytest.out

dtree.o: dtree.cpp
	g++ -Wall -c dtree.cpp

utree.o: utree.cpp
	g++ -Wall -c utree.cpp

mytest.o: mytest.cpp
	g++ -Wall -c mytest.cpp
clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#[
run:
	./mytest.out

