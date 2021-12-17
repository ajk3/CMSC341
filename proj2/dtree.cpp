/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */

#include "dtree.h"

 /**
  * Destructor, deletes all dynamic memory.
  */
DTree::~DTree()
{
    clear();
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */

DTree& DTree::operator=(const DTree& rhs)
{
    if (this != &rhs)
    {
        this->clear();
      
        DNode*& tempLhs = this->_root;
        DNode* tempRhs = rhs._root;

        copyNodes(tempLhs, tempRhs);
    }
    return *this;
}


/*
 * Dynamically allocates a new DNode in the tree.
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */

bool DTree::insert(Account newAcct)
{
    bool inserted = false;

    if (_root == nullptr)
    {
        _root = new DNode(newAcct);

        sizeUpTheTree(_root);
        vacantUpTheTree(_root);
        imbalanceUpTheTree(_root);

        inserted = true;
    }
    else
    {
        if (retrieve(newAcct.getDiscriminator()) == nullptr) // if descriminator doesn't exist already
        {
            inserted = recursiveInsert(_root, newAcct);
        }
    }

    return inserted;
}

/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::remove(int disc, DNode*& removed)
{
    bool status = false;
    DNode* keyNode = retrieve(disc);

    if (keyNode != nullptr)
    {
        keyNode->_vacant = true;
        updateNumVacant(keyNode);

        removed = keyNode;

        vacantUpTheTree(keyNode);

        status = true;
    }

    return status;
}

/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::retrieve(int disc)
{
    DNode* temp = _root;

    return search(temp, disc);
}

/**
 * Helper for the destructor to clear dynamic memory.
 */

void DTree::clear()
{
    DNode* temp = this->_root;

    deleteNodes(temp);
    this->_root = nullptr;   
}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const
{
    printInOrder(_root); // calling recursive helper function
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if (node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const
{
    // size - vacant nodes = total non vacant node
   
    return ((_root->getSize()) - _root->getNumVacant());
}

/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 */
void DTree::updateSize(DNode* node)
{
    if (node != nullptr)
    {
        if (node->_left == nullptr && node->_right == nullptr) // leaf node
        {
            node->_size = 1;
        }
        else if (node->_left != nullptr && node->_right == nullptr) // internal node with left child
        {
            node->_size = (node->_left->getSize()) + 1;
        }
        else if (node->_right != nullptr && node->_left == nullptr) // internal node with right child
        {
            node->_size = (node->_right->getSize()) + 1;
        }
        else // internal node with two children
        {
            node->_size = (node->_right->getSize()) + (node->_left->getSize()) + 1;
        }
    }
}

/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node)
{
    if (node != nullptr)
    {
        if (node->_left == nullptr && node->_right == nullptr) // leaf node
        {
            if (node->isVacant() == true)
            {
                node->_numVacant++;
            }
            else
            {
                node->_numVacant = 0;
            }
        }
        else if (node->_left != nullptr && node->_right == nullptr) // internal node with left child
        {
            if (node->isVacant() == true)
            {
                node->_numVacant = node->_left->getNumVacant() + 1;
            }
            else
            {
                node->_numVacant = node->_left->getNumVacant();
            }
        }
        else if (node->_right != nullptr && node->_left == nullptr) // internal node with right child
        {
            if (node->isVacant() == true)
            {
                node->_numVacant = node->_right->getNumVacant() + 1;
            }
            else
            {
                node->_numVacant = node->_right->getNumVacant();
            }
        }
        else if (node->_right != nullptr && node->_left != nullptr) // internal node with two children
        {
            if (node->isVacant() == true)
            {
                node->_numVacant = (node->_right->getNumVacant()) + (node->_left->getNumVacant()) + 1;
            }
            else
            {
                node->_numVacant = (node->_right->getNumVacant()) + (node->_left->getNumVacant());
            }
        }
    }
}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
bool DTree::checkImbalance(DNode* node)
{
    bool status = false;

    int leftSize = 0;
    int rightSize = 0;
    double fiftyPerOfRight = 0;
    double fiftyPerOfLeft = 0;

    if (node != nullptr)
    {
        if (node->_right != nullptr)
        {
            rightSize = node->_right->getSize();
            fiftyPerOfRight = ((50.0 / 100) * rightSize);
        }
        if (node->_left != nullptr)
        {
            leftSize = node->_left->getSize();
            fiftyPerOfLeft = (50.0 / 100) * leftSize;
        }
    }


    if (node == nullptr)
    {
        return status;
    }
    else
    {
        if ((node->_left == nullptr && node->_right != nullptr))
        {
            if (rightSize >= 4)
            {
                status = true;
            }
        }
        else if ((node->_right == nullptr && node->_left != nullptr))
        {
            if (leftSize >= 4)
            {
                status = true;
            }
        }
        else if ((node->_right != nullptr && node->_left != nullptr))
        { 
            if (((rightSize >= (leftSize + fiftyPerOfLeft)) || (leftSize >= (rightSize + fiftyPerOfRight))) &&
                (((rightSize) >= 4) || (leftSize >= 4)))
            {
                status = true;
            }
        }
    }

    return status;
}


void DTree::rebalance(DNode*& node)
{
    int size = node->getSize();

    int nonVacSize = node->getSize() - node->getNumVacant();

    DNode** nodeArr = new DNode * [size]; // converts tree to an array, includes vacant nodes too
    DNode** nonVac = new DNode * [nonVacSize]; // holds just the vacant nodes

    int idx = 0;

    int counter = 0;

    treeToArray(node, nodeArr, idx);

    for (int i = 0; i < size; i++)
    {
        if (nodeArr[i]->isVacant() == false)
        {
            nonVac[counter] = nodeArr[i];
            counter++;
        }
        else
        {
            delete nodeArr[i]; // deleting the vacant node
        }
    }

    arrayToTree(node, nonVac, 0, nonVacSize - 1);


    delete[] nonVac;
    delete[] nodeArr;

    nodeArr = nullptr;
    nonVac = nullptr;

} 

 /**
  * Overloaded << operator for an Account to print out the account details
  * @param sout ostream object
  * @param acct Account objec to print
  * @return ostream object containing stream of account details
  */
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() <<
        "\n\tDiscriminator: " << acct.getDiscriminator() <<
        "\n\tNitro: " << acct.hasNitro() <<
        "\n\tBadge: " << acct.getBadge() <<
        "\n\tStatus: " << acct.getStatus();
    return sout;
}


//------------------------------------------   Helper functions   --------------------------------------------------//

// helper function to recursively insert a node
bool DTree::recursiveInsert(DNode* root, Account newAcct)
{
    bool status = false;
    DNode* tempPtr = root;

    bool holdBstProp = false;

    if (status == true)
    {
        return status;
    }
    else
    {
        if (tempPtr->isVacant() == true)
        {
            holdBstProp = foundVacant(tempPtr, newAcct);

        }

        if (holdBstProp == false)
        {
            if (newAcct.getDiscriminator() < tempPtr->getDiscriminator()) // vist left sub tree
            {
                if (tempPtr->_left == nullptr)
                {
                    tempPtr->_left = new DNode(newAcct);

                    sizeUpTheTree(tempPtr->_left);
                    vacantUpTheTree(tempPtr->_left);
                   imbalanceUpTheTree(tempPtr->_left);

                   return true;
                }
                else
                {
                   status = recursiveInsert(tempPtr->_left, newAcct);
                }
            }

            else if (newAcct.getDiscriminator() > tempPtr->getDiscriminator()) // vist the right sub tree
            {
                if (tempPtr->_right == nullptr)
                {
                    tempPtr->_right = new DNode(newAcct);
                   
                    sizeUpTheTree(tempPtr->_right);
                    vacantUpTheTree(tempPtr->_right);
                   imbalanceUpTheTree(tempPtr->_right);

                   return true;
                }
                else
                {
                  status =  recursiveInsert(tempPtr->_right, newAcct);
                }
            }
        }

        return status;
    }
}

// recursive search
DNode* DTree::search(DNode* node, int disc)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        // if the key is found and the node is not vacant
        if (node->getDiscriminator() == disc)
        {
            if (node->isVacant() == true)
            {
                return nullptr;
            }
            else
            {
                return node;
            }
        }

        // key < root's key, traverse left sub tree
        else if (disc < node->getDiscriminator())
        {
            node = search(node->_left, disc);
        }

        // key > root's key, traverse right sub tree
        else if (disc > node->getDiscriminator())
        {
            node = search(node->_right, disc);

        }

        return node;
    }

}

