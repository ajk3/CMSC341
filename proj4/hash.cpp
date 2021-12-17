// CMSC 341 - Spring 2021 - Project 4
// hash.cpp
// The implementation of the class HashTable

#include "hash.h"
#include "math.h"

HashTable::HashTable(unsigned size, hash_fn hash)
{
    int capacity = 0;

    if (!isPrime(size))
    {
        capacity = findNextPrime(size);
    }
    else
    {
        if (size < MINPRIME)
        {
            capacity = MINPRIME;
        }
        else if (size > MAXPRIME)
        {
            capacity = MAXPRIME;
        }
        else
        {
            capacity = size;
        }

    }

    m_capacity = capacity;
    m_size = m_numDeleted = 0;
    m_hash = hash;
    m_currentProb = LINEAR;

    m_table = new Person[m_capacity]; // hash table

    for (unsigned int i = 0; i < m_capacity; i++)
    {
        m_table[i] = EMPTY;
    }    
}

HashTable::~HashTable()
{
    clear(m_table);
}

bool HashTable::insert(Person person)
{
    bool status = false;

    if (search(m_table, person) == -1) // if not found
    {
        status = insHelper(m_table, person);

        if (status == true && checkForInsRehash(m_table))
        {
            if (m_currentProb == LINEAR)
            {
                setProbingPolicy(QUADRATIC);
            }
            else
            {
                setProbingPolicy(LINEAR);
            }
        }
    }
  
    return status;
}

bool HashTable::remove(Person person)
{
    bool status = false;

    int index = search(m_table, person);

    if (index != -1)
    {
        status = rmvHelper(m_table, person, index);

        if (status == true && checkForRmvRehash(m_table))
        {
            if (m_currentProb == LINEAR)
            {
                setProbingPolicy(QUADRATIC);
            }
            else
            {
                setProbingPolicy(LINEAR);
            }
        }
    }
    return status;
}


void HashTable::setProbingPolicy(probing prob)
{
    int dataPoint = (m_size - m_numDeleted);

    int newCapacity = findNextPrime(4 * dataPoint);

    HashTable temp(newCapacity, this->m_hash);

    if (prob == LINEAR)
    {
        temp.m_currentProb = LINEAR;

        for (unsigned int i = 0; i < m_capacity; i++)
        {
            if (this->m_table[i].key() != "" && this->m_table[i].key() != "DELETED") // we don't want to insert deleted objs in our new table
            {
                temp.insert(this->m_table[i]);
            }
        }
    }
    else
    {
        temp.m_currentProb = QUADRATIC;

        for (unsigned int i = 0; i < m_capacity; i++)
        {
            if (this->m_table[i].key() != "" && this->m_table[i].key() != "DELETED") // if not empty and not deleted
            {
                temp.insert(this->m_table[i]);
            }
        }
    }

    *this = temp;
}

float HashTable::lambda() const 
{
    return (m_size / (float) m_capacity);
}

float HashTable::deletedRatio() const 
{
    return (m_numDeleted / (float) m_size);
}

void HashTable::dump() const {
  for (int i = 0; i < m_capacity; i++) {
    cout << "[" << i << "] : " << m_table[i] << endl;
  }
}

bool HashTable::isPrime(int number){
    // If number is prime this function returns true
    // otherwise it returns false
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we won't go beyond MAXPRIME
    //the smallest prime would be next after MINPRIME
    if (current < MINPRIME) current = MINPRIME;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

//--------------------------------------------------------------------------------------------------------

// deallocates the memory
void HashTable:: clear(Person arr[])
{
    if (m_capacity != 0)
    {
        delete[] arr;

        m_capacity = m_size = m_numDeleted = 0;
        m_hash = nullptr;
        m_table = nullptr;
    }
}

// inserts person into the correct bucket based on current policy
bool HashTable::insHelper(Person arr[], Person person)
{
    int size = m_capacity;
  
    int idx = 0;
    int i = 0;

    int bucketProbed = 0;

    if (m_currentProb == LINEAR)
    {
        while (bucketProbed < size)
        {
            idx = (m_hash(person.key()) + i) % size;

            if (arr[idx] == EMPTY)
            {
                arr[idx] = person;
                m_size++;
                return true;
            }

            i++;
            bucketProbed++;
        }

        return false;
    }
    else
    {
        while (bucketProbed < size)
        {
            idx = ((m_hash(person.key()) % size) + (i * i)) % size;
                
            if (arr[idx] == EMPTY)
            {
                arr[idx] = person;
                m_size++;
                return true;
            }

            i++;
            bucketProbed++;
        }

        return false;
    }
}

// uses idx parameter to delete the person
bool HashTable:: rmvHelper(Person arr[], Person person, int idx)
{
    arr[idx] = DELETED;
    m_numDeleted++;

    return true;   
}

// checks whether rehash is required after insertion
bool HashTable:: checkForInsRehash(const Person* arr)
{
    if (lambda() > 0.5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// checks whether rehash is required after removal
bool HashTable::checkForRmvRehash(const Person[])
{
    if (deletedRatio() > 0.25)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// looks for the person passed in as the parameter
int HashTable::search(const Person arr[], const Person& person)
{
    int size = m_capacity;
    int idx = -1;

    int bucket = 0;
    int bucketProbed = 0;
    int i = 0;

    if (m_currentProb == LINEAR)
    {
        bucket = (m_hash(person.key()) + i) % size;

        while (bucketProbed < size && !(arr[bucket] == EMPTY))
        {
            if (arr[bucket] == person)
            {
                idx = bucket;
                return idx;
            }

            i++;
            bucketProbed++;

            bucket = (m_hash(person.key()) + i) % size;
        }

        return idx;
        
    }
    else
    {
        bucket = ((m_hash(person.key()) % size) + (i * i)) % size;

        while (bucketProbed < size && !(arr[bucket] == EMPTY))
        {
            if (arr[bucket] == person)
            {
                idx = bucket;
                return idx;
            }

            i++;
            bucketProbed++;

            bucket = ((m_hash(person.key()) % size) + (i * i)) % size;
        }

        return idx;
    }

}

const HashTable& HashTable :: operator=(const HashTable& rhs) // overloaded assignment operator
{
    if (this != &rhs)
    {
        delete[] m_table;

        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_numDeleted = rhs.m_numDeleted;
        m_hash = rhs.m_hash;
        m_currentProb = rhs.m_currentProb;

        m_table = new Person[m_capacity];

        for (unsigned int i = 0; i < m_capacity; i++)
        {
            m_table[i] = rhs.m_table[i];
        }
    }

    return *this;
}
