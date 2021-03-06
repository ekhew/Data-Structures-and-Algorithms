/*
Title: Binary Search Tree (BST)
Author: Edwin Khew
Description: Binary search tree class implementation.
Date Created: 6/4/2021
*/

#include <queue> //for level order traversal

template<typename ItemType>
BST<ItemType>::BST():root_ptr_(nullptr) { }

template<typename ItemType>
BST<ItemType>::BST(const BST<ItemType> &tree)
{
    root_ptr_ = copyConstructorHelper(tree.root_ptr_); //set 'root_ptr_' of the new tree to the tree that was created in the helper function
}

template<typename ItemType>
BST<ItemType>::~BST()
{
    destroyTreeHelper(root_ptr_);
}

template<typename ItemType>
void BST<ItemType>::insert(const ItemType &new_item)
{
    root_ptr_ = insertHelper(root_ptr_, new_item); //update the 'root_ptr_' to the updated tree with the new node
}

template<typename ItemType>
void BST<ItemType>::remove(const ItemType &item)
{
    if(!isEmpty()) //can only remove if the tree is not empty
    {
        root_ptr_ = removeHelper(root_ptr_, item); //update the 'root_ptr_' to the updated tree with the node deleted
    }
}

template<typename ItemType>
void BST<ItemType>::clear()
{
    destroyTreeHelper(root_ptr_);
}

template<typename ItemType>
size_t BST<ItemType>::nodeCount() const
{
    return nodeCountHelper(root_ptr_);
}

template<typename ItemType>
size_t BST<ItemType>::getHeight() const
{
    return getHeightHelper(root_ptr_);
}

template<typename ItemType>
bool BST<ItemType>::isEmpty() const
{
    return root_ptr_ == nullptr;
}

template<typename ItemType>
ItemType BST<ItemType>::search(const ItemType &item) const
{
    Node<ItemType> *search_ptr = searchHelper(root_ptr_, item); //pointer to the node that is being searched for

    if(search_ptr == nullptr) //if the item cannot be found, throw an exception
    {
        throw(std::out_of_range("Position out of range!"));
    }
    else //return the item being pointed to by 'search_ptr'
    {
        return search_ptr->getItem();
    }
}

template<typename ItemType>
ItemType BST<ItemType>::findMin() const
{
    if(isEmpty()) //if the tree is empty, throw an exception
    {
        throw(std::out_of_range("Position out of range!"));
    }
    else //return the smallest item found by the helper function
    {
        return findMinHelper(root_ptr_)->getItem();
    }
}

template<typename ItemType>
ItemType BST<ItemType>::findMax() const
{
    if(isEmpty()) //if the tree is empty, throw an exception
    {
        throw(std::out_of_range("Position out of range!"));
    }
    else //return the greatest item found by the helper function
    {
        return findMaxHelper(root_ptr_)->getItem();
    }
}

template<typename ItemType>
void BST<ItemType>::preorderTraverse()
{
    if(!isEmpty()) //can only traverse if the tree is not empty
    {
        preorderHelper(root_ptr_); //traverse using the helper function
    }
    else
    {
        std::cout << "Tree is empty!";
    }
}

template<typename ItemType>
void BST<ItemType>::inorderTraverse()
{
    if(!isEmpty()) //can only traverse if the tree is not empty
    {
        inorderHelper(root_ptr_); //traverse using the helper function
    }
    else
    {
        std::cout << "Tree is empty!";
    }
}

template<typename ItemType>
void BST<ItemType>::postorderTraverse()
{
    if(!isEmpty()) //can only traverse if the tree is not empty
    {
        postorderHelper(root_ptr_); //traverse using the helper function
    }
    else
    {
        std::cout << "Tree is empty!";
    }
}

template<typename ItemType>
void BST<ItemType>::levelorderTraverse()
{
    if(!isEmpty()) //can only traverse if the tree is not empty
    {
        levelorderHelper(root_ptr_); //traverse using the helper function
    }
    else
    {
        std::cout << "Tree is empty!";
    }
}

