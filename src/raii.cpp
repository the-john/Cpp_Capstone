//#include <iostream>                                                                     // for debug purposes
#include "raii.h"

// Class for face detection
RAII::RAII(size_t size)                                                                 // constructor
{
    _size = size;
    _data = new int[_size];
    //std::cout << "CREATING instance of RAII at " << this << " allocated with size = " << _size * sizeof(int) << " bytes" << std::endl;
}

RAII::~RAII()                                                                           // destructor
{
    //std::cout << "DELETING instance of RAII at " << this << std::endl;
    delete[] _data;
}

RAII::RAII(const RAII &source)                                                          // copy constructor
{
    _size = source._size;
    _data = new int[_size];
    *_data = *source._data;
    //std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
}

RAII &RAII::operator=(const RAII &source)                                               // copy assignment operator
{
    //std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    delete[] _data;
    _data = new int[source._size];
    *_data = *source._data;
    _size = source._size;
    return *this;
}

RAII::RAII(RAII &&source)                                                               // move constructor
{
    //std::cout << "MOVING constructor instance " << &source << " to instance " << this << std::endl;
    _data = source._data;
    _size = source._size;
    source._data = nullptr;
    source._size = 0;
}

RAII &RAII::operator=(RAII &&source)                                                    // move assignment operator
{
    //std::cout << "MOVING assignment instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    delete[] _data;
    _data = source._data;
    _size = source._size;
    source._data = nullptr;
    source._size = 0;
    return *this;
}

