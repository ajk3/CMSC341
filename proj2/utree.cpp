/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"

 /**
  * Destructor, deletes all dynamic memory.
  */
UTree::~UTree()
{
    clear();
  
}

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */
void UTree::loadData(string infile, bool append) {
    std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];

    /* Check to make sure the file was opened */
    if (!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
    if (!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
    while (std::getline(instream, line)) {
        std::stringstream buffer(line);

        /* Quick check to make sure each line is formatted correctly */
        int delimCount = 0;
        for (unsigned int c = 0; c < buffer.str().length(); c++) if (buffer.str()[c] == delim) delimCount++;
        if (delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes -
         * Each line always has 5 sections of data */
        for (int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
}

/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree.
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 */
bool UTree::insert(Account newAcct)
{
    bool inserted = false;

    UNode* userNode = (retrieve(newAcct.getUsername()));

    if (userNode == nullptr) // usernode not found, create a new node
    {
        if (_root == nullptr)
        {
            _root = new UNode();
            _root->_dtree->insert(newAcct);

            heightUpTheTree(_root);
            imbalanceUpTheTree(_root);

            inserted = true;
        }
        else
        {

            inserted = recursiveInsert(_root, newAcct);
        }
    }
    else // if username exist already, check to see if the account is already present
    {
        DNode* lookForAccount = retrieveUser(newAcct.getUsername(), newAcct.getDiscriminator());

        if (lookForAccount == nullptr) // if the account is not already present, insert it else return
        {
            userNode->_dtree->insert(newAcct);

            inserted = true;
        }
        else
        {
            inserted = false;
        }

    }
    return inserted;
}

/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed)
{
    bool nodeRemoved = false;
    UNode* user = retrieve(username);

    if (user == nullptr) // username doesn't exist
    {
        nodeRemoved = false;
    }
    else
    {
        if (retrieveUser(username, disc) == nullptr) // account doesn't exist
        {
            nodeRemoved = false;
        }
        else
        {
            user->_dtree->remove(disc, removed);

            if (user->_dtree->getNumUsers() == 0) // if all nodes in the dTree are vacant, delete the node
            {
                removeAvlNode(user);
            }
            nodeRemoved = true;
        }
    }
    return nodeRemoved;
}



/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username)
{
    UNode* temp = _root;

    return search(temp, username);
}

/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc)
{
    UNode* temp = retrieve(username);

    if (temp == nullptr)
    {
        return nullptr;
    }
    else
    {
        DTree* tempTree = (temp->_dtree);

        return tempTree->retrieve(disc);
    }
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username)
{
    UNode* temp = retrieve(username);

    if (temp == nullptr)
    {
        return 0;
    }
    else
    {
        DTree* tempTree = (temp->_dtree);

        return tempTree->getNumUsers();
    }
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear()
{
    deleteNodes(_root);
    _root = nullptr;
}

/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const
{
    printInOrder(_root);
}

/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if (node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node)
{
    if (node != nullptr)
    {
        if (node->_left == nullptr && node->_right == nullptr) // leaf node
        {
            node->_height = 0;
        }
        else if (node->_left != nullptr && node->_right == nullptr) // internal node with left child
        {
            node->_height = node->_left->getHeight() + 1;
        }
        else if (node->_right != nullptr && node->_left == nullptr) // internal node with right child
        {
            node->_height = node->_right->getHeight() + 1;
        }
        else // internal node with two children
        {
            int maxHeight = findMaxHeight(node);

            node->_height = maxHeight + 1;
        }
    }
}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node)
{

    int leftHeight = -1;
    int rightHeight = -1;

    int imbalance = 0;

    if (node == nullptr)
    {
        imbalance = 1;
    }
    else
    {

        if (node->_left != nullptr)
        {
            leftHeight = node->_left->getHeight();
        }

        if (node->_right != nullptr)
        {
            rightHeight = node->_right->getHeight();
        }

        imbalance = (leftHeight - rightHeight);
    }

    return imbalance;
}

//----------------
/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */
void UTree::rebalance(UNode*& node)
{
    int balancingFactor = checkImbalance(node);

    if (balancingFactor == -2)
    {
        if (checkImbalance(node->_right) == 1)
        {
            rightRotation(node->_right);
        }

        leftRotation(node);
    }
    else if (balancingFactor == 2)
    {
        if (checkImbalance(node->_left) == -1)
        {
            leftRotation(node->_left);
        }

        rightRotation(node);
    }

}


//-------------------------------------------------------- Helper function --------------------------------------------------------------//

// helper function to recursively insert a node
bool UTree::recursiveInsert(UNode* root, Account newAcct)
{
    bool status = false;
    UNode* tempPtr = root;

    if (status == true)
    {
        return status;
    }
    else
    {
        if (newAcct.getUsername() < tempPtr->getUsername()) // vist left sub tree
        {
            if (tempPtr->_left == nullptr)
            {
                tempPtr->_left = new UNode();
                tempPtr->_left->_dtree->insert(newAcct);

                heightUpTheTree(tempPtr->_left);
                imbalanceUpTheTree(tempPtr->_left);

                status = true;
            }
            else
            {
               status =  recursiveInsert(tempPtr->_left, newAcct);
            }
        }
        else if (newAcct.getUsername() > tempPtr->getUsername()) // vist the right sub tree
        {
            if (tempPtr->_right == nullptr)
            {
                tempPtr->_right = new UNode();
                tempPtr->_right->_dtree->insert(newAcct);

                heightUpTheTree(tempPtr->_right);
                imbalanceUpTheTree(tempPtr->_right);

                status = true;
            }
            else
            {
                status = recursiveInsert(tempPtr->_right, newAcct);
            }
        }

        return status;
    }
}

void UTree::deleteNodes(UNode* temp)
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
        {
            temp->_dtree->clear();
            delete temp;
        }
    }

}

