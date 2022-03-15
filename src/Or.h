#ifndef Or_h
#define Or_h

#include  <stdio.h>
#include  <sys/types.h>
#include "../src/Base.h"

using namespace std;

class Or : public Base{
    
protected:
    
    Base* left;         // base ptr left
    Base* right;        // base ptr right
    
public:
    
    // or constructor takes L and R base type ptrs
    Or(Base* left, Base* right)
    {
        // initialize passed ptrs to data members
        this->left = left;
        this->right = right;
    }
    
    // OR - execute: will return a bool (t or f)
    // returns true if one of the execute passes
    bool execute()
    {
        bool valid = false;             // return value - bool
        
        if(left->execute() == 0)        // left op no pass
        {
            if(right->execute() == 1)
            {
                valid = true;           // right op passes
            }
            else
            {
                valid = false;          // means right side AND left DNP
            }
        }
        else
        {
            valid = true;               // first execute was valid
        }
        // return bool value for OR logic
        return valid;
    }
    
};


#endif /* or_h */

