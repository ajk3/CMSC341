#include "bufferlist.h"

BufferList::BufferList(int minBufCapacity)
{
    // **************************************
    // Implement the alternative constructor
    // **************************************

    m_cursor = nullptr;
    m_listSize = 0; 
    
    if (minBufCapacity < 1)
    {
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;
    }
    else
    {
        m_minBufCapacity = minBufCapacity;
    }

    // creates a new node that points to the new buffer
    m_cursor = new Buffer(m_minBufCapacity);
    m_listSize++;
    
    m_cursor->m_next = m_cursor; // since there is only one node in the list, next is pointing to itself
    
}

BufferList::~BufferList()
{
    clear();
}

void BufferList::clear()
{
    // *****************************
    // Implement clear() function
    // *****************************

  if (m_listSize != 0)
  {
      for (int i = 0; i < m_listSize; i++)
      {
          Buffer* tempPtr = (m_cursor->m_next);
          m_cursor->m_next = tempPtr->m_next;
          tempPtr->clear();
          delete tempPtr;  
      }

      m_listSize = 0; // at this point the list is empty
  }
}
void BufferList::enqueue(const int& data)
{
    // ****************************************************************************
    // Implement enqueue(...) function
    // we always insert at the back, that would be the cursor
    // if the current cursor is full we create a new node as cursor then we insert
    // ****************************************************************************

    // if the queue is not full, add data to existing buffer
    if (!m_cursor->full())
    {
        m_cursor->enqueue(data);
    }
    else
    {
        int size = m_cursor->capacity() * INCREASE_FACTOR;  
        int max = MAX_FACTOR * m_minBufCapacity;              


        // if we excced the max capacity, new buffer with the minBufCapacity will be created

        if (size <= max) 
        {
            addNewNode(size);
        }
        
        else
        {
            addNewNode(m_minBufCapacity);
        }

        m_cursor->enqueue(data); // adding data to the new buffer
    }
}

int BufferList::dequeue() {
    // *****************************
    // Implement dequeue() function
    // *****************************

    Buffer* tempCursor = nullptr; // points to the node that is to be deleted

    int val = 0;

    bool lastEmptyBuffer = (m_listSize == 1 && m_cursor->m_next->empty()); // checking to see if that's the last buffer and is empty

    if (lastEmptyBuffer)
    {
        throw underflow_error("The buffer is empty!!!\n");
    }

    else if (!(m_cursor->m_next)->empty())
    {
        val = m_cursor->m_next->dequeue();
        
        lastEmptyBuffer = (m_listSize == 1 && m_cursor->empty());

        if ((m_cursor->m_next)->empty() && !lastEmptyBuffer) // if the buffer is empty, but is not the last one, delete the node
        {
            tempCursor = m_cursor->m_next;

            m_cursor->m_next = (m_cursor->m_next)->m_next;

            tempCursor->clear();

	        delete tempCursor;
	    
            m_listSize--;
        }
    }
    
    return val;
}

BufferList::BufferList(const BufferList & rhs)
{
    // *******************************
    // Implement the copy constructor
    // *******************************

    {
        m_listSize = rhs.m_listSize;
        m_minBufCapacity = rhs.m_minBufCapacity;

        Buffer* tempRhs = rhs.m_cursor; // points to the original buffer (rhs)

        Buffer* tempLhs = this->m_cursor = new Buffer(*tempRhs); // points to the new buffer (lhs)
        tempLhs->m_next = m_cursor; 
       

        for (int i = 2; i <= m_listSize; i++) // starts from 2 because we have already copied first buffer
        {
            tempRhs = tempRhs->m_next; // move the rhs pointer

            tempLhs->m_next = new Buffer(*tempRhs); // copy the elements

            tempLhs = tempLhs->m_next; // move the lhs pointer to point to the new buffer

            tempLhs->m_next = m_cursor;
        }
    }

}

const BufferList & BufferList::operator=(const BufferList & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************

    if (this != &rhs) // checking for self assigment
    {
        delete m_cursor; // deleting the old chunk of memory

        m_listSize = rhs.m_listSize;
        m_minBufCapacity = rhs.m_minBufCapacity;

        // allocating new memeory for the node
        Buffer* tempRhs = rhs.m_cursor; // points to the original buffer

        Buffer* tempLhs = this->m_cursor = new Buffer(*tempRhs); // points to the new buffer
        tempLhs->m_next = m_cursor;


        for (int i = 2; i <= m_listSize; i++) // starts from 2 because we have already copied the first buffer
        {
            tempRhs = tempRhs->m_next; // move the rhs pointer

            tempLhs->m_next = new Buffer(*tempRhs); // copy the elements

            tempLhs = tempLhs->m_next; // move the lhs pointer to point to the new buffer

            tempLhs->m_next = m_cursor;
        }
    }


    return *this;
}

void BufferList::dump()
{
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}


// this function creates a new node and adds it to the circular list
void BufferList::addNewNode(const int size)
{
    Buffer* temp = new Buffer(size);

    {
        temp->m_next = m_cursor->m_next;
        m_cursor->m_next = temp;
        m_cursor = temp;   
    }
    
    m_listSize++;
}
