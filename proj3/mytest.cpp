#include <iostream>
#include <cstdlib>
#include <map>
#include "rqueue.h"

using namespace std;

// priority functions

int priorityFn1(const Student& student) {
	//priority value is determined based on some criteria
	//priority value falls in the range [0-6]
	//the smaller value means the higher priority
	int priority = student.getYear() + student.getMajor() + student.getGroup();
	return priority;
}

int priorityFn2(const Student& student) {
	//priority is determined by an officer in registrar office
	//priority value falls in the range [0-6]
	//the smaller value means the higher priority
	return student.getPriority();
}

int priorityFn3(const Student& student) {
	//priority based on the student's year in school
	//priority value falls in the range [0-3]
	//the smaller value means the higher priority
	return student.getYear();
}
//------------------------------------------------------------------------------------------------------//

class Tester
{
public:

	bool removeFromEmptyQueue();
	bool testInsert(RQueue&);
	bool validExtraction(RQueue&);

	bool testMerge(RQueue&, RQueue&);

	bool changePriorityFunc();

	bool testAssignmentOperator(RQueue&, const RQueue&);
	bool testCopyConstructor(const RQueue&);

	void insertionPerformance(int, int);
	void extractionPerformance(int, int);
	void copyConstructorPerformance(int, int);

	Student createStudent();

private:

	// helper functions
	bool checkMinHeapProp(Node*, const RQueue&);
	bool validMinHeap(Node*,const RQueue&);
	bool compareNodes(Node*, const Student&);
	bool unalteredData(Node*, map<string, Student>);
	bool compareTrees(Node*, const Node*);
	int  findHighestPriority(const RQueue&, Node*, int);
};

