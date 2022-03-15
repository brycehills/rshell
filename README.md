### Compiling rshell on hammer:
```
1. git clone https://github.com/cs100/assignment-1-abc1234.git
2. git submodule init
3. git submodule update
4. cmake3 .
5. make
6. run executables ./test or ./rshell from main directory
```

# Coding Requirements
Extend your rshell program so that it properly handles input redirection <, output redirection > and >>, and piping |. This will require using the Unix functions dup and pipe. You can find help on how to use these functions in the man pages.
As an example, after this assignment, your program should be able to successfully handle the following command:
$ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2
IMPORTANT: This is a necessary but not sufficient test case. You must come up with others on your own.
Bash has an extensive syntax for redirection, and you are not required to implement all of it but only <, >, >>, and | as listed above. But if you're curious, see the linux documentation project's bash io-redirection tutorial for details.
# Submission
Make sure all branches are merged into the master branch, create a tag called hw4. Make sure the master branch is committed and pushed to your remote repository. You should also update your the design document that you created for Assignment 1 with the additional classes that you added to your system, as well as updating any previous classes that you modified.

NOTE: git push will not automatically push tags to your repository. Use git push origin hw4 to update your repository to include the hw4 tag. Additional information about git tags can be found here.

IMPORTANT: You should verify these commands work for your repository by cloning a fresh copy of your repository, checking out the tag, and confirming everything functions correctly.  on hammer.cs.ucr.edu to verify that you've submitted your code successfully. If you forget how to use git, two students from previous cs100 courses (Rashid Goshtasbi and Kyler Rynear) made video tutorials on the git commands needed to submit your assignments via Github.

Do not wait to upload your assignment to Github until the project due date. You should be committing and uploading your assignment continuously. If you wait until the last day and can't figure out how to use git properly, then you will get a zero on the assignment. NO EXCEPTIONS.
# Project Structure
Your project structure should follow the structure outlined in Assignment 2. You should add additional unit tests using the Google Test framework for the additional classes, functions, and systems that you create for this assignment as well as keeping and updating (if necessary) the tests for the classes, functions, and systems used in the previous assignment. The additional functionality created for this assignment should not break any of the functionality from the previous assignment and should work seamlessly with it. You should also create bash scripts as integration tests for your system to validate that all the components work together as expected by the user. This type of testing is much more efficient than testing it by hand after each change.

Your code must not generate any warnings during compilation, and you must follow the CalTech coding guidelines, as stated in the syllabus. Your final rshell and test executables must have no memory leaks.
Coding Conventions
Your code must not generate any warnings on compilation.
You must follow the CalTech coding guidelines, as stated in the syllabus.
Your final executable must have no memory leaks.
Collaboration Policy
You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the Unix functions.

You are ENCOURAGED to talk with other students about test cases. You are allowed to freely share ideas in this regard.

You are ENCOURAGED to look at bash's source code for inspiration.
# Grading

| Points        | Description   |
| ------------- | ------------- |
| 5             | Code Comments |
| 5             | Following Style Guidelines |
| 10             | Updated Design Document  |
| 10             | Sufficient Test Cases |
| 20             | Input Redirection (<) |
| 25             | Output redirection (> and >>)  |
| 25             | Piping | |
| 100            | Total    |