// finds the parent of the provided key
DNode* DTree::findParent(DNode* root, DNode* key)
{
    DNode* temp = root;

    if (key == nullptr || root == nullptr || key == _root)
    {
        return nullptr;
    }
    else
    {
        
        if (key == _root)
        {
            return nullptr;
        }

        if (key->getDiscriminator() < temp->getDiscriminator())
        {
            if (key->getDiscriminator() == (temp->_left)->getDiscriminator())
            {
               
                return temp;
            }
            else
            {
               
                temp = findParent(temp->_left, key);
            }

        }

        else if (key->getDiscriminator() > temp->getDiscriminator())
        {
           

            if (key->getDiscriminator() == (temp->_right)->getDiscriminator())
            {
                
                return temp;
            }
            else
            {

                temp = findParent(temp->_right, key);
            }
        }

        return temp;
    }
}


// uses postorder traversal to delete the nodes 
void DTree::deleteNodes(DNode* temp)
{
    if (temp == nullptr)
    {
        return;
    }
    else
    {
        // using postorder(deleting childrns before deleting the parent)
        deleteNodes(temp->_left); // visit left subtree
        deleteNodes(temp->_right); // visit right subtree
        delete temp; // delete the node
    }

}

// helper function to update size from the node to its parent 
void DTree::sizeUpTheTree(DNode* temp)
{
    DNode* parent = findParent(_root, temp);

    while (parent != nullptr)
    {
        updateSize(parent);
        parent = findParent(_root, parent);
    }

    return;
}

