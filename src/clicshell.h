/** **********************************
* *[author] Diogo André (git-hub : das-dias)
* *[date] 24-02-2022
* *[filename] clicshell.h
* *[summary] Console Line Interpreter written in C (CLIC) is a command line interpreter library
                fully written in C, allowing for the fast and easy integration of the library in other
                console applications, and with another languages such as Rust-lang.
                Shell class header file
 ***********************************
*/
#ifndef _CLICSHELL_H_
#define _CLICSHELL_H_

#include <stdlib.h> /* for using malloc/realloc/free */
#include <string.h> /* for using memcpy/memmove */
#include "src/cliccommand.h" /* for interfacing shell commands with the shell itself */

#ifndef RETURN_SUCCESS
#define RETURN_SUCCESS 0
#endif
#ifndef RETURN_FAILURE 
#define RETURN_FAILURE 1
#endif

typedef struct CommandStack{
    int id; // key of the hashed item
    char* receivedCommand; /* item to be hashed */
    UT_hash_handle hh;
} CommandStack;

/**
* *[name] clicshell
* *[description] Shell structure of the CLIC interface to interpret, save and validate commands
* ?[variables]
* @par commands (cliccommand* (hash)) : hashmap of the commands, hashable by their name
* @par commandStack (CommandStack* (hash)) : hashmap stack of the received console strings
* @par historyFileName (char*) : Name of the file in which the history of the programm will be written
* @par promptMessage (char*) : User prompt message of the shell 
* @par variableDelimiter (char) : Delimiter of the several possible variable/argument pairs to be parsed through the shell
* @par argumentDelimiter (char) : Delimiter between the variable and its associated parameter
*/
typedef struct clicshell{
    struct cliccommand *commands; /* hashmap of the commands, hashable by their name */
    struct CommandStack *commandStack; /* hashmap stack of the received console strings */
    char* historyFileName;
    char* promptMessage;
    char variableDelimiter; /* Delimiter of the several possible variable/argument pairs to be parsed through the shell */
    char argumentDelimiter; /* Delimiter between the variable and its associated parameter */
} clicshell;

/**
* [name] clicshell_alloc
* *[description] clicshell constructor
* ?[input]
* @par void
* ![output]
* @par self (clicshell*) : pointer to clicshell object being constructed (shell object)
*/
clicshell clicshell_alloc(void);

/**
* [name] clicshell_free
* *[description] clicshell destructor
* ?[input]
* @par self (clicshell*) : pointer to clicshell object being destructed
* ![output]
* @par success (int) : integer reporting the success or insuccess of the destruction
*/
int clicshell_free(clicshell* self);

/**
* [name] clicshell_processCommand
* *[description] Apply pre processing on the received input string from console
* ?[input]
* @par self (clicshell*) : pointer to clicshell object being destructed
* ![output]
* @par success (int) : integer reporting the success or insuccess of the destruction
*/
int clicshell_preprocessCommand(clicshell* self, char* inputBuffer, char* cmdName, int* argc, char* (*argv[]));

#endif /* _CLICSHELL_H_ */