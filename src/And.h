#ifndef And_h
#define And_h

#include  <stdio.h>
#include  <sys/types.h>
#include "../src/Base.h"

using namespace std;


class And : public Base{

protected:

    Base* left;     // left operand
    Base* right;    // right operand
    
public:

    // AND conntructor takes l and r pointers of type base
    And(Base* left, Base* right)
    {
        //initialize pointers
        this->left = left;
        this->right = right;
    }

    // if left evaluates to true then nwe execute right also
    bool execute()
    {
        bool valid = false;             // return boolean variable

        if(left->execute() == 1)        // if lhs is true
        {
            if(right->execute() == 1)   // then we execute rhs
            {
                valid = true;           // both executed so we return true
            }
            else
            {
                valid = false;          // otherwise rhs failed, so return false
            }
        }
        else
        {
            valid = false;              // lhs failed so return false
        }

        return valid;                   // return boolean value t or f
    }

};


#endif /* And_h */