// recursive search
UNode* UTree::search(UNode* node, string username)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        // if the key is found and the node is not vacant
        if (node->_dtree->getUsername() == username)
        {
            return node;
        }

        // key < root's key, traverse left sub tree
        else if (username < node->_dtree->getUsername())
        {
            node = search(node->_left, username);
        }

        // key > root's key, traverse right sub tree
        else if (username > node->_dtree->getUsername())
        {
            node = search(node->_right, username);
        }

        return node;
    }

}

// prints account
void UTree::printInOrder(UNode* temp) const
{
    if (temp == nullptr)
    {
        return;
    }
    else
    {
        printInOrder(temp->_left); // left sub tree

        temp->_dtree->printAccounts();

        printInOrder(temp->_right); // right sub tree
    }
}

// looks for parent
UNode* UTree::findParent(UNode* root, UNode* key)
{
    UNode* temp = root;

    if (key == nullptr || root == nullptr || key == root)
    {
        return nullptr;
    }
    else
    {
        if (key->getUsername() < temp->getUsername())
        {
            if (key->getUsername() == (temp->_left)->getUsername())
            {
                return temp;
            }
            else
            {
                temp = findParent(temp->_left, key);
            }
        }

        else if (key->getUsername() > temp->getUsername())
        {
            if (key->getUsername() == (temp->_right)->getUsername())
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

// updates height from the node upto the root
void UTree::heightUpTheTree(UNode* temp)
{
    UNode* parent = findParent(_root, temp);

    while (parent != nullptr)
    {
        updateHeight(parent);
        parent = findParent(_root, parent);
    }
    return;
}

// checks for imbalance from the node upto the root
void UTree::imbalanceUpTheTree(UNode* node)
{
    UNode* parent = findParent(_root, node);
    int imbalance = 0;

    while (parent != nullptr)
    {
        imbalance = abs(checkImbalance(parent));

        if (imbalance > 1) // there's an imbalance
        {
            if (parent == _root)
            {
                rebalance(_root);
                parent = nullptr;
            }
            else
            {
                UNode* grandParent = findParent(_root, parent);
                rebalance(parent);
                parent = grandParent;
            }
        }
        else
        {
            parent = findParent(_root, parent);
        }
    }
    return;
}

// finds max height (used my update height func)
int UTree::findMaxHeight(UNode* node)
{
    int maxHeight = 0;

    if (node->_right->getHeight() > node->_left->getHeight())
    {
        maxHeight = node->_right->getHeight();
    }
    else if (node->_left->getHeight() > node->_right->getHeight())
    {
        maxHeight = node->_left->getHeight();
    }
    else // if both height are equal
    {
        maxHeight = node->_left->getHeight();
    }

    return maxHeight;
}

void UTree::removeAvlNode(UNode* node)
{
    if (node != nullptr)
    {
        UNode* tempNode = node;

        UNode* parent = findParent(_root, tempNode); // finds parent

        if (tempNode->_left == nullptr && tempNode->_right == nullptr) // leaf node
        {
            if (parent == nullptr)
            {
                _root = nullptr;
            }
            else if (tempNode == parent->_left)
            {
                parent->_left = nullptr;
            }
            else
            {
                parent->_right = nullptr;
            }

            delete tempNode;
            tempNode = nullptr;
        }
        else if (tempNode->_left != nullptr && tempNode->_right == nullptr) // internal node with only left child
        {

            if (parent == nullptr)
            {
                _root = tempNode->_left;
            }

            else if (tempNode == parent->_right)
            {
                parent->_right = tempNode->_left;

            }
            else
            {
                parent->_left = tempNode->_left;
            }

            delete tempNode;
            tempNode = nullptr;
        }
        else if (tempNode->_right != nullptr && tempNode->_left == nullptr) // internal node with only right child
        {

            if (parent == nullptr)
            {
                _root = tempNode->_right;
            }

            else if (tempNode == parent->_right)
            {
                parent->_right = tempNode->_right;

            }
            else
            {
                parent->_left = tempNode->_right;
            }

            delete tempNode;
            tempNode = nullptr;
        }
        else // internal node with two child
        {
            UNode* predNode = tempNode->_left;

            while (predNode->_right != nullptr)
            {
                predNode = predNode->_right;
            }

            DTree tempTree;
            tempTree = *(predNode->_dtree); // create a copy of predcessor's data


            removeAvlNode(predNode); // delete the pred

            *(tempNode->_dtree) = tempTree; // assign data to node

            return; // since this case is recursive and I already updated the height and checked for reblancing, I don't want to do it again
        }

        updateHeight(parent);
        heightUpTheTree(parent);

        if (abs(checkImbalance(parent)) > 1)
        {
            rebalance(parent);
        }

        imbalanceUpTheTree(parent);

    }
}

void UTree::leftRotation(UNode*& node)
{
    if (node != nullptr)
    {
        UNode* tempNode = node;

        UNode* rightLeftChild = node->_right->_left;

        UNode* parent = findParent(_root, node);

        if (parent == nullptr) // i.e. root node
        {
            _root = tempNode->_right;
            _root->_left = tempNode;
            tempNode->_right = rightLeftChild;
        }
        else if (tempNode == parent->_right)
        {
            parent->_right = tempNode->_right;

            (parent->_right)->_left = tempNode;

            tempNode->_right = rightLeftChild;
        }
        else if (tempNode == parent->_left)
        {
            UNode* tempsRightChild = tempNode->_right;

            parent->_left = tempsRightChild;

            tempsRightChild->_left = tempNode;

            tempNode->_right = nullptr;
            tempNode->_left = nullptr;
        }

        updateHeight(tempNode);
        heightUpTheTree(tempNode);
    }
}

void UTree::rightRotation(UNode*& node)
{
    if (node != nullptr)
    {
        UNode* tempNode = node;

        UNode* leftRightChild = node->_left->_right;

        UNode* parent = findParent(_root, node);

        if (parent == nullptr) // i.e. root node
        {
            _root = tempNode->_left;
            _root->_right = tempNode;
            tempNode->_left = leftRightChild;
        }
        else if (tempNode == parent->_left)
        {
            parent->_left = tempNode->_left;
            (parent->_left)->_right = tempNode;
            tempNode->_left = leftRightChild;
        }
        else if (tempNode == parent->_right)
        {
            UNode* tempslefttChild = tempNode->_left;

            parent->_right = tempslefttChild;

            tempslefttChild->_right = tempNode;

            tempNode->_right = nullptr;
            tempNode->_left = nullptr;
        }

        updateHeight(tempNode);
        heightUpTheTree(tempNode);
    }
}


