// CMSC 341 - Spring 2021 - Project 3
// RQueue: 

#include "rqueue.h"

using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
  /************************
   * To be implemented
   * *********************/

    _heap = nullptr; 
    _size = 0;
    priority = priFn;
}

RQueue::~RQueue()
{
  /************************
   * To be implemented
   * *********************/
    clear();
}

RQueue::RQueue(const RQueue& rhs)
{
  /************************
   * To be implemented
   * *********************/

    if (rhs._heap != nullptr)
    {
        this->_size = rhs._size;
        this->priority = rhs.priority;
        copyNodes(this->_heap, rhs._heap);
    }
    else
    {
        _heap = nullptr;
        _size = 0;
        priority = nullptr;
    }
}


RQueue& RQueue::operator=(const RQueue& rhs)
{
  /************************
   * To be implemented
   * *********************/

    if (this != &rhs) // guarding against self assignment
    {
        this->clear();

        this->_size = rhs._size;
        this->priority = rhs.priority;
        copyNodes(this->_heap, rhs._heap);
    }
    return *this;
}

void RQueue::insertStudent(const Student& input) {
  /************************
   * To be implemented
   * *********************/

    Node* tempRhs = new Node(input);
    this->_heap = merge(this->_heap, tempRhs);
    _size++;
}

Student RQueue::getNextStudent() {
  /************************
   * To be implemented
   * *********************/

    Student removed;

    if (this->_size == 0)
    {
        throw domain_error("Queue is empty!!!!");
    }
    else
    {
        this->_heap = removeNode(this->_heap, removed);  // variable removed is passed by refernce
        this->_size--;
    }

    return removed;
}


void RQueue::mergeWithQueue(RQueue& rhs) {
  /************************
   * To be implemented
   * *********************/
    
    if (this->getPriorityFn() != rhs.getPriorityFn()) // making sure that the priority fucntion are the same for both queues
    {
        throw domain_error("Queues with different priority functions can't be merged!!!!");
    }

    if (this != &rhs) // guarding against the self-merging
    {
        this->_heap = merge(this->_heap, rhs._heap);
        this->_size = this->_size + rhs._size; // update the size

        rhs._heap = nullptr;
        rhs._size = 0;
    }
}

void RQueue::clear()
{
  /************************
   * To be implemented
   * *********************/
    deleteNodes(_heap); // call tp the hepler function to delete the nodes
    
    _heap = nullptr;
    _size = 0;
    priority = nullptr;
}

int RQueue::numStudents() const
{
  /************************
   * To be implemented
   * *********************/

    return this->_size;
}

void RQueue::printStudentQueue() const {
  /************************
   * To be implemented
   * *********************/
    cout << "Contents of the student queue :" << endl;
    printRecords(_heap);
}

prifn_t RQueue::getPriorityFn() const 
{
  /************************
   * To be implemented
   * *********************/

    return priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  /************************
   * To be implemented
   * *********************/

    priority = priFn;
    reconstruct(*this);
    
}

// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->_left);
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}


//---------------------------------------------- /* helper functions */ ---------------------------------------------------------------------

// deallocates all the nodes in the skew heap, leaves the skew heap empty
void RQueue::deleteNodes(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {   
        // uses postorder travesal to delete the nodes
        deleteNodes(node->_left);
        deleteNodes(node->_right);
        delete node;
    }
}

// merges two node into a single heap
Node* RQueue :: merge(Node* lhs, Node* rhs)
{
    if (lhs == nullptr)
    {
        return rhs;
    }
    if (rhs == nullptr)
    {
        return lhs;
    }

    if ((priority(lhs->getStudent()) > priority(rhs->getStudent()))) // making sure that the lhs has the higher priority
    {
        swap(lhs, rhs);
    }

    swap(lhs->_left, lhs->_right); //swapping the chlidern of lhs

    lhs->_left = merge(lhs->_left, rhs);

    return lhs;   
}

void RQueue::swap(Node*& lhs, Node*& rhs)
{
    Node* temp = nullptr;

    temp = lhs;
    lhs = rhs;
    rhs = temp;
}

void RQueue::printRecords(Node* node) const
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        // uses preorder travesal to print the content of the tree
        //[0] Student: Nick, priority : 2, year : 0, major : CS, group : Minority
        
        cout << "[" << priority(node->getStudent()) << "] " << node->getStudent() << endl;
        printRecords(node->_left);
        printRecords(node->_right);
    }
}

// removes highest priority node from the tree
Node* RQueue::removeNode(Node* node, Student& tempStd)
{
    Node* removed = node;
    Node* left = node->_left;
    Node* right = node->_right;

    left = merge(left, right);
    tempStd = removed->getStudent();
    delete removed;

    return left;
}

// recreates the tree after changing the priority function
void RQueue::reconstruct(RQueue& oldHeap)
{
    RQueue tempHeap(getPriorityFn());

    while (oldHeap._size != 0)
    {
        Node* newNode = new Node(oldHeap.getNextStudent());
        tempHeap._heap = merge(tempHeap._heap, newNode);
        tempHeap._size++;
    }

    oldHeap._heap = tempHeap._heap;
    oldHeap._size = tempHeap._size;
    
    tempHeap._heap = nullptr;
}


void RQueue::copyNodes(Node*& lhs, const Node* rhs)
{
    if (rhs == nullptr)
    {
        return;
    }
    else
    {
        lhs = new Node(rhs->getStudent());
        copyNodes(lhs->_left, rhs->_left);
        copyNodes(lhs->_right, rhs->_right);
    }
}
