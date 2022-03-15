#ifndef COLON_h
#define COLON_h

#include  <stdio.h>
#include  <sys/types.h>
#include "../src/Base.h"

using namespace std;


class Colon : public Base{

protected:

    Base* left;
    Base* right;    // right operand
    
public:

    // Colon conntructor take r pointers of type base
    Colon(Base* left, Base* right)
    {
        //initialize pointer
        this->left  = left;
        this->right = right;
    }

    // execute right
    bool execute()
    {
        bool valid = false;             // return boolean variabl
     
        if(right != NULL)
        {
        
        left->execute();
                
            if(right->execute() == 1)   // execute rhs
            {
                valid = true;           // executed so return true
            }
            else
            {
                valid = false;          // otherwise rhs failed, so return false
            }
            
        }
        
        else
        {
            return left->execute();
        }

        return valid;                   // return boolean value t or f
    }

};


#endif /* Colon_h */
