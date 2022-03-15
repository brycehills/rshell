#ifndef OutputAppend_h
#define OutputAppend_h

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

// used for the output redirect operstor >>
class OutputAppend : public Base{

protected:
  //data members
  Base* l;
  string fileName;

public:

  // constrcutor takes in cmd ptr and filename to use in execute
  OutputAppend(Base* left, string file)
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

  int getOutputFile(std::string fileName)
  {
      //open output file
      // >> includes append
      return open(fileName.c_str(), O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  }

  bool execute()
  {
    bool valid = false;
    // save stdout & in backups
    int backup_Out = backupStdOut();
    int backup_In  = backupStdIn();

    int fileNum = getOutputFile(fileName);

    changeStdOut(fileNum);

    // check if excute passes or not
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
    fflush(stdout);     // flush output buffer
    close(fileNum);     // close getOutputFile

    // restore to original stdout
    changeStdOut(backup_Out);

    return 1;
  }

};

#endif
