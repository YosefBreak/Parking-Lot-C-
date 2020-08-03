
// Created by Yosef on 05/01/2020.

#ifndef MTM_UNIQUEARRAY_H
#define MTM_UNIQUEARRAY_H
#include <iostream>


/*                          *  ~~ UniqueArray.H implementaion & initialization Class ~~                        */

template <class Element, class Compare >
class UniqueArray;


/*
 * Node Class implement & initialization.
 * Node Class  was utilized to implement Unique Class.
 * Node Class was decleared as a friend with Unique Class.
 */
template <class Element,class Compare>

class Node {
private:

    Element *ele;
    unsigned int serial_number;
    bool isempty;

public:
    /* Node Class include two types of Constructors & an copy Constructor
     * 1- a defaulted constructor which implemented as ()
     * 2- Constructor which absorb an element as input.
     * 3- Copy Constructor.
     * */
    Node() {
        isempty = true;
        ele = NULL;
    };
    Node(const Element &element, int serial_num) : serial_number(serial_num) {
        Element *tmp = new Element(element);
        ele = tmp;
    };
    Node(const Node &tmp) : serial_number(tmp.serial_number), isempty(tmp.isempty)  {
        this->ele = new Element(*(tmp.ele));
    };

    /* Destructor : Freeing allocated memory and turning unused space to true  */
    ~Node() {
        delete (ele);
        isempty = true;
    };

    /* overriding opertator =*/
    Node &operator=(const Node &tmp) {
        this->ele = new Element(*(tmp.ele));
        this->serial_number = tmp.serial_number;
        this->isempty = tmp.isempty;
        return *this;
    }

    Element* Getele() {
        return ele;
    }

    bool GetFlag(){
            return isempty;
    }


    friend class UniqueArray<Element, Compare>;
};

/*                              ~~~ Our main Class , UniqueArray.h ~~~                                               */
template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {
    /*
      * size - the maximum size of our  UniqueArray
      * iterator - our iterator point to the next empty space at the UniqueArray
      * if the array is full then iterator = size
      * counter - how many element we have at our UniqueArray
      */
private:
    unsigned int size;
    unsigned int iterator;
    unsigned int counter;
    Node<Element,Compare> * array;

public:
    UniqueArray() = default;
    UniqueArray (const UniqueArray& other);
    UniqueArray (unsigned int size);
    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[] (const Element& element) const;
    bool remove(const Element& element);
    unsigned int getCount() const;
    unsigned int getSize() const;

    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };
    UniqueArray filter(const Filter& f) const;
    class UniqueArrayIsFullException{};

    /* Notfound - a throwed expectation as a result of not finding the requested element at our Class */
    class Notfound{};

    /* IsThere - a function which absorb as a parameter Element and check if it exist at our Class
     * return Value : exception if not found , else his serial number.
     */
    unsigned int  IsThere ( const Element& element ) const ;

    /* Getnext - a function which move the iterator to the next empty place at our Class */
    unsigned  int Getnext();

    /* Get an Element by index */
    Node<Element,Compare>* Getbyid(unsigned int i) const
    {
        return &array[i];
    }
};


#include "UniqueArrayImp.h"

#endif //MTM_UNIQUEARRAY_H
