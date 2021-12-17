#include "buffer.h"

Buffer::Buffer(int capacity){
    m_buffer = nullptr;
    m_capacity = (capacity < 1) ? 0 : capacity; // if the parameter is less than 1, set m_capacity to 0 

    if(m_capacity != 0)
    {
        m_buffer = new int[m_capacity];
    }

    m_count = 0;
    m_start = 0;
    m_end = 0;
    m_next = nullptr;
}

void Buffer::clear()
{
    if (m_capacity != 0)
    {
        delete[] m_buffer; // deleting the array
        m_buffer = nullptr;
    }

    // re-initalizing member variables
    m_next = nullptr;
    m_capacity = 0;
    m_count = 0;
    m_start = 0;
    m_end = 0;
}


Buffer::~Buffer()
{
    clear();
}

int Buffer::count(){return m_count;}

int Buffer::capacity(){return m_capacity;}

bool Buffer::full()
{
    if (count() == capacity()) // if num of element == available space
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Buffer::empty()
{
    if (capacity() != 0 && count() == 0) // spaces are available but there are no elements
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Buffer::enqueue(int data)
{
    // ********************************
    // Implement enqueue(...) function
    // ********************************

    if (full() || capacity() == 0)
    {
        throw overflow_error("ERROR!!!! The Queue is full. Operation couldn't be completed at this moment!\n");
    }
    else
    { 
        m_end = m_end % capacity(); // helps us go around the array in circle

        m_buffer[m_end] = data;

        m_end++;
        m_count++;
    }
}

int Buffer::dequeue()
{
    // *****************************
    // Implement dequeue() function
    // *****************************

    int val = 0; // to hold the value that is to be returned

    if (empty() || capacity() == 0)
    {
        throw underflow_error("ERROR!!!! The Queue is empty. Operation couldn't be completed at this moment!\n");
    }
    else
    {
        m_start = m_start % capacity(); // helps us go around the array in a circle

        val = m_buffer[m_start];

        m_start++;
        m_count--;
    }

    return val;
}

Buffer::Buffer(const Buffer & rhs)
{
    // *******************************
    // Implement the copy constructor
    // *******************************

    // copying the values over
    m_capacity = rhs.m_capacity;
    m_count = rhs.m_count;
    m_start = rhs.m_start;
    m_end = rhs.m_end;
    

    if (!(m_capacity <= 0))
    {
       m_buffer = new int [rhs.m_capacity];

       for (int i = 0; i < rhs.m_capacity; i++)
       {
          m_buffer[i] = (rhs.m_buffer[i]);
       }
    }
}

const Buffer & Buffer::operator=(const Buffer & rhs)
{
    // ******************************
    // Implement assignment operator
    // ******************************

   if (this != &rhs) // checking for self assigment
   {
        delete[] m_buffer; // deleting old chunk of memory

        m_capacity = rhs.m_capacity;
        m_count = rhs.m_count;
        m_start = rhs.m_start;
        m_end = rhs.m_end;

        // allocating new memeory for the array
        m_buffer = new int[m_capacity];

        for (int i = 0; i < m_capacity; i++)
        {
            m_buffer[i] = rhs.m_buffer[i];
        }
   }

    return *this;
}

void Buffer::dump(){
    int start = m_start;
    int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}
