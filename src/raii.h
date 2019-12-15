#ifndef RAII_H                                                                      // make sure header is not already defined
#define RAII_H                                                                      // define header

#include <stdlib.h>
#include <iostream>                                                               // for debugging
//#include <opencv2/objdetect.hpp>

// Class for RAII
class RAII
{
    public:
        // constructor and destructor
        RAII(size_t size);
        ~RAII();
        RAII(const RAII &source);
        //RAII &operator=(const RAII &source);
        RAII(RAII &&source);
        //RAII &operator=(RAII &&source);
    
    private:
        int _size;
        int *_data;
};

#endif