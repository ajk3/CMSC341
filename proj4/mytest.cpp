// CMSC 341 - Spring 2021 - Project 4
// mytest.cpp
// test program
#include "hash.h"
#include <random>
#include <vector>
#include <cstdlib>

// Using a fixed seed value generates always the same sequence
// of pseudorandom numbers, e.g. reproducing scientific experiments
// here it helps us with testing since the same sequence repeats
std::mt19937 generator(10);// 10 is the fixed seed value

// We distribute the pseudorandom numbers uniformaly within
// the range [1000,99999]
std::uniform_int_distribution<> distribution(1000, 99999);

// the function to generate random serial numbers
unsigned int vaccineSerial() {return distribution(generator);}

// The hash function used by HashTable class
// The implementation of the hash function
// you can copy this function to your mytest.cpp file
unsigned int hashCode(const string str)
{
    unsigned int val = 0;
    const unsigned int thirtyThree = 33;  // magic number from textbook
    for (int i = 0; i < str.length(); i++)
        val = val * thirtyThree + str[i];
    return val;
}

//---------------------------------------------------------------------------------------------------------------//

class Tester
{ 
   public:

   bool testTableSize(unsigned);
   bool testInsert(int);
   bool testDuplicateInsert();
   bool testRemove();
   bool testDuplicateRemoval();
   bool testLinearProbing();
   bool testQuadProbing();
   bool testRehashAfterInsRmv();
   bool testSetProbPolicy();

   private: 
   bool properlyRehased(unsigned, probing, HashTable&);
   
};

int main()
{
    Tester tester;

    { // testing table size. Size should be the prime number between MINPRIME and MAXPRIME
        cout << "Trying to create a table with a size less than MINPRIME\n";
        if (tester.testTableSize(2))
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing table size. Size should be the prime number between MINPRIME and MAXPRIME
        cout << "Trying to create a table with a size greatetr than MAXPRIME\n";
        if (tester.testTableSize(100000))
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing table size. Size should be the prime number between MINPRIME and MAXPRIME
        cout << "Trying to create a table with a size of 200\n";
        if (tester.testTableSize(200))
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing basic insert
        cout << "Testing insertion operation(inserting 1 element)\n";
        if (tester.testInsert(1))
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing basic insert
        cout << "Testing insertion operation(inserting 26 elements)\n";
        if (tester.testInsert(26))
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing duplicate insertion
        cout << "Testing Duplicate insertion\n";
        if (tester.testDuplicateInsert())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing remove
        cout << "Testing removal operation\n";
        if (tester.testRemove())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing duplicate removal, i.e. trying to remove the obj that has already been removed
        cout << "Testing Duplicate removal\n";
        if (tester.testDuplicateInsert())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;

    }
    
    { // testing linear probing
        cout << "Testing linear probling\n";
        if (tester.testLinearProbing())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;
    }

    { // testing quadratic probing
        cout << "Testing Quadratic probing\n";
        if (tester.testQuadProbing())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;
    }

    { // rehashing after insertion and removal
        cout << "Rehashing after insertion and removal\n";
        if (tester.testRehashAfterInsRmv())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;
    }

    { // testing setProbingPolicy()
        cout << "Testing setProbingPolicy\n";
        if (tester.testSetProbPolicy())
            cout << "\tTest Passed!!!" << endl;
        else
            cout << "\tTest Failed!!!" << endl;
    }

    cout << endl;
    return 0;
}

//-----------------------------------------------------------------------------------------------------------//

bool Tester::testInsert(int size)
{
    vector<Person> people; // holds person obj
    vector<char> characters; // holds uppercase A-Z

    HashTable table(101, hashCode);

    for (int i = 0; i < size; i++) // adding characters to the vector
    {
        characters.push_back(65 + i);
    } 

    for (int i = 0; i < size; i++)
    {
        people.push_back(Person(string(1, characters[i]), vaccineSerial())); // we'll use these objs later
        table.insert(people[i]);
    }

    // as uppercase A has ascii value 65, we are starting our loop from 65
    // and checking if they were inserted in the correct bucket. 
    for (int i = 65; i < (size+65); i++)
    {
        if (!((table.m_table[i].key() == people[i-65].key()) && (table.m_table[i].serial() == people[i-65].serial())))
        {
            return false;
        }
    }

    return true;
}

