/* Created and writen by yosef break */

template <class Element, class Compare>
UniqueArray<Element,Compare>::UniqueArray(unsigned int size ) :size(size),iterator(0),counter(0),
                                                               array(new Node<Element,Compare> [size]) {
}

template <class Element, class Compare>
UniqueArray<Element,Compare>::UniqueArray(const UniqueArray& other) :size(other.size),iterator(other.iterator),
                                                                     counter(other.counter) ,array(new Node<Element,Compare> [other.size]) {
    for (unsigned int i = 0; i < size; i++) {
        if (other.array[i].isempty == false) {

            array[i].ele = new Element(*other.array[i].ele);
            array[i].isempty = other.array[i].isempty;
            array[i].serial_number = other.array[i].serial_number;

        }
    }

}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::Getnext()
{
    for( unsigned int i=0 ;i<size;i++)
    {
        if(array[i].isempty == true)
        {
            return i;
        }
    }
    throw UniqueArrayIsFullException();
}

template <class Element, class Compare>
unsigned int  UniqueArray<Element,Compare>::IsThere(const Element &element) const {
    Compare comparefun = Compare();
    for (unsigned int i = 0; i < size; i++) {
        if ( array[i].isempty == false ) {
            if (comparefun(element ,*(array[i].ele))== true)
                return array[i].serial_number;
        }
    }
    throw Notfound();
}

template <class Element, class Compare>
UniqueArray<Element,Compare>::~UniqueArray() {

    delete [] array;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::insert(const Element &element) {

    unsigned int index;
    try {
        index = IsThere(element);
    }
    catch (UniqueArray<Element, Compare>::Notfound &e)
    {
        if (this->iterator == this->size) {
            throw UniqueArrayIsFullException();
        }
        Element *_insert = new Element (element);
        (array[this->iterator].ele) = _insert;
        array[iterator].isempty= false;
        array[iterator].serial_number =iterator;
        this->counter++;
        unsigned int res = array[iterator].serial_number;
        try{
            iterator = Getnext();
        }
        catch(UniqueArray<Element, Compare>::UniqueArrayIsFullException & e)
        {
            this->iterator = size;
        }
        return  res;

    }
    return index;
}

template <class Element, class Compare>
bool UniqueArray<Element,Compare>::getIndex(const Element &element, unsigned int &index) const {

    try {
        index = IsThere(element);
    }
    catch (UniqueArray<Element, Compare>::Notfound& e) {
        return false;
    }
    return true;
}

template <class Element, class Compare>
const Element* UniqueArray<Element,Compare>::operator[](const Element &element) const {
    unsigned int index;
    try {
        index = IsThere(element);
    }
    catch (UniqueArray<Element, Compare>::Notfound& e)
    {
        return nullptr;
    }
    return array[index].ele;
}


template <class Element, class Compare>
bool UniqueArray<Element,Compare>::remove(const Element &element) {
    unsigned int index ;
    try {
        index = IsThere(element);
    }
    catch (UniqueArray<Element, Compare>::Notfound& e)
    {
        return false;
    }
    this->counter--;
    delete (array[index].ele);
    array[index].isempty = true;
    array[index].ele = nullptr;
    this->iterator  = Getnext();

    return false;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::getCount() const { return this->counter;}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::getSize() const { return this->size;}

template <class Element, class Compare>
UniqueArray<Element,Compare> UniqueArray<Element,Compare>::filter(const UniqueArray<Element, Compare>::Filter &f) const {
    UniqueArray<Element,Compare> * res = new UniqueArray<Element,Compare>(this->size);
    for (unsigned int i = 0 ; i < size ; i++)
    {
        if(array[i].isempty == false)
        {
            if(f(*array[i].ele) == true)
            {
                (*res).array[i].ele = new Element(*(this->array[i].ele));
                (*res).array[i].isempty = false;
                (*res).array[i].serial_number =this->array[i].serial_number;
                res->counter++;
            }
        }
    }
    UniqueArray<Element,Compare> final (*res);
    delete(res);
    return final;
}