// helper function to update vacant node from the node to its parent 
void DTree::vacantUpTheTree(DNode* temp)
{
    DNode* parent = findParent(_root, temp);

    while (parent != nullptr)
    {
        updateNumVacant(parent);
        parent = findParent(_root, parent);
    }

    return;
}

// helper function to check for the imbalance from the node to the root 
void DTree::imbalanceUpTheTree(DNode*& temp)
{
    DNode* parent = findParent(_root, temp);

    bool imbalance = false;

    while (parent != nullptr)
    {
        imbalance = checkImbalance(parent);
        
        if (imbalance == true)
        {
            if (_root == parent)
            {
                rebalance(_root);
                parent = nullptr;
            }
            else if (parent == _root->_right)
            {
                DNode* grandParent = findParent(_root, parent);

                rebalance(_root->_right);
                parent = grandParent;

            }
            else if (parent == _root->_left)
            {
                DNode* grandParent = findParent(_root, parent);

                rebalance(_root->_left);
                parent = grandParent;
            }
        }
        else
        {
            parent = findParent(_root, parent);
        }
    }

} 


// prints account
void DTree::printInOrder(DNode* temp) const
{
    if (temp == nullptr)
    {
        return;
    }
    else
    {
        printInOrder(temp->_left); // left sub tree

        if (temp->isVacant() == false)
        {
            cout << temp->getAccount() << endl;
        }

        printInOrder(temp->_right); // right sub tree
    }
}

// copies nodes from rhs over to lhs
void DTree::copyNodes(DNode*& lhsNode, DNode* const rhsNode)
{

    if (rhsNode == nullptr)
    {
        return;
    }
    else
    {
        // uses preorder traversal
        lhsNode = new DNode(rhsNode->getAccount());
        lhsNode->_size = rhsNode->_size;
        lhsNode->_numVacant = rhsNode->_numVacant;
        lhsNode->_vacant = rhsNode->_vacant;
       
        copyNodes(lhsNode->_left, rhsNode->_left); // visit left subtree

        copyNodes(lhsNode->_right, rhsNode->_right); // visit right subtree
    }
}


// used during insertion if we encounter the vacant node
bool DTree::foundVacant(DNode* tempPtr, Account newAcct)
{
    bool validLeftProp = false;
    bool validRightProp = false;
    bool status = false;

    if (tempPtr->isVacant() == true)
    {
        if (tempPtr->_left != nullptr)
        {
            if (tempPtr->_left->getDiscriminator() < newAcct.getDiscriminator())
            {
                validLeftProp = true;
            }
        }
        else
        {
            validLeftProp = true;
        }

        if (tempPtr->_right != nullptr)
        {
            if (tempPtr->_right->getDiscriminator() > newAcct.getDiscriminator())
            {
                validRightProp = true;
            }
        }
        else
        {
            validRightProp = true;
        }

        if (validLeftProp && validRightProp)
        {
            tempPtr->_account = newAcct;

            tempPtr->_vacant = false;

            updateNumVacant(tempPtr);

            vacantUpTheTree(tempPtr); // updating the number of vacant nodes up the tree

            status = true;
        }
    }

    return status;
}


// converts tree to an array using in-order traversal
int DTree::treeToArray(DNode*& node, DNode* arr[], int idx)
{
    if (node == nullptr)
    {
        return idx;
    }
    else // uses in-order traversal
    {
        idx = treeToArray(node->_left, arr, idx);

        *(arr + idx) = node;
        idx++;

        idx = treeToArray(node->_right, arr, idx);

        return idx;
    }
}

// converts array to tree
void DTree::arrayToTree(DNode*& node, DNode* arr[], int startIdx, int endIdx)
{
    if (startIdx > endIdx)
    {
        return;
    }

    else
    {
        int middle = (startIdx + endIdx) / 2;

        node = arr[middle];

        node->_right = nullptr;
        node->_left = nullptr;

        arrayToTree((node->_left), arr, startIdx, middle - 1);

        arrayToTree((node->_right), arr, middle + 1, endIdx);
    }

    updateNumVacant(node);
    updateSize(node);
}









