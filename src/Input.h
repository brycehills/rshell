#ifndef Input_h
#define Input_h

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>

#include "../src/Command.h"
#include "../src/Base.h"


using namespace std;

// this class implements the input redirect operstor >
class Input : public Base{

protected:

  Base* l;          // left hand op - base *
  string fileName;  // right op is filename

public:

  // constrcutor takes in cmd ptr and filename to use in execute
  Input(Base* left, string file)
  {
    l = left;
    fileName = file;
  }

  // changes passed integer on the table to have stdout
  void changeStdOut(int fd)
  {
    dup2(fd,1);
  }

  // changes passed integer on the table to have stdin
  void changeStdIn(int fd)
  {
    dup2(fd, 0);
  }

  // save a copy of first file descriptor
  int backupStdOut()
  {
    return dup(1);
  }

  // save file descriptior
  int backupStdIn()
  {
    return dup(0);
  }

  // gets output file & opens it - returns int val of file location
  int getOutputFile(std::string fileName)
  {
      //open output file
      return open(fileName.c_str(), O_RDONLY);
  }

  bool execute()
  {
    bool valid = false;
    // save stdout & in backups
    int backup_Out = backupStdOut();
    int backup_In  = backupStdIn();

    int fileNum = getOutputFile(fileName);

    changeStdIn(fileNum);

    // check if excute passes or not
    // restore stdout if fails as shown at bottom
    if(l->execute())
    {
      valid = true;
    }
    else
    {
      valid = false;
      changeStdIn(backup_In);
    }

    //fflush(stdout);     // flush output buffer
    close(fileNum);     // close getOutputFile

    // restore to original stdin
    changeStdIn(backup_In);

    return valid;
  }

};

#endif
