#ifndef Base_h
#define Base_h

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <cstdlib>
#include <cstring> 
#include <string> 
#include <vector>

using namespace std;

// this is our abstract base class 
class Base{
  
public:
    // contructor for abstract base class
    Base(){};

    // virtual method to be overwritten by child classes
    // returns a bool value
    virtual bool execute()=0;
    
};


#endif /* Base_h */
