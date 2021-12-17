all: myTest.o buffer.o bufferlist.o
	g++ -Wall myTest.o buffer.o bufferlist.o  -o mytest.out

buffer.o: buffer.cpp
	g++ -Wall -c buffer.cpp

bufferlist.o: bufferlist.cpp
	g++ -Wall -c bufferlist.cpp

driver.o: myTest.cpp
	g++ -Wall -c myTest.cpp
clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#[
run:
	./mytest.out