template<typename ItemType>
ItemType BST<ItemType>::inorderSuccessor(const ItemType &item)
{
    Node<ItemType> *successor_ptr = inorderSuccessorHelper(root_ptr_, item); //pointer to the inorder successor of the specified node

    if(successor_ptr == nullptr) //if no successor was found, throw an exception
    {
        throw(std::out_of_range("Position out of range!"));
    }
    else //return the item being pointed to by 'successor_ptr'
    {
        return successor_ptr->getItem();
    }
}

template<typename ItemType>
void BST<ItemType>::printTree()
{
    if(!isEmpty())
    {
        printTreeHelper(root_ptr_, 0);
    }
}

/**************************************************************************************************
                                    Helper functions below.
**************************************************************************************************/

template<typename ItemType>
Node<ItemType> *BST<ItemType>::copyConstructorHelper(Node<ItemType> *root) const
{
    if(root == nullptr) //base case; return if a subtree is empty
    {
        return root; //returns 'nullptr'
    }
    else //copying a tree uses preorder traversal (copy the root node of the subtree, then its left and right subtrees)
    {
        Node<ItemType> *new_node_ptr = new Node<ItemType>(root->getItem()); //create a new node with a copy of the root item
        new_node_ptr->setLeft(copyConstructorHelper(root->getLeft())); //copy the left subtree
        new_node_ptr->setRight(copyConstructorHelper(root->getRight())); //copy the right subtree

        return new_node_ptr;
    }
}

template<typename ItemType>
void BST<ItemType>::destroyTreeHelper(Node<ItemType> *root)
{
    if(root == nullptr) //base case; return if a subtree is empty
    {
        return;
    }
    else
    {
        //destroying a tree uses postorder traversal (delete a node only after both its subtrees are destroyed)
        destroyTreeHelper(root->getLeft()); //traverse the left subtree
        destroyTreeHelper(root->getRight()); //traverse the right subtree
        delete root; //delete the root node of the subtree
        root = nullptr;

        root_ptr_ = nullptr; //set 'root_ptr_' to 'nullptr' once the entire tree has been destroyed
    }
}

template<typename ItemType>
Node<ItemType> *BST<ItemType>::insertHelper(Node<ItemType> *root, const ItemType &new_item)
{
    if(root == nullptr) //base case; once the correct position to insert is reached, create a new node with the new item
    {
        Node<ItemType> *new_node_ptr = new Node<ItemType>(new_item);
        root = new_node_ptr;
    }
    else if(new_item < root->getItem()) //if the new item is less than the root node, traverse to the left subtree
    {
        root->setLeft(insertHelper(root->getLeft(), new_item));
    }
    else //if the new item is greater than the root node, traverse to the right subtree
    {
        root->setRight(insertHelper(root->getRight(), new_item));
    }
    return root;
}

template<typename ItemType>
Node<ItemType> *BST<ItemType>::removeHelper(Node<ItemType> *root, const ItemType &item)
{
    //if the tree has only one node and the specified item matches
    if((nodeCount() == 1) && (root_ptr_->getItem() == item))
    {
        delete root_ptr_;
        root_ptr_ = nullptr;
    }

    //if the tree has more than one node
    if(root == nullptr) //base case; return if a subtree is empty
    {
        return root;
    }
    else
    {
        if(root->getItem() > item) //if root item is greater than the item to delete, search the left subtree
        {
            root->setLeft(removeHelper(root->getLeft(), item));
        }
        else if(root->getItem() < item) //if root item is less than the item to delete, search the right subtree
        {
            root->setRight(removeHelper(root->getRight(), item));
        }
        else //if the root item matches the item to delete, then the node to be deleted is found and can now be deleted
        {
            if(root->isLeaf()) //case 1: no children (is a leaf)
            {
                delete root;
                root = nullptr;
            }
            else if(root->getLeft() == nullptr) //case 2: one child (a right child)
            {
                Node<ItemType> *temp_ptr = root;
                root = root->getRight();
                delete temp_ptr;
                temp_ptr = nullptr;
            }
            else if(root->getRight() == nullptr) //case 2: one child (a left child)
            {
                Node<ItemType> *temp_ptr = root;
                root = root->getLeft();
                delete temp_ptr;
                temp_ptr = nullptr;
            }
            else //case 3: two children
            {
                Node<ItemType> *temp_ptr = inorderSuccessorHelper(root, root->getItem()); //find the inorder successor and create a pointer to point to it
                root->setItem(temp_ptr->getItem()); //replace the old item with a copy of the inorder successor item
                root->setRight(removeHelper(root->getRight(), temp_ptr->getItem())); //traverse the right subtree and remove the inorder successor
            }
        }
        return root;
    }
}

