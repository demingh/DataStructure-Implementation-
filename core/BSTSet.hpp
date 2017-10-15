// BSTSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.
#ifndef BSTSET_HPP
#define BSTSET_HPP
#include "Set.hpp"


template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Initializes a new BSTSet whose contents are moved from an
    // expiring one.
    BSTSet(BSTSet&& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);

    // Assigns an expiring BSTSet into another.
    BSTSet& operator=(BSTSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
        T key; 
        Node* left=nullptr; 
        Node* right=nullptr; 
    };
    Node* root=nullptr; 
    int node_size=0; 

    Node* copyAll(Node* L);
    void destroyAll(Node* L); 
    Node* addNode(Node* L, const T& element);
};


template <typename T>
BSTSet<T>::BSTSet()   
	:root(nullptr)
{ 
}


template <typename T>
BSTSet<T>::~BSTSet()  
{
    destroyAll(root);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    root=copyAll(s.root);
    node_size=s.node_size; 
}


template <typename T>
BSTSet<T>::BSTSet(BSTSet&& s)
{
    std::swap(root,s.root);
    std::swap(node_size,s.node_size);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    destroyAll(root); 
    root=copyAll(s.root);
    node_size=s.node_size; 
    return *this;
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(BSTSet&& s)
{
    std::swap(root, s.root);
    std::swap(node_size,s.node_size);
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const  
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element) 
{  
    root=addNode(root,element);
    node_size++;
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const 
{
    Node* curr=root; 
    while(curr!=nullptr)
    {
        if(curr->key ==element)
        {
            return true; 
        }
        else
            if(curr->key>element)
            {
                curr=curr->left; 
            }
            else
                curr=curr->right; 
    }
    return false;
}


template <typename T>
unsigned int BSTSet<T>::size() const 
{
    return node_size;
}


template<typename T>
typename BSTSet<T>::Node* BSTSet<T>::addNode(Node* L, const T& element)
{
    if(L==nullptr)
    {
        L= new Node();
        L->key=element; 
        return L;  
    }
    else
    {   
        if(element<L->key)
        {
            L->left=addNode(L->left,element);
        }
        if(element>L->key)
        {
            L->right=addNode(L->right,element);
        }
        return L; 
    }
}


template<typename T>
typename BSTSet<T>::Node* BSTSet<T>::copyAll(Node* L)   
{ 
    Node* curr=new Node();
    if(L==nullptr)
    {
        return nullptr; 
    }
    else
    {
        curr->key=L->key; 
        curr->left=copyAll(L->left); 
        curr->right=copyAll(L->right); 
    } 
    return curr; 
}


template<typename T>
void BSTSet<T>::destroyAll(Node*L)  
{
    if(L!=nullptr)
    {
        destroyAll(L->left);
        destroyAll(L->right);
        delete L; 
    }
}


#endif // BSTSET_HPP