bool Tester::testDuplicateInsert()
{
    HashTable table(101, hashCode);

    table.insert(Person("A", 1111));  // this will be inserted in bucket 65

    if (table.insert(Person("A", 1111))) // re-inserting the same person
    {
        return false;   // if re-inserted, insert function is not working 
    } 
    else
    {
        return true;
    }
}

bool Tester::testRemove()
{
    constexpr int SIZE = 26;

    Person arr[SIZE]; // holds person obj
    char characters[SIZE]; // holds uppercase A-Z

    HashTable table(101, hashCode);

    for (int i = 0; i < SIZE; i++)
    {
        characters[i] = (65 + i);
    }

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = Person(string(1, characters[i]), vaccineSerial()); // these objs will be used later
        table.insert(arr[i]);
    }

    // as uppercase A has ASCII value 65, we are starting our loop from 65
    // and we will only be deleting 6 elements because deleting the 7th element will rehash the table 
    for (int i = 65; i < ('A' +6); i++)
    {
        table.remove(arr[i - 'A']); // i-65 
        if (!(table.m_table[i].key() == "DELETED" && table.m_table[i].serial() == 0))
        {
            return false;
        }
    }

    return true;
}

// this function will try to remove the obj that has already been removed
bool Tester:: testDuplicateRemoval()
{
    HashTable table(101, hashCode);
    table.insert(Person("A", 1111));  // this will be inserted in bucket 65
 
    table.remove(Person("A", 1111));

    if (table.remove(Person("A", 1111))) // trying to remove it again
    {
        return false;
    }
    else
    {
        return true;
    }
}

// this function tests whether table size is a prime number between MINPRIME and MAXPRIME
bool Tester::testTableSize(unsigned size)
{
    HashTable tempTable(size, hashCode);

    if (size < MINPRIME)
    {
        return (tempTable.m_capacity == MINPRIME) ? true : false;
    }
    else if (size > MAXPRIME)
    {
        return (tempTable.m_capacity == MAXPRIME) ? true : false;
    }
    else
    { 
        return (tempTable.isPrime(tempTable.m_capacity)) ? true : false;
    }
}


bool Tester::testLinearProbing()
{
    bool status1 = false;
    bool status2 = false;

    constexpr int SIZE = 15;

    Person arr[SIZE]; // holds person obj
    char characters[SIZE]; // holds uppercase A-Z

    HashTable table(101, hashCode);

    for (int i = 0; i < SIZE; i++)
    {
        characters[i] = (65 + i);
        table.insert(Person(string(1, characters[i]), vaccineSerial())); // these obj will be inserted from 65 - 79
    }

    for (int i = 0; i < SIZE; i++) // inserting colliding objects
    {
        arr[i] = Person(string(1, characters[i]), vaccineSerial()); // these array elements will be used later during deletion
        table.insert(arr[i]); // if the linear probing in working correctly, these objs will be inserted from 80-94
    }

     // testing insertion
    for (int i = 80; i < (80 + SIZE); i++)
    {
        if (!((arr[i - 80].key() == table.m_table[i].key()) && (arr[i - 80].serial() == table.m_table[i].serial())))
        {
            return false;
        }
    }
        
    status1 = true;
    

    // testing removal
    for (int i = 80; i < (80 +7); i++) // we're only deleting 7 element, as deleting the 8th elemlent rehashes the table
    {
        table.remove(arr[i - 80]);
        if (!(table.m_table[i].key() == DELETED))
        {
            return false;
        }
    }

    status2 = true;
   
    return (status1 && status2);
}

bool Tester::testQuadProbing()
{
    bool status1 = false;
    bool status2 = false;

    constexpr int SIZE = 10;

    Person arr[SIZE]; // holds person obj
    char characters[SIZE]; // holds uppercase A-Z

    HashTable table(101, hashCode);

    table.setProbingPolicy(QUADRATIC);

    for (int i = 0; i < SIZE; i++)
    {
        characters[i] = (65 + i);
        table.insert(Person(string(1, characters[i]), vaccineSerial())); // these obj will be inserted from 65 - 74
    }

    for (int i = 0; i < SIZE; i++) // colliding objects
    {
        arr[i] = Person(string(1, characters[i]), vaccineSerial()); // these array elements will be used later during deletion
        table.insert(arr[i]);
    }

    // if quad probling is working correctly, elements will be inserted into follwing indices
    int idx[SIZE] = {81,75,76,77,78,79,80,88,82,83}; // indices of A-J in the hashTable

   
    // testing insertion
    for (int i = 0; i < SIZE; i++)
    {
        if (!((arr[i].key() == table.m_table[idx[i]].key()) && (arr[i].serial() == table.m_table[idx[i]].serial())))
        {
            return false; // if those collidig objs were not inserted into the desired idx, return false
        }
    }
 
    status1 = true;

  
    // testing removal
    for (int i = 0; i < 5; i++) // we're only deleting 5 element, as deleting the 6th elemlent rehashes the table
    {
        table.remove(arr[i]);
        if (!(table.m_table[idx[i]].key() == DELETED)) // if those collidig objs were not inserted into the desired idx, return false
        {
            return false;
        }
    }

    status2 = true;

    return status1 && status2;
}