template<typename ItemType>
size_t BST<ItemType>::nodeCountHelper(Node<ItemType> *root) const
{
    int count = 1; //node count of the subtree; count starts at '1' to account for the root node of the subtree

    if(root == nullptr) //base case; return 0 if a subtree is empty
    {
        return 0;
    }
    else
    {
        count += nodeCountHelper(root->getLeft()); //count nodes in the left subtree
        count += nodeCountHelper(root->getRight()); //count nodes in the right subtree
        return count;
    }
}

template<typename ItemType>
size_t BST<ItemType>::getHeightHelper(Node<ItemType> *root) const
{
    if(root == nullptr) //base case; return if a subtree is empty
    {
        return 0;
    }
    else
    {
        //get the height of the left and right subtrees, then return the greater of the two; the '+ 1' accounts for the root of the subtree
        return 1 + std::max(getHeightHelper(root->getLeft()), getHeightHelper(root->getRight()));

    /*
        Below is basically what the std::max() function does.
    */

    /*
        size_t left_height = getHeightHelper(root->getLeft());
        size_t right_height = getHeightHelper(root->getRight());

        if(left_height > right_height)
        {
            return (left_height + 1);
        }
        else
        {
            return (right_height + 1);
        }
    */
    }
}

template<typename ItemType>
Node<ItemType> *BST<ItemType>::searchHelper(Node<ItemType> *root, const ItemType &item) const
{
    if((root == nullptr) || (root->getItem() == item)) //base case; if the item does not exist or if the item has been found
    {
        return root;
    }
    else
    {
        if((root->getItem() > item)) //if the root of the subtree is greater than the specified item, search the left subtree
        {
            return searchHelper(root->getLeft(), item);
        }
        else //if the root of the subtree is less than the specified item, search the right subtree
        {
            return searchHelper(root->getRight(), item);
        }
    }
}

template<typename ItemType>
Node<ItemType> *BST<ItemType>::findMinHelper(Node<ItemType> *root) const
{
    if(root->getLeft() == nullptr) //base case; once the leftmost item in the tree is found, return it
    {
        return root;
    }
    else //traverse to the left child
    {
        return findMinHelper(root->getLeft());
    }
}

template<typename ItemType>
Node<ItemType> *BST<ItemType>::findMaxHelper(Node<ItemType> *root) const
{
    if(root->getRight() == nullptr) //base case; once the rightmost item in the tree is found, return it
    {
        return root;
    }
    else //traverse to the right child
    {
        return findMaxHelper(root->getRight());
    }
}

template<typename ItemType>
void BST<ItemType>::preorderHelper(Node<ItemType> *root)
{
    if(root != nullptr) //base case; return if a subtree of a root is empty
    {
        std::cout << root->getItem() << " "; //visit the node
        preorderHelper(root->getLeft()); //traverse the left subtree
        preorderHelper(root->getRight()); //traverse the right subtree
    }
}

template<typename ItemType>
void BST<ItemType>::inorderHelper(Node<ItemType> *root)
{
    if(root != nullptr) //base case; return when a subtree of a root is empty
    {
        inorderHelper(root->getLeft()); //traverse the left subtree
        std::cout << root->getItem() << " "; //visit the node
        inorderHelper(root->getRight()); //traverse the right subtree
    }
}

