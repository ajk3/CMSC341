#include "bufferlist.h"

#include<iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Tester
{
    public:

    // Tests for Buffer Class
    bool BufferEnqueueDequeue(Buffer&, int);
    bool BufferEnqueueFull(int);
    bool BufferDequeueEmpty();
    bool BufferCopyConstructor(const Buffer&);
    bool BufferAssignmentOperator(const Buffer&);


    // Tests for BufferList Class
    bool BufferListEnqueueDequeue(BufferList&, int);
    bool BufferListDequeueEmpty();
    bool BufferListCopyConstructor(const BufferList&);
    bool BufferListAssignmentOperator(BufferList&);
    void BufListEnqueuePerformance(int, int);

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
      //---------------------------------------------------test cases for Buffer-------------------------------------------------//

      cout << "\n----------------------------------------------test cases for Buffer------------------------------------------------------" << endl;
      {

          Tester tester;

          int bufferSize = 1000;

          Buffer buffer(bufferSize);

          {
              //testing insertion/removal for 1 data item
              cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
              if (tester.BufferEnqueueDequeue(buffer, 1))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing insertion/removal for half data size
              cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
              if (tester.BufferEnqueueDequeue(buffer, bufferSize / 2))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing insertion/removal for full data size
              cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
              if (tester.BufferEnqueueDequeue(buffer, bufferSize))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {   //testing deletion on an empty buffer
              cout << "\nTest case: Buffer class: Throwing exception while deleting in empty buffer:\n";
              if (tester.BufferDequeueEmpty())
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing insertion in a full buffer
              cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
              if (tester.BufferEnqueueFull(1000))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing Buffer class copy constructor with buffer size less than zero
              cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
              Buffer buffer(-10);
              if (tester.BufferCopyConstructor(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing Buffer class copy constructor with buffer size equals zero
              cout << "\nTest case: Buffer class: Copy constructor, buffer size 0:\n";
              Buffer buffer(0);
              if (tester.BufferCopyConstructor(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing Buffer class copy constructor with buffer size 5
              cout << "\nTest case: Buffer class: Copy constructor, with capacity 5:\n";
              Buffer buffer(5);

              buffer.enqueue(12);
              buffer.enqueue(22);
              buffer.enqueue(32);
              buffer.enqueue(42);
              buffer.enqueue(52);

              if (tester.BufferCopyConstructor(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing Buffer class copy constructor with partially initialized buffer
              cout << "\nTest case: Buffer class: Copy constructor, partially initialized buffer:\n";
              Buffer buffer(10);

              buffer.enqueue(12);

              if (tester.BufferCopyConstructor(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing assignment operator with buffer size less than zero
              cout << "\nTest case: Buffer class: Assignment operator, negative buffer size:\n";
              Buffer buffer(-20);

              if (tester.BufferAssignmentOperator(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing assignment operator with buffer size zero
              cout << "\nTest case: Buffer class: Assignment operator, buffer size O:\n";
              Buffer buffer(0);

              if (tester.BufferAssignmentOperator(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }

          {
              //testing Buffer class assignment operator with buffer size 5
              cout << "\nTest case: Buffer class: Assignment operator, with buffer capacity 5:\n";
              Buffer buffer(5);

              buffer.enqueue(12);
              buffer.enqueue(22);
              buffer.enqueue(32);
              buffer.enqueue(42);
              buffer.enqueue(52);

              if (tester.BufferAssignmentOperator(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }

          }

          {
              //testing Buffer class assignment operator with partially initialized buffer
              cout << "\nTest case: Buffer class: Assignment operator, partially initialized buffer:\n";
              Buffer buffer(10);

              buffer.enqueue(12);


              if (tester.BufferAssignmentOperator(buffer))
              {
                  cout << "\tTest passed!\n";
              }
              else
              {
                  cout << "\tTest failed!\n";
              }
          }
      } // end of test cases for buffer

      // ----------------------------------------------------------------------------------------------------test cases for BufferList---------------------------------------------------------//

    cout << "\n----------------------------------------test cases for BufferList-------------------------------------------" << endl;

    {

         Tester tester;
        
        {
            int bufferSize = 500;

            BufferList list(bufferSize);

            {
                //testing insertion/removal for 1 data item
                cout << "\nTest case: BufferList class: Inserting/removing 1 data item:\n";
                if (tester.BufferListEnqueueDequeue(list, 1))
                {
                    cout << "\tTest passed!\n";
                }
                else
                {
                    cout << "\tTest failed!\n";
                }
            }

            {
                //testing insertion/removal for half data size
                cout << "\nTest case: BufferList class: insertion/removal for half data size:\n";
                if (tester.BufferListEnqueueDequeue(list, bufferSize / 2))
                {
                    cout << "\tTest passed!\n";
                }
                else
                {
                    cout << "\tTest failed!\n";
                }
            }

            {
                //testing insertion/removal for twice data size
                cout << "\nTest case: BufferList class: insertion/removal for twice data size:\n";
                if (tester.BufferListEnqueueDequeue(list, bufferSize * 2))
                {
                    cout << "\tTest passed!\n";
                }
                else
                {
                    cout << "\tTest failed!\n";
                }
            }
        }

        {   //testing deletion on an empty buffer
            cout << "\nTest case: BufferList class: Throwing exception while deleting in empty buffer:\n";
            if (tester.BufferListDequeueEmpty())
            {
                cout << "\tTest passed!\n";
            }
            else
            {
                cout << "\tTest failed!\n";
            }
        } 
        
       {
           //testing BufferList class copy constructor with buffer capacity 1
           cout << "\nTest case: BufferList class: Copy constructor, with capacity 1:\n";
           BufferList buffer(1);

           buffer.enqueue(12);

           if (tester.BufferListCopyConstructor(buffer))
           {
               cout << "\tTest passed!\n";
           }
           else
           {
               cout << "\tTest failed!\n";
           }
       }

       {
           //testing BufferList class copy constructor with buffer size 50
           cout << "\nTest case: BufferList class: Copy constructor, with buffer capacity 50:\n";
           BufferList buffer(50);

           for (int i = 0; i < 150; i++) // enqueueing 150 elements
           {
               buffer.enqueue(i);
           }

           if (tester.BufferListCopyConstructor(buffer))
           {
               cout << "\tTest passed!\n";
           }
           else
           {
               cout << "\tTest failed!\n";
           }
       }

       {
           //testing BufferList class copy constructor on partially initialized buffer
           cout << "\nTest case: BufferList class: Copy constructor, partially initialized buffer:\n";
           BufferList buffer(10);

           buffer.enqueue(5);

           if (tester.BufferListCopyConstructor(buffer))
           {
               cout << "\tTest passed!\n";
           }
           else
           {
               cout << "\tTest failed!\n";
           }
       } 

       {
           //testing assignment operator with initial buffer capacity 1
           cout << "\nTest case: BufferList class: Assignment operator: with capacity 1:\n";
           BufferList buffer(1);

           buffer.enqueue(5);

           if (tester.BufferListAssignmentOperator(buffer))
           {
               cout << "\tTest passed!\n";
           }
           else
           {
               cout << "\tTest failed!\n";
           }
       }

       {
           //testing BufferList assignment operator with initial buffer capacity 50
           cout << "\nTest case: BufferList class:  Assignment operator, with capacity 50:\n";
           BufferList buffer(50);

           for (int i = 0; i < 200; i++) // enqueueing 150 elements
           {
               buffer.enqueue(i);
           }

           if (tester.BufferListAssignmentOperator(buffer))
           {
               cout << "\tTest passed!\n";
           }
           else
           {
               cout << "\tTest failed!\n";
           }
       }

       {
           //testing BufferList assignment operator on a partially initialized buffer
           cout << "\nTest case: BufferList class:  Assignment operator, partially initialized buffer:\n";
           BufferList buffer(10);

           buffer.enqueue(5);

           if (tester.BufferListAssignmentOperator(buffer))
           {
               cout << "\tTest passed!\n";
           }
           else
           {
               cout << "\tTest failed!\n";
           }
       }

       {
           //Measuring the efficiency of insertion functionality
           cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
           int M = 5;//number of trials
           int N = 10000;//original input size
           tester.BufListEnqueuePerformance(M, N);
       }

       {
           //an example of BufferList::dump()
           cout << "\nHere is an example of a linked list:" << endl;
           BufferList bufferList(5);
           for (int i = 40; i > 0; i--)
               bufferList.enqueue(i);
           bufferList.dump();
       } 

    } // end of test cases(bufferlist)

        return 0;

} // end of main


    



//--------------------------------------------------------------------------------------------------------------------------------------//


//-------------------------------------------------   function defn (Buffer Class)  ------------------------------------------------------------------//


bool Tester::BufferEnqueueFull(int size)
{
    Buffer aBuffer(size);

    for (int i=0;i<size;i++)
        aBuffer.enqueue(i);
    try{
        //trying to insert in a full buffer
        aBuffer.enqueue(size+1);
    }
    catch(overflow_error& e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester :: BufferDequeueEmpty()
{
    Buffer aBuffer(0);
 
    try 
    {
        //trying to remove in an empty buffer
        aBuffer.dequeue();
    }
    catch (underflow_error& e) {
        //the exception that we expect
        return true;
    }
    catch (...) {
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester :: BufferEnqueueDequeue(Buffer& buffer, int dataCount)
{
    vector<int> enqueued; // holds the values that are enqueued to the buffer
    vector<int> dequeued; // holds the values that are dequeued from the buffer

    int num = 0;

    for (int i = 0; i < dataCount; i++)
    {
        num = i * 10;
        buffer.enqueue(num);
        enqueued.push_back(num);
    }

    for (int j = 0; j < dataCount; j++)
    {
        dequeued.push_back(buffer.dequeue()); // dequeue the element and add it to the vector
    }

    if (enqueued == dequeued) // since our buffer is FIFO, order of insertion should be same as the order of deletion
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tester::BufferCopyConstructor(const Buffer& buffer)
{
    Buffer copy(buffer);
   
    //the case of empty object
    if (buffer.m_capacity == 0 && copy.m_capacity == 0)
    {
        return true;
    }

    //the case that sizes are the same and the buffer pointers are not the same
    else if (buffer.m_capacity == copy.m_capacity && &buffer.m_buffer != &copy.m_buffer)
    {
        for (int j = 0; j < buffer.m_count; j++)
        {
            if ((buffer.m_buffer[j] != copy.m_buffer[j]) || //check the value
                (&buffer.m_buffer[j]) == (&copy.m_buffer[j])) //check the ith pointer
            {   
                return false;
            }
        }
        
        return true;
    }
    //everthing else

    else
    {
        return false;
    } 
} 

bool Tester::BufferAssignmentOperator(const Buffer& buffer)
{
    Buffer copy = buffer;

    //the case of empty object
    if (buffer.m_capacity == 0 && copy.m_capacity == 0)
    {
        return true;
    }

    else if (&copy == &buffer)
    {
        return false; // checking for self assignment
    }
    //the case that sizes are the same and the buffer pointers are not the same
    else if (buffer.m_capacity == copy.m_capacity && &buffer.m_buffer != &copy.m_buffer)
    {
        for (int j = 0; j < buffer.m_count; j++)
        {
            if ((buffer.m_buffer[j] != copy.m_buffer[j]) || //check the value
                (&buffer.m_buffer[j]) == (&copy.m_buffer[j])) //check the ith pointer
            {
                return false;
            }
        }

        return true;
    }
    //everthing else
    else return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------//


//--------------------------------------  function defn (BufferList Class)   ------------------------------------------------------------------------------------------------//

bool Tester::BufferListEnqueueDequeue(BufferList& buffer, int dataCount)
{
    vector<int> enqueued; // holds the values that are enqueued to the buffer
    vector<int> dequeued; // holds the values that are dequeued from the buffer

    int num = 0;

    for (int i = 0; i < dataCount; i++)
    {
        num = i * 10;
        buffer.enqueue(num);
        enqueued.push_back(num);
    }


    for (int j = 0; j < dataCount; j++)
    {
        dequeued.push_back(buffer.dequeue()); // dequeue the element and add it to the vector
    }

    if (enqueued == dequeued) // if two buffer contains same sequence of elements
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tester::BufferListDequeueEmpty()
{
    BufferList list(10);

    try
    {
        //trying to remove from an empty buffer
        list.dequeue();
    }
    catch (underflow_error& e) {
        //the exception that we expect
        return true;
    }
    catch (...) {
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

void Tester::BufListEnqueuePerformance(int numTrials, int inputSize)
{
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.

    int a = 1; //scaling factor for input size
    int size = 0;
    clock_t start, stop; //stores the clock ticks while running the program

    double T = 0.0;
    double timeInSec = 0;

    vector<double> time; // stores instertion time

    for (int i = 0; i < numTrials; i++)
    {
        size = a * inputSize;
        
        BufferList tempBuffer(size);

        start = clock();

        for (int k = 0; k < size; k++) //the algorithm to be analyzed for efficiency
        {
            tempBuffer.enqueue(k);
        }

        stop = clock();

        T = stop - start; //number of clock ticks the algorithm took

        time.push_back(T / CLOCKS_PER_SEC);

        cout << "Insertion operation took " << T << " clock ticks (" << time[i] << " seconds) to enqueue " << size << " elements." << endl;

        a+=2;
    }

    {
        // displaying the insertion time in table

        int initalEle = inputSize;; // holds initial number of elements

        int nextSize = 0;
        int scale = 1;

        cout << "\nTime comparision: " << endl;
        cout << left << setw(20) << "Input(n)" << setw(20) << "Time(sec)" << setw(20) << "n increased by" << setw(20) << "time increased by" << endl;

        for (int i = 0; i < time.size(); i++)
        {
            nextSize = scale * initalEle;

            cout << left << setw(20) << nextSize << setw(20) << time[i] << setw(20) << (nextSize / initalEle) << setw(20) << static_cast<int> (time[i] / time[0]) << endl;

            scale+=2;
        }
    }
}


bool Tester :: BufferListAssignmentOperator(BufferList& rhs)
{
    BufferList lhs(100);
    
    lhs = rhs;

    Buffer* lhsPtr = lhs.m_cursor->m_next; // points to oldest node of lhs

    Buffer* rhsPtr = rhs.m_cursor->m_next; // points to newest node of rhs

    if (lhs.m_listSize != rhs.m_listSize)
    {
        return false; // if number of nodes doesn't match, there's something wrong with the assignment
    }
    // same list size but different pointer
    else if (lhs.m_listSize == rhs.m_listSize && lhsPtr != rhsPtr)
    {
        for (int i = 0; i < rhs.m_listSize; i++)
        {
            for (int j = 0; j < rhsPtr->count(); j++)
            {
                if ((lhsPtr->m_buffer[j] != rhsPtr->m_buffer[j]) || // compare value
                    (lhsPtr == rhsPtr)) // compare pointer
                {
                    return false;
                }
            }
            lhsPtr = lhsPtr->m_next; // move the pointer
            rhsPtr = rhsPtr->m_next; // move the pointer
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Tester::BufferListCopyConstructor(const BufferList& rhs)
{
    BufferList lhs(rhs);

    Buffer* lhsPtr = lhs.m_cursor->m_next; // points to oldest node of lhs

    Buffer* rhsPtr = rhs.m_cursor->m_next; // points to newest node of rhs

    if (lhs.m_listSize != rhs.m_listSize)
    {
        return false; // if number of nodes doesn't match, there's something wrong with copy constructor
    }
    else if (lhs.m_listSize == rhs.m_listSize && lhsPtr != rhsPtr)
    {
         for (int i = 0; i < rhs.m_listSize; i++)
         {
            for (int j = 0; j < rhsPtr->count(); j++)
            {  
                if ((lhsPtr->m_buffer[j] != rhsPtr->m_buffer[j]) || // compare value
                    (lhsPtr == rhsPtr)) // compare pointer
                {
                    return false;
                } 
            }
            lhsPtr = lhsPtr->m_next; // move the pointer
            rhsPtr = rhsPtr->m_next; // move the pointer
         }
        return true;
    }
    else
    {
        return false;
    }
   
    return true;
}