bool Tester::testRehashAfterInsRmv()
{ 
    const int SIZE = 26;

    HashTable table(101, hashCode);
    
    bool status1 = false;
    bool status2 = false;

    char characters[SIZE]; // holds uppercase A-Z
    Person people[SIZE - 12]; // holds 14 elements, will be used for remove

    probing oldProb = LINEAR;
    int oldDataPoints = 0;
    unsigned int expectedCapacity = 0;

    for (int i = 0; i < SIZE; i++)
    {
        characters[i] = (65 + i);
    }

    // insert section
    oldProb = table.m_currentProb;
  
    for (int i = 0; i < 50; i++)
    {
        if (i < 14)
        {
            people[i] = Person(string(1, characters[rand()%SIZE]), vaccineSerial()); // these objs will be used later during deletion
            table.insert(people[i]);
        }
        else
        {
            table.insert(Person(string(1, characters[rand() % SIZE]), vaccineSerial()));
        }
    }

    oldDataPoints = table.m_size-table.m_numDeleted;
    expectedCapacity = table.findNextPrime(4 * oldDataPoints);
  
    table.insert(Person(string(1, characters[rand() % SIZE]), vaccineSerial())); // this will cause the rehashing of the table

    status1 = properlyRehased(expectedCapacity, oldProb, table);

    // remove section
    oldProb = table.m_currentProb;

    for (int i = 0; i < 12; i++)
    {
        table.remove(people[i]);
    }

    oldDataPoints = table.m_size - table.m_numDeleted;
    expectedCapacity = table.findNextPrime(4 * oldDataPoints);

    table.remove(people[12]); //this will cause the table to be rehased
  
    status2 = properlyRehased(expectedCapacity, oldProb, table);

    //----------------------------------------------------------------------------------------------//

    return (status1 && status2);
}

bool Tester::testSetProbPolicy()
{
    bool status1 = false;
    bool status2 = false;

    const int SIZE = 26;
    char characters[SIZE]; // holds uppercase A-Z

    for (int i = 0; i < SIZE; i++)
    {
        characters[i] = (65 + i);
    }

    int oldDataPoints = 0;
    int expectedCapacity = 0;
   
    HashTable table(101, hashCode);

    for (int i = 0; i < SIZE; i++)
    {
        table.insert(Person(string(1, characters[rand() % SIZE]), vaccineSerial()));  
    }

    probing oldProb = table.m_currentProb;
    oldDataPoints = table.m_size - table.m_numDeleted;
    expectedCapacity = table.findNextPrime(4 * oldDataPoints);
   
    table.setProbingPolicy(QUADRATIC); // this will change current prob policy to quad

    status1 = properlyRehased(expectedCapacity, oldProb, table);

    //---------------------------------------------

    oldProb = table.m_currentProb;
    oldDataPoints = table.m_size - table.m_numDeleted;
    expectedCapacity = table.findNextPrime(4 * oldDataPoints);

    table.setProbingPolicy(LINEAR);  // this will change current prob policy to linear

    status2 = properlyRehased(expectedCapacity, oldProb, table);

    return (status1 && status2);
} 

//----------------------/ helper function /-----------------------//

bool Tester::properlyRehased(unsigned int expectedCapacity, probing oldProb, HashTable& table)
{
    probing alternateProbing = LINEAR;

    if (oldProb == LINEAR)
    {
        alternateProbing = QUADRATIC;
    }
    else
    {
        alternateProbing = LINEAR;
    }

    if (table.m_currentProb == alternateProbing && table.m_capacity == expectedCapacity)
    {
        for (unsigned int i = 0; i < table.m_capacity; i++)
        {
            if (table.m_table[i] == DELETED) // new table should not contain any deleted objs
            {
                return false;
            }
        }
    }

    return true;
}

