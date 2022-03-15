#ifndef Output_h
#define Output_h

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

// this class is built for the single output redirect operator
class Output : public Base{

protected:

  Base* l;            // base pointer - left operans
  string fileName;    // name of file to be written to

public:

  // contructor - takes cmd and filename
  Output(Base* left, string file)
  {
    l = left;
    fileName = file;
  }

  // change the stdout
  void changeStdOut(int fd)
  {
    dup2(fd,1);
  }

  //change std in
  void changeStdIn(int fd)
  {
    dup2(fd, 0);
  }

  // save original stdout
  int backupStdOut()
  {
    return dup(1);
  }

  // save original std in
  int backupStdIn()
  {
    return dup(0);
  }

  // return integer value the holds our file
  int getOutputFile(std::string fileName)
  {
      //open output file
      return open(fileName.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  }

  bool execute()
  {
    bool valid = false;
    // save stdout & in backups
    int backup_Out = backupStdOut();
    int backup_In  = backupStdIn();

    // get file
    int fileNum = getOutputFile(fileName);

    changeStdOut(fileNum);

    // check if execute passes or not
    // restore stdout if fails as shown at bottom
    if(l->execute())
    {
      valid = true;
    }
    else
    {
      valid = false;
      changeStdOut(backup_Out);
    }

    // used to clear the buffer to avoid stdout issue
    fflush(stdout);     // flush output buffer
    close(fileNum);     // close getOutputFile

    // restore to original stdout
    changeStdOut(backup_Out);

    return valid;
  }

};

#endif
