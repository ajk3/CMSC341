#include "utree.h"
#include <random>
#include <iostream>


#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester 
{
public:

    //--------------------------------------------------  // test cases for dtree // ---------------------------------------------------------------------

    bool testBasicDTreeInsert(DTree& dtree);
    bool testAssignmentOop(DTree& dtree1, const DTree& dtree2);
    bool testDTreeRemove(DTree& dtree);
    bool checkDtreeBstProp(DTree& dtree);

    // helper functions used by testAssignmentOop
    bool compareTrees(DNode* rootT1, DNode* rootT2);
    bool compareData(DNode* rootT1, DNode* rootT2);

    // helper functions used by checkDTreeBstProp
    bool holdsBstProp(DNode* node);
    bool validBstProp(DNode* node);

  //--------------------------------------------------  // test cases for utree // ---------------------------------------------------------------------
    bool testBasicUTreeInsert(UTree& utree);
    bool testUTreeRemove(UTree& utree);
    bool checkUtreeBstProp(UTree& utree);

    // helper functions used by checkDTreeBstProp
    bool holdsBstProp(UNode* node);
    bool validBstProp(UNode* node);

};

int main()
{
    Tester tester;
    cout << " ---------------------------------------------------------  DTree tests --------------------------------------------------------------------------------------" << endl;
    //--------------------------------------------------------- /*  DTree tests */ --------------------------------------------------------------------------------------//
    {
        /* Basic dtree tests */
        
        
        // basic insertion
        {
            DTree dtree;

            cout << "Testing DTree insertion...";
            if (tester.testBasicDTreeInsert(dtree)) {
                cout << "test passed" << endl;
            }
            else {
                cout << "test failed" << endl;
            }

            cout << "Resulting DTree:" << endl;
            dtree.dump();
            cout << endl << endl;
        }

        // inserting duplicate value
        {
            Account acc1("", 10, 1, "", "");
            Account acc2("", 10, 1, "", "");

            DTree dtree;
            dtree.insert(acc1);
            bool inserted = dtree.insert(acc2);

            cout << "Testing DTree insert with duplicate value.....";
            if (inserted == false)
            {
                cout << "test passed" << endl;
            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting DTree:" << endl;
            dtree.dump();
            cout << endl << endl;

        }

        // basic removal
        {
            DTree dtree;

            cout << "Testing DTree removal...";
            if (tester.testDTreeRemove(dtree)) {
                cout << "test passed" << endl;
            }
            else {
                cout << "test failed" << endl;
            }

            cout << "Resulting DTree:" << endl;
            dtree.dump();
            cout << endl << endl;
        }


        // removing from an empty tree
        {
            Account acc1("", 10, 1, "", "");
            Account acc2("", 20, 1, "", "");

            DTree dtree;
            dtree.insert(acc1);
            dtree.insert(acc2);
            DNode* removed = nullptr;

            dtree.clear(); //  clearing the tree
            dtree.remove(20, removed); // if the node was present and deleted, removed will hold pointer to the node

            cout << "Testing DTree removal on an empty tree.....";
            if (removed == nullptr)
            {
                cout << "test passed" << endl;
            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting DTree:" << endl;
            if (removed == nullptr)
            {
                cout << "The tree is empty!!!";
            }
            else
            {
                dtree.dump();
            }

            cout << endl << endl;
        }
        

        // testing assignment operaotr
        {
            DTree dtree;
            DTree dtree1;
            Account acc1("", 10, 1, "", "");
            Account acc2("", 20, 1, "", "");
            Account acc3("", 30, 1, "", "");
            Account acc4("", 40, 1, "", "");

            dtree.insert(acc1);
            dtree.insert(acc2);
            dtree.insert(acc3);
            dtree.insert(acc4);

            cout << "Testing DTree assignment operaotr.....";
            if (tester.testAssignmentOop(dtree1, dtree) == true)
            {
                cout << "test passed" << endl;

            }
            else
            {
                cout << "test failed" << endl;
            }
            cout << endl;

        }

        // testing assignment operaotr on empty trees
        {
            DTree dtree;
            DTree dtree1;
          
            cout << "Testing DTree assignment operaotr (empty tree).....";
            if (tester.testAssignmentOop(dtree1, dtree) == true)
            {
                cout << "test passed" << endl;

            }
            else
            {
                cout << "test failed" << endl;
            }
            cout << endl;
        }

        // testing assignment operaotr on empty trees
        {
            DTree dtree;
            Account acc1("", 10, 1, "", "");
            dtree.insert(acc1);
         
            cout << "Testing DTree assignment operaotr (self-assignment)";
            if (tester.testAssignmentOop(dtree, dtree) == true)
            {
                cout << "test passed" << endl;

            }
            else
            {
                cout << "test failed" << endl;
            }
            cout << endl;
        } 


        // testing Bst prop
        {
            DTree dtree;
          
            cout << "Testing BST prop on dtree.......";
            if (tester.checkDtreeBstProp(dtree) == true)
            {
                cout << "test passed" << endl;

            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting DTree:" << endl;
            dtree.dump();
            cout << endl << endl;
        }


    }
    cout << " ---------------------------------------------------------  UTree tests --------------------------------------------------------------------------------------" << endl;
    //--------------------------------------------------------- /* UTree tests */ --------------------------------------------------------------------------------------//
    {
        
        {
            UTree utree;

            cout << "\n\nTesting UTree insertion...";
            if (tester.testBasicUTreeInsert(utree))
            {
                cout << "test passed" << endl;
            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting UTree:" << endl;
            utree.dump();
            cout << endl << endl;
        }

        // inserting duplicate value
        {
            UTree utree;

            Account acc1("Hey", 10, 1, "", "");
            Account acc2("Hey", 10, 1, "", "");

            utree.insert(acc1);
            bool inserted = utree.insert(acc2);

            cout << "Testing DTree insert with duplicate value.....";
            if (inserted == false)
            {
                cout << "test passed" << endl;
            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting UTree:" << endl;
            utree.dump();
            cout << endl << endl;

        }

        // testing utree removal
        {
            UTree utree;

            cout << "Testing UTree removal...";
            if (tester.testUTreeRemove(utree))
            {
                cout << "test passed" << endl;
            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting UTree:" << endl;
            utree.dump();
            cout << endl << endl;
        }



        // removing from an empty tree
        {
            Account acc1("hello", 10, 1, "", "");
            Account acc2("hey", 20, 1, "", "");

            UTree utree;
            utree.insert(acc1);
            utree.insert(acc2);


            DNode* removed = nullptr;

            utree.clear(); //  clearing the tree

            utree.removeUser("hey", 20, removed); // looking for the preveiously stored account

            cout << "Testing UTree removal on an empty tree.....";

            if (removed == nullptr)
            {
                cout << "test passed" << endl;
            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting UTree:" << endl;
            if (removed == nullptr)
            {
                cout << "The tree is empty!!!" << endl << endl;
            }
            else
            {
                utree.dump();
                cout << endl << endl;
            }
        }

        // testing Bst prop
        {
            UTree utree;

            cout << "Testing BST prop on UTree.......";
            if (tester.checkUtreeBstProp(utree) == true)
            {
                cout << "test passed" << endl;

            }
            else
            {
                cout << "test failed" << endl;
            }

            cout << "Resulting UTree:" << endl;
            utree.dump();
            cout << endl << endl;
        }
    }

    return 0;
}

//----------------------------------------------------------------- DTree -------------------------------------------------------------------------------------//

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for (int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");

        // cout << "Disc: " << endl;
        if (!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}

bool Tester::testDTreeRemove(DTree& dtree)
{

    {
        Account acc1("", 10, 1, "", "");
        dtree.insert(acc1);
    }
    {
        Account acc1("", 5, 1, "", "");
        dtree.insert(acc1);
    }
    {
        Account acc1("", 18, 1, "", "");
        dtree.insert(acc1);
    }
    {
        Account acc1("", 15, 1, "", "");
        dtree.insert(acc1);
    }
    {
        Account acc1("", 88, 1, "", "");
        dtree.insert(acc1);
    }
    {
        Account acc1("", 16, 1, "", "");
        dtree.insert(acc1);
    }
    {
        // removing 16
        DNode* removed1;
        dtree.remove(5, removed1);
    }
    {
        Account acc1("", 17, 1, "", "");
        dtree.insert(acc1);
    }
   
    if (dtree._root->getNumVacant() == 0) // vacant nodes will be deleted
        return true;
    else
        return false;
}

// testing assignment oop
bool Tester::testAssignmentOop(DTree& dtree1, const DTree& dtree2)
{
    dtree1 = dtree2;
    bool valid = false;

    //the case of empty object
    if (dtree1._root == nullptr && dtree2._root == nullptr)
    {
        valid = true;
    }

    // self assignment
    else if (&dtree1 == &dtree2)
    {
        cout << "\nSelf-assignment!!!-- Cannot move forward with the process........";
        valid = true;

    }

    // checking for the deep copy
    else if (dtree1.getNumUsers() == dtree2.getNumUsers())
    {
        bool status1 = false;
        bool status2 = false;

        status1 = compareTrees(dtree1._root, dtree2._root); // comparing values

        // checking for deep copy
        dtree1.clear();

        if (dtree2.getNumUsers() != 0) // if the copy is deep, clearing the first tree will not affect the second tree
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

// compares each node (used in testAssignmentOop)
bool Tester:: compareTrees(DNode* rootT1, DNode* rootT2)
{
    if (rootT1 == nullptr && rootT2 == nullptr)
        return true;
    else
    {
        // uses pre-order traversal
        if (compareData(rootT1, rootT2) == true) // if values are same proceed to another root. 
        {
            bool left = compareData(rootT1->_left, rootT2->_left);
            bool right = compareData(rootT1->_right, rootT2->_right);

            return left && right;
        }
        else
        {
            return false;
        }

    }

}

// used in compare trees function. compares value of each node
bool Tester:: compareData(DNode* rootT1, DNode* rootT2)
{
    if (rootT1 != nullptr && rootT2 != nullptr)
    {
        if (rootT1->getDiscriminator() == rootT2->getDiscriminator() && rootT1->getUsername() == rootT2->getUsername() &&
            rootT1->getSize() == rootT2->getSize() && rootT1->getNumVacant() == rootT2->getNumVacant() &&
            rootT1->isVacant() == rootT2->isVacant())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

// checks to see if the node follow bst ordering prop or not
bool Tester::validBstProp(DNode* node)
{
    bool validLeftProp = false;
    bool validRightProp = false;

    if (node->_left != nullptr)
    {
        if (node->_left->getDiscriminator() < node->getDiscriminator())
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
        if (node->_right->getDiscriminator() > node->getDiscriminator())
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

// checking if all the nodes in tree follow bst prop or not
bool Tester::holdsBstProp(DNode* node)
{
    if (node == nullptr)
    {
        return true;
    }
    else
    {
        if (validBstProp(node) == true) // if the node follows bst prop, move to another node
        {
            bool left = holdsBstProp(node->_left);
            bool right = holdsBstProp(node->_right);

            return left && right;
        }
        else
        {
            return false;
        }

    }
}

// called in main func
bool Tester::checkDtreeBstProp(DTree& dtree)
{
    bool status = false;


    for (int i = 0; i < 10; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);
    }

    status = holdsBstProp(dtree._root);

    return status;
}

//-------------------------------------------------------------------------------------------------------------------------- UTree ------------------------------------------------------------------------------//

bool Tester::testBasicUTreeInsert(UTree& utree)
{
    const int SIZE = 10;
    Account acct[SIZE];

    {
        Account acc1("d", 20, 1, "n", "o");
        acct[0] = acc1;
    }
    {
        Account acc1("a", 90, 1, "n", "o");
        acct[1] = acc1;
    }
    {
        Account acc1("g", 100, 1, "n", "o");
        acct[2] = acc1;
    }
    {
        Account acc1("i", 50, 1, "n", "o");
        acct[3] = acc1;
    }
    {
        Account acc1("h", 40, 1, "n", "o");
        acct[4] = acc1;
    }
    {
        Account acc1("h", 5, 1, "n", "o");
        acct[5] = acc1;
    }
    {
        Account acc1("g", 55, 1, "n", "o");
        acct[6] = acc1;

    }
    {
        Account acc1("p", 66, 1, "n", "o");
        acct[7] = acc1;

    }
    {
        Account acc1("k", 89, 1, "n", "o");
        acct[8] = acc1;

    }
    {
        Account acc1("k", 05, 1, "n", "o");
        acct[9] = acc1;
    }

    bool allInserted = true;

    for (int i = 0; i < SIZE; i++) {
        if (!utree.insert(acct[i])) {
            cout << "Insertion on node " << acct[i].getDiscriminator() << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}



bool Tester::testUTreeRemove(UTree& utree)
{
    {   Account acc1("j", 20, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("d", 90, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("d", 50, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("d", 1000, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("f", 50, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("a", 100, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("a", 1088, 1, "n", "o");
        utree.insert(acc1);
    }
    {
        Account acc1("e", 108, 1, "n", "o");
        utree.insert(acc1);
    }

    // removing nodes
    {
        DNode* removed1 = nullptr;
        DNode* removed2 = nullptr;
        DNode* removed3 = nullptr;
           
        utree.removeUser("d", 90, removed1);
        utree.removeUser("d", 50, removed2);
        utree.removeUser("d", 1000, removed3);
           
    }
      

    // if node d is not found retrive return null
    UNode* look1 = utree.retrieve("d");
   
    if (look1 == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// checks to see if the node follow bst prop or not
bool Tester::validBstProp(UNode * node)
{
    bool validLeftProp = false;
    bool validRightProp = false;

    if (node->_left != nullptr)
    {
        if (node->_left->getUsername() < node->getUsername())
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
        if (node->_right->getUsername() > node->getUsername())
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

// checks if all the nodes in tree follow bst prop or not
bool Tester::holdsBstProp(UNode* node)
{
    if (node == nullptr)
    {
        return true;
    }
    else
    {
        if (validBstProp(node) == true)
        {
            bool left = holdsBstProp(node->_left);
            bool right = holdsBstProp(node->_right);

            return left && right;
        }
        else
        {
            return false;
        }

    }
}

// called by main func
bool Tester::checkUtreeBstProp(UTree& utree)
{
    bool status1 = false;
    bool status2 = false;

    status1 = testBasicUTreeInsert(utree);

    status2 = holdsBstProp(utree._root);

    return status1 && status2;
}