int main()
{
	Tester tester;

	{   //testing basic correctness (insertion and deletion) using priority func 1
		cout << "\nTest case: Basic correctness (insertion and deletion) using priority func 1:\n";
		RQueue queue1(priorityFn1);

		if (tester.testInsert(queue1) && tester.validExtraction(queue1))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing basic correctness (insertion and deletion) using priority func 2
		cout << "\nTest case: Basic correctness (insertion and deletion) using priority func 2:\n";
		RQueue queue1(priorityFn2);

		if (tester.testInsert(queue1) && tester.validExtraction(queue1))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing basic correctness (insertion and deletion) using priority func 3
		cout << "\nTest case: Basic correctness (insertion and deletion) using priority func 3:\n";
		RQueue queue1(priorityFn3);

		if (tester.testInsert(queue1) && tester.validExtraction(queue1))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing deletion on an empty queue
		cout << "\nTest case: attempting to delete from an empty queue: exception thrown:\n";
		if (tester.removeFromEmptyQueue())
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing basic merge
		cout << "\nTest case: Basic merge:\n";
		RQueue queue1(priorityFn2);
		RQueue queue2(priorityFn2);

		for (int i = 0; i < 4; i++)
		{
			queue1.insertStudent(tester.createStudent());
		}

		for (int j = 0; j < 2; j++)
		{
			queue2.insertStudent(tester.createStudent());
		}

		if (tester.testMerge(queue1,queue2))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing self merging
		cout << "\nTest case: self merge:\n";
		RQueue queue1(priorityFn2);

		for (int i = 0; i < 4; i++)
		{
			queue1.insertStudent(tester.createStudent());
		}

		if (tester.testMerge(queue1, queue1))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing merge functionality using an empty rhs
		cout << "\nTest case: merging empty rhs:\n";
		RQueue queue1(priorityFn2);
		RQueue queue2(priorityFn2);

		for (int i = 0; i < 4; i++)
		{
			queue1.insertStudent(tester.createStudent());
		}

		if (tester.testMerge(queue1, queue2))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing merge on two empty heaps
		cout << "\nTest case: merging two empty heaps:\n";
		RQueue queue1(priorityFn2);
		RQueue queue2(priorityFn2);

		if (tester.testMerge(queue1, queue2))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   //testing merge on two heaps with different priority functions
		cout << "\nTest case: attempting to merge queues with different priority functions: exception thrown:\n";
		RQueue queue1(priorityFn2);
		RQueue queue2(priorityFn1);

		queue1.insertStudent(tester.createStudent());
		queue2.insertStudent(tester.createStudent());

		if (tester.testMerge(queue1,queue2))
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{   // changing the priority function
		cout << "\nTest case: changing priority function:\n";
		if (tester.changePriorityFunc())
		{
			cout << "Test Passed!!!!" << endl;
		}
		else
		{
			cout << "Test failed!!!" << endl;
		}
	}

	{ // testing copy constructor on an empty heaps
		RQueue rhs(priorityFn1);

		cout << "\nTest case: testing copy constructor on an empty heap:\n";
		if (tester.testCopyConstructor(rhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{ // testing copy constructor on a heap with one data
		RQueue rhs(priorityFn1);

		for (int i = 0; i < 1; i++)
		{
			rhs.insertStudent(tester.createStudent());
		}

		cout << "\nTest case: testing copy constructor on a heap with only one data:\n";
		if (tester.testCopyConstructor(rhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{ // testing copy constructor on a heap with 10 data
		RQueue rhs(priorityFn1);

		for (int i = 0; i < 10; i++)
		{
			rhs.insertStudent(tester.createStudent());
		}

		cout << "\nTest case: testing copy constructor on a heap with ten data:\n";
		if (tester.testCopyConstructor(rhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{ // testing assignment operator on empty heaps
		RQueue lhs(priorityFn1);
		RQueue rhs(priorityFn1);

		cout << "\nTest case: testing assignment operator on an empty heap:\n";
		if (tester.testAssignmentOperator(lhs, rhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{ // testing self-assignment
		RQueue lhs(priorityFn1);

		for (int i = 0; i < 5; i++)
		{
			lhs.insertStudent(tester.createStudent());
		}

		cout << "\nTest case: self assignment:\n";
		if (tester.testAssignmentOperator(lhs, lhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{ // testing assigment operator on a heap with one data
		RQueue lhs(priorityFn1);
		RQueue rhs(priorityFn1);

		for (int i = 0; i < 1; i++)
		{
			rhs.insertStudent(tester.createStudent());
		}

		cout << "\nTest case: testing assignment operator on a heap with only one data:\n";
		if (tester.testAssignmentOperator(lhs, rhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{ // testing assigment operator on a heap with 10 data
		RQueue lhs(priorityFn1);
		RQueue rhs(priorityFn1);

		for (int i = 0; i < 10; i++)
		{
			rhs.insertStudent(tester.createStudent());
		}

		cout << "\nTest case: testing assignment operator on a heap with ten data:\n";
		if (tester.testAssignmentOperator(lhs, rhs))
		{
			cout << "test passed!!!" << endl;
		}
		else
		{
			cout << "test failed!!!!" << endl;
		}
	}

	{
		//Measuring the efficiency of insertion functionality
		cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
		int M = 5;//number of trials
		int N = 10000;//original input size
		tester.insertionPerformance(M, N);
	}

	{
		//Measuring the efficiency of extraction functionality
		cout << "\nMeasuring the efficiency of extraction functionality:" << endl;
		int M = 5;//number of trials
		int N = 10000;//original input size
		tester.extractionPerformance(M, N);
	}

	{
		//Measuring the efficiency of copy constructor
		cout << "\nMeasuring the efficiency of copy constructor:" << endl;
		int M = 5;//number of trials
		int N = 10000;//original input size
		tester.copyConstructorPerformance(M, N);
	}
	
	cout << "\n\n-----------------------------------------// End of test cases!!!! //----------------------------------------" << endl << endl;
	
	return 0;
}


//-------------------------------------------------------------// function defn // ---------------------------------------------------------------------//

Student Tester::createStudent()
{
	const int SIZE = 10;

	//Student(string name, int priority, int year, int major, int group)

	string names[SIZE] = { "sam", "nick", "mia", "harry", "joe", "katy", "josh", "tia", "hey", "hello" };

	string name = names[rand() % SIZE];
	int priority = rand() % 7; // 0-6
	int year = rand() % 4; // 0-3
	int major = rand() % 3; // 0-2
	int group = rand() % 2; // 0-1

	Student student(name, priority, year, major, group);

	return student;
}


bool Tester::removeFromEmptyQueue()
{
	RQueue queue1(priorityFn1);

	try
	{
		//trying to remove from an empty queue
		queue1.getNextStudent();
		
	}
	catch (domain_error& e) {
		//the exception that we expect
		cout << e.what() << endl;
		return true;
	}
	catch (...) {
		//any other exception, this case is not acceptable
		return false;
	}
	//no exception thrown, this case is not acceptable
	return false;
}

bool Tester::testInsert(RQueue& queue1)
{
	for (int i = 0; i < 10; i++)
	{
		queue1.insertStudent(createStudent());
	}

	if (validMinHeap(queue1._heap, queue1))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Tester:: testMerge(RQueue& queue1, RQueue& queue2)
{
	int heap1Size = queue1.numStudents();
	int heap2Size = queue2.numStudents();

	if (&queue1 == &queue2) // self-merge
	{
		queue1.mergeWithQueue(queue2);

		if (queue1._size == heap1Size) // if size before merge == size after merge, we can assure that the code guards against the self-merging
		{
			cout << "Can't merge lhs with itself!!!!" << endl;
			return true;
		}
	}

	if (queue1.getPriorityFn() != queue2.getPriorityFn()) // merging heaps with two different priority function
	{
		try
		{
			queue1.mergeWithQueue(queue2);
		}
		catch (domain_error& e) // expected exception
		{
			cout << e.what() << endl;
			return true;
		}
		catch (...) 
		{
			//any other exception, this case is not acceptable
			return false;
		}
		//no exception thrown, this case is not acceptable
		return false;
	}
	
	try // basic merge
	{
		queue1.mergeWithQueue(queue2);
	}
	catch (...) // at this point we're not expecting any exceptions including the domain_error
	{
		return false;
	}

	// if the min heap prop holds and the size of the queue after merge is equal to the size of two initial heaps
	if (validMinHeap(queue1._heap, queue1) && (queue1._size == (heap1Size + heap2Size)))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

/**
* this function basically checks if the heap is rebuilt correctly after changing the priority function
* this function uses three helper functions and a map to check the validaty of newly constructed heap
*/
bool Tester::changePriorityFunc()
{
	RQueue tempHeap(priorityFn3);

	map<string, Student> list;

	const int SIZE = 6;

	//Student(string name, int priority, int year, int major, int group)
	Student arr[SIZE] =
	{
		{"Sam", 1, 1, 1, 1},
		{"Liz", 5, 1, 2, 0},
		{"Nick", 2, 0, 0, 0},
		{"Eva", 4, 3, 2, 1},
		{"John", 6, 3, 2, 1},
		{"Mia", 3, 0, 0, 0}
	};

	for (int i = 0; i < SIZE; i++)
	{
		tempHeap.insertStudent(arr[i]);
		list.insert(make_pair(arr[i].getName(), arr[i]));
	}

	cout <<"Before changing priority function:\n\t";
	tempHeap.dump();

	tempHeap.setPriorityFn(priorityFn1); // function changed
	
	cout << "After changing priority function:\n\t";
	tempHeap.dump();

	// function unalteredData() makes sure that the information of students is the same even after reconstructing the heap
	// and the validminHeap() makes sure that the newly constructed heap is a valid min heap. 
	// i.e. priority of parent <= priority of its childern
	if (unalteredData(tempHeap._heap, list) && validMinHeap(tempHeap._heap, tempHeap))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// testing assignment operator
bool Tester::testAssignmentOperator(RQueue& lhs, const RQueue& rhs)
{
	bool valid = false;

	lhs = rhs; 

	// empty object
	if (lhs._heap == nullptr && rhs._heap == nullptr)
	{
		valid = true;
	}

	// self assignment
	else if (&lhs == &rhs)
	{
		cout << "Self-assignment!!!-- Cannot move forward with the process!\n";
		valid = true;

	}

	else if (lhs.numStudents() == rhs.numStudents())
	{
		bool status1 = false; 
		bool status2 = false;

		status1 = (compareTrees(lhs._heap, rhs._heap) && validMinHeap(lhs._heap, lhs)   // comparing the records of both heap
													  && validMinHeap(rhs._heap, rhs)); // and also making sure that the heaps are valid

		// checking for deep copy
		lhs.clear();

		if (rhs.numStudents() != 0) // if the copy is deep, clearing the first heap will not affect the second heap
		{
			status2 = true;
		}
		else
		{
			status2 = false;
		}

		valid = (status1 && status2); 
	}

	return valid;
}

// testing copy constructor
bool Tester::testCopyConstructor(const RQueue& rhs)
{
	bool valid = false;

	RQueue lhs(rhs);

	// empty object
	if (lhs._heap == nullptr && rhs._heap == nullptr)
	{
		valid = true;
	}

	else if (lhs.numStudents() == rhs.numStudents())
	{
		bool status1 = false;
		bool status2 = false;

		status1 = (compareTrees(lhs._heap, rhs._heap) && validMinHeap(lhs._heap, lhs)   // comparing the records of both queue
													  && validMinHeap(rhs._heap, rhs)); // and also making sure that the heap is valid

		// checking for deep copy
		lhs.clear();

		if (rhs.numStudents() != 0) // if the copy is deep, clearing the first heap will not affect the second heap
		{
			status2 = true;
		}
		else
		{
			status2 = false;
		}

		valid = (status1 && status2);
	}

	return valid;
}

// function to make sure that the highest priority obj is deleted everytime we call the getNextStudent()
bool Tester::validExtraction(RQueue& queue)
{
	bool valid = false;

	while (queue._size != 0)
	{
		// 10000 is just a random value
		int highestPriority = findHighestPriority(queue, queue._heap, 10000); // highest priority in the heap

		int extractedPriority = queue.priority(queue.getNextStudent()); // priority of extracted student

		if (extractedPriority == highestPriority)
		{
			valid = true;
		}
		else
		{
			return false;
		}
	}

	return valid;
}

void Tester::insertionPerformance(int numTrials, int inputSize)
{
	//Measuring the efficiency of insertion algorithm with system clock ticks
	//Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
	//Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.

	int a = 1; //scaling factor for input size
	int size = 0;
	clock_t start, stop; //stores the clock ticks while running the program

	double T = 0.0;
	
	Tester tester;

	for (int i = 0; i < numTrials; i++)
	{
		size = a * inputSize;

		RQueue heap(priorityFn1);

		start = clock();

		for (int k = 0; k < size; k++) 
		{
			heap.insertStudent(tester.createStudent()); //the algorithm to be analyzed for efficiency
		}

		stop = clock();

		T = stop - start; //number of clock ticks the algorithm took

		double time = (T / CLOCKS_PER_SEC);

		cout << "Insertion operation took " << T << " clock ticks (" << time << " seconds) to insert " << size << " students." << endl;

		a *= 2;
	}
}

void Tester::extractionPerformance(int numTrials, int inputSize)
{
	//Measuring the efficiency of extraction algorithm with system clock ticks
	//Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
	//Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.

	int a = 1; //scaling factor for input size
	int size = 0;
	clock_t start, stop; //stores the clock ticks while running the program

	double T = 0.0;
	
	Tester tester;

	for (int i = 0; i < numTrials; i++)
	{
		size = a * inputSize;

		RQueue heap(priorityFn1);

		for (int k = 0; k < size; k++) 
		{
			heap.insertStudent(tester.createStudent());
		}

		start = clock();

		for (int j = 0; j < size; j++) //the algorithm to be analyzed for efficiency
		{
			heap.getNextStudent();
		}

		stop = clock();

		T = stop - start; //number of clock ticks the algorithm took

		double time = (T / CLOCKS_PER_SEC);

		cout << "Extraction operation took " << T << " clock ticks (" << time << " seconds) to extract " << size << " students." << endl;

		a *= 2;
	}
}

void Tester::copyConstructorPerformance(int numTrials, int inputSize)
{
	//Measuring the efficiency of copy constructor with system clock ticks
	//Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
	//Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.

	int a = 1; //scaling factor for input size
	int size = 0;
	clock_t start, stop; //stores the clock ticks while running the program

	double T = 0.0;

	Tester tester;

	for (int i = 0; i < numTrials; i++)
	{
		size = a * inputSize;

		RQueue heap(priorityFn1);

		for (int k = 0; k < size; k++)
		{
			heap.insertStudent(tester.createStudent());
		}

		start = clock();

		RQueue tempHeap(heap);
	
		stop = clock();

		T = stop - start; //number of clock ticks the algorithm took

		double time = (T / CLOCKS_PER_SEC);

		cout << "Copy constructor took " << T << " clock ticks (" << time << " seconds) to copy " << size << " students." << endl;

		a *= 2;
	}
}

//----------------------------------------------- // helper functions //-----------------------------------------------//


// makes sure that the nodes follow the min heap prop
// i.e. priority of parent <= priority of its childern
bool Tester::checkMinHeapProp(Node* node, const RQueue& heap)
{
	bool validLeftProp = false;
	bool validRightProp = false;
	if (node == nullptr)
	{
		return true;
	}
	else
	{
		if (node->_left != nullptr)
		{
			if (heap.priority(node->getStudent()) <= heap.priority(node->_left->getStudent()))
			{
				validLeftProp = true;
			}
		}
		else
		{
			validLeftProp = true;
		}

		if (node->_right != nullptr)
		{
			if (heap.priority(node->getStudent()) <= heap.priority(node->_right->getStudent()))
			{
				validRightProp = true;
			}
		}
		else
		{
			validRightProp = true;
		}

		return validLeftProp && validRightProp;
	}
}

// checks if a heap is a valid min heap or not
bool Tester::validMinHeap(Node* node, const RQueue& heap)
{
	if (node == nullptr)
	{
		return true;
	}
	else
	{
		if (checkMinHeapProp(node, heap))
		{
			bool left = checkMinHeapProp(node->_left, heap);
			bool right = checkMinHeapProp(node->_right, heap);

			return left && right;
		}
		else
		{
			return false;
		}
	}

}

// this function compares two nodes and identifies if the values in both nodes are same or not
bool Tester::compareNodes(Node* node, const Student& data)
{
	if (node == nullptr)
	{
		return true;
	}
	else
	{
		if (node->getStudent().getName() == data.getName() && node->getStudent().getPriority() == data.getPriority()
			&& node->getStudent().getYear() == data.getYear() && node->getStudent().getMajor() == data.getMajor()
			&& node->getStudent().getGroup() == data.getGroup())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

// this function checks if the student info is the same after reconstruction the tree 
// uses compareNode() function 
bool Tester::unalteredData(Node* node, map<string, Student> list)
{
	if (node == nullptr)
	{
		return true;
	}
	else
	{
		try
		{
			if (compareNodes(node, (list.at(node->getStudent().getName()))))
			{
				bool left = unalteredData(node->_left, list);
				bool right = unalteredData(node->_right, list);

				return left && right;
			}
			else
			{
				return false;
			}
		}
		catch (...) // not expecting any exceptions
		{
			return false;
		}

	}
}

// compares two tree
// uses compareNode() function to compare nodes in lhs and rhs 
bool Tester::compareTrees(Node* lhs, const Node* rhs)
{
	if (lhs == nullptr && rhs == nullptr)
	{
		return true;
	}
	else
	{
		// uses pre-order traversal
		if (compareNodes(lhs, rhs->getStudent()) == true) // if values are the same in both heaps proceed to another node. 
		{
			bool left = compareTrees(lhs->_left, rhs->_left);
			bool right = compareTrees(lhs->_right, rhs->_right);

			return left && right;
		}
		else
		{
			return false;
		}
	}
}

// finds the highest priority in the tree
int Tester::findHighestPriority(const RQueue& heap, Node* node, int _priority)
{
	if (node == nullptr)
	{
		return _priority;
	}
	else
	{
		int prio = heap.priority(node->getStudent());

		if (prio < _priority)
		{
			_priority = prio;
		}

		_priority = findHighestPriority(heap, node->_left, _priority);
		_priority = findHighestPriority(heap, node->_right, _priority);

		return _priority;
	}
}