template<typename ItemType>
void BST<ItemType>::postorderHelper(Node<ItemType> *root)
{
    if(root != nullptr) //base case; return when a subtree of a root is empty
    {
        postorderHelper(root->getLeft()); //traverse the left subtree
        postorderHelper(root->getRight()); //traverse the right subtree
        std::cout << root->getItem() << " "; //visit the node
    }
}

template<typename ItemType>
void BST<ItemType>::levelorderHelper(Node<ItemType> *root)
{
    if(root != nullptr) //base case; can only traverse if the tree is not empty
    {
        std::queue<Node<ItemType>*> Q; //create a new queue of item type 'Node<ItemType>*'
        Q.push(root);//push the root node into the queue

        while(!Q.empty())
        {
            Node<ItemType> *current_ptr = Q.front(); //create a pointer to store the address of the node at the front of the queue

            std::cout << current_ptr->getItem() << " "; //visit the node

            //push the parent node's left child into the queue, if a left child is present
            if(current_ptr->getLeft() != nullptr)
            {
                Q.push(current_ptr->getLeft());
            }

            //push the parent node's right child into the queue, if a right child is present
            if(current_ptr->getRight() != nullptr)
            {
                Q.push(current_ptr->getRight());
            }

            Q.pop(); //pop the parent node from the front of the queue
        }
    }
}

template<typename ItemType>
Node<ItemType> *BST<ItemType>::inorderSuccessorHelper(Node<ItemType> *root, const ItemType &item) const
{
    Node<ItemType> *node_ptr = searchHelper(root, item); //pointer to the node to find successor of

    if(node_ptr == nullptr) //if the item does not exist in the tree
    {
        return nullptr;
    }
    //case 1: node has a right subtree; find the leftmost node (the minimum) in the right subtree
    else if(node_ptr->getRight() != nullptr)
    {
        Node<ItemType> *leftmost_ptr = node_ptr->getRight(); //pointer that will traverse the right subtree and store the address of the lefmost node

        while(leftmost_ptr->getLeft() != nullptr) //while it is possible to traverse left, keep traversing left
        {
            leftmost_ptr = leftmost_ptr->getLeft();
        }
        return leftmost_ptr;
    }
    //case 2: node does not have a right subtree; find the deepest ancestor in which the node falls in its left subtree
    else if(node_ptr->getRight() == nullptr)
    {
        Node<ItemType> *successor_ptr = nullptr; //pointer to the successor; will return 'nullptr' if no successor is found
        Node<ItemType> *ancestor_ptr = root; //pointer to an ancestor; starts from the root of the tree

        while(ancestor_ptr != node_ptr) //traverse the tree until the node is reached
        {
            if(node_ptr->getItem() < ancestor_ptr->getItem()) //if the node's item is less than the ancestor's item, then the node is in the ancestor's left subtree
            {
                successor_ptr = ancestor_ptr; //keep track of the current deepest ancestor in which the node falls in its left subtree
                ancestor_ptr = ancestor_ptr->getLeft();
            }
            else //if the node's item is greater than the ancestor's item, then the node is in the ancestor's right subtree
            {
                ancestor_ptr = ancestor_ptr->getRight();
            }
        }
        return successor_ptr;
    }

    return nullptr;
}

template<typename ItemType>
void BST<ItemType>::printTreeHelper(Node<ItemType> *root, int space)
{
    if(root == nullptr) //base case; return when a subtree of a root is empty
    {
        return;
    }
    else
    {
        space += 10; //increase distance between levels

        printTreeHelper(root->getRight(), space); //print the right subtree

        std::cout << std::endl;
        for(int i = 10; i < space; i++)
        {
            std::cout << " ";
        }
        std::cout << root->getItem() << std::endl;

        printTreeHelper(root->getLeft(), space); //print the left subtree
    }
}
