// AVLSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.


#ifndef AVLSET_HPP
#define AVLSET_HPP
#include "Set.hpp"
 

template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
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
    void destroyAll(Node* L); 
    Node* copyAll(Node* L);
    Node* addNode(Node* L, const T& element);
    Node* rotation(Node* L);
    int height(Node* L); 
    int height_diff(Node* L);
    Node* LL_rotation(Node* L);
    Node* LR_rotation(Node* L);
    Node* RR_rotation(Node* L);
    Node* RL_rotation(Node* L);

};


template <typename T>
AVLSet<T>::AVLSet()
    :root(nullptr)
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    destroyAll(root);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    root=copyAll(s.root);
    node_size=s.node_size;
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
{
    std:: swap(root, s.root);
    std:: swap(node_size,s.node_size);

}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    destroyAll(root);
    root=copyAll(s.root);
    node_size=s.node_size; 
    return *this;
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
    std::swap(root,s.root);
    std::swap(node_size,s.node_size);
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    root=addNode(root,element); 
    node_size++; 
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
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
unsigned int AVLSet<T>::size() const
{
    return node_size;
}


template<typename T>
int AVLSet<T>:: height(Node* L)
{
    int node_height=0; 
    if(L==nullptr)
    {
        return 0;
    }
    else
    {
        int left_height=height(L->left);
        int right_height=height(L->right);
        if(left_height>right_height)
        {
            node_height=left_height+1; 
        }
        else
        {
            node_height=right_height+1;
        }
    }
    return node_height;
}


template<typename T>
int AVLSet<T>::height_diff(Node* L)
{
    return height(L->left)-height(L->right);
}


template< typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotation(Node* L)
{
    if(height_diff(L)==-2)
    {
        if(height_diff(L->right)>0)
        {
            L=RL_rotation(L);
        }
        else
        {
            L=RR_rotation(L);

        }
    }
    if(height_diff(L)==2)
    {
        if(height_diff(L->left)<0)
        {
            L=LR_rotation(L);
        }
        else
        {
            L=LL_rotation(L);
        }
    }
    return L; 
}


template<typename T>
typename AVLSet<T>::Node* AVLSet<T>::LL_rotation(Node* L)
{
    Node* temp=L->left; 
    L->left=temp->right; 
    temp->right=L; 
    return temp; 
}


template< typename T>
typename AVLSet<T>::Node* AVLSet<T>::RR_rotation(Node* L)
{
    Node* temp=L->right; 
    L->right=temp->left; 
    temp->left=L; 
    return temp; 
}


template< typename T>
typename AVLSet<T>::Node* AVLSet<T>::LR_rotation(Node* L)
{
    Node* temp=L->left; 
    L->left=RR_rotation(temp);
    temp=LL_rotation(L);
    return temp; 
}


template< typename T>
typename AVLSet<T>::Node* AVLSet<T>::RL_rotation(Node* L)
{
    Node* temp=L->right; 
    L->right=LL_rotation(temp);
    temp=RR_rotation(L);
    return temp; 
}


template< typename T>
typename AVLSet<T>::Node* AVLSet<T>::addNode(Node* L, const T& element) 
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
            L=rotation(L);

        }
        if(element>L->key)
        {
            L->right=addNode(L->right,element);
            L=rotation(L);
        }
        return L; 
    }
}


template<typename T>
typename AVLSet<T>::Node* AVLSet<T>::copyAll(Node* L)  
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
void AVLSet<T>::destroyAll(Node*L) 
{
    if(L!=nullptr)
    {
        destroyAll(L->left);
        destroyAll(L->right);
        delete L; 
    }
}


#endif // AVLSET_HPP

