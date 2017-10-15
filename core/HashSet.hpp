// HashSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"

template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    HashFunction hashFunction;
    struct Node
    {
        T key; 
        Node* next=nullptr; 
    };
    Node** hash; 
    int hash_size; 
    int hash_capacity; 
    void deleteall();
    void deletenode(Node* L);
    void resize(Node** hash);
    void insert(Node** Hash, const T& element);
    void copyall(const HashSet& s);
    void createnewhash(const HashSet& s);
};


template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}, hash_size{0}, hash_capacity{DEFAULT_CAPACITY}
{
    hash=new Node*[hash_capacity];
    for(int i=0; i<hash_capacity;i++)
    {
        hash[i]=nullptr; 
    }
}


template <typename T>
HashSet<T>::~HashSet()
{
    deleteall(); 
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{nullptr}
{
    copyall(s);
    hash_size=s.hash_size;
}


template <typename T>
HashSet<T>::HashSet(HashSet&& s)
    : hashFunction{nullptr}
{  
    createnewhash(s);
    std::swap(hashFunction,s.hashFunction);
    std::swap(hash,s.hash);
    std::swap(hash_size,s.hash_size);
    std::swap(hash_capacity,s.hash_capacity);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    deleteall();
    copyall(s);
    hash_size=s.hash_size;
    return *this;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(HashSet&& s)
{
    createnewhash(s);
    std::swap(hashFunction,s.hashFunction);
    std::swap(hash,s.hash);
    std::swap(hash_size,s.hash_size);
    std::swap(hash_capacity,s.hash_capacity);
    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    if(!contains(element))
    {
        insert(hash, element);        
        if(static_cast<double>(hash_size)/static_cast<double>(hash_capacity)>0.8)
        {
            resize(hash);
        }
    }
    hash_size++;
}


template<typename T>
void HashSet<T>:: insert(Node** Hash, const T& element)
{
        int index=hashFunction(element)%hash_capacity; 
        Node* addon= new Node();
        addon->key=element; 
        addon->next=hash[index]; 
        hash[index]=addon;   
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{   
    int index=hashFunction(element)%hash_capacity;
    for(Node* temp=hash[index];temp!=nullptr; temp=temp->next)
    {
        if(temp->key==element)
        {
            return true; 
        }
    }
    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return hash_size;
}


template<typename T>
void HashSet<T>:: deleteall()
{
    for (int n=0; n<hash_capacity; n++)
    {
        deletenode(hash[n]);
    }
    delete hash; 
}


template<typename T>
void HashSet<T>:: deletenode(Node* L)
{
    if(L!=nullptr)
    {
        deletenode(L->next);
        delete L; 
    }
}


template<typename T>
void HashSet<T>:: resize(Node** Hash)
{
    Node**copy=hash; 
    hash_capacity=hash_capacity*2; 
    hash=new Node* [hash_capacity];
    for(int i=0; i<hash_capacity;i++)
    {
        hash[i]=nullptr; 
    }
    for( int n=0; n<(hash_capacity/2);n++)
    {
        for (Node* temp=copy[n];temp!=nullptr; temp=temp->next)
        {
            insert(hash,temp->key);
        }
    }
    for(int j=0; j<hash_capacity/2; j++)
    {
        deletenode(copy[j]);
    }
    delete[] copy; 
}


template<typename T>
void HashSet<T>:: copyall(const HashSet& s)
{
    hashFunction=s.hashFunction;
    hash= new Node*[s.hash_capacity];
    for( int i=0; i<s.hash_capacity;i++)
    {
        Node* newnode=hash[i];
        for(Node* temp=s.hash[i];temp!=nullptr;temp=temp->next)
        {    
            newnode= new Node(); 
            newnode->key=temp->key;
            newnode->next=temp->next;   
            newnode=hash[i];  
        }
    }
}


template<typename T>
void HashSet<T>:: createnewhash(const HashSet& s)
{
    hash=new Node*[s.hash_capacity];
    for (int i=0; i<s.hash_capacity;i++)
    {
        hash[i]=nullptr; 
    }
}

#endif // HASHSET_HPP

