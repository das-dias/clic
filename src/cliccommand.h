/** **********************************
* *[author] Diogo André (git-hub : das-dias)
* *[date] 24-02-2022
* *[filename] cliccommand.h
* *[summary] Console Line Interpreter written in C (CLIC) is a command line interpreter library
                fully written in C, allowing for the fast and easy integration of the library in other
                console applications, and with another languages such as Rust-lang.
                Command Class header file.
 ***********************************
*/
#ifndef _CLICCOMMAND_H_
#define _CLICCOMMAND_H_

#include <stdlib.h> /* for using malloc/realloc/free */
#include <string.h> /* for using memcpy/memmove */
#include "uthash.h" /* for being able to create  */

#ifndef RETURN_SUCCESS
#define RETURN_SUCCESS 0
#endif
#ifndef RETURN_FAILURE
#define RETURN_FAILURE 1
#endif

#ifndef MAXCHAR_NAME /* Maximum characters of command's name string */
#define MAXCHAR_NAME 16
#endif // !MAXCHAR_NAME

#ifndef MAXCHAR_HELP /* Maximum characters of command's help string */
#define MAXCHAR_HELP 255
#endif // !MAXCHAR_HELP


/**
* *[name] CLICCommand
* *[description] Command unit structure of the CLIC interface
* ?[variables]
* @par name ( char* ) : Name of the command used to call it;
* @par help ( char* ) : Help string stating the description of the command and its variables/arguments
* @par method ( void (*)(int, char*[], char*) ) : Associated method to the command;
*/
typedef struct cliccommand {
    char* name; // name of the command, and key of the hashable command
    char* help; // help string of the command
    void (*method)(int, char*[], char*); // associated method of the command
    UT_hash_handle hh; /* makes this structure hashable */
} cliccommand;

/**
* [name] cliccommand_
* *[description] cliccommand constructor
* ?[input]
* @par name (char*) : name of the command
* @par help (char*) : help string descriptor of the command and its arguments
* @par method (void (*)(int, char*[], char*))
* ![output]
* @par self (cliccommand*) : pointer to cliccommand object being constructed
*/
cliccommand cliccommand_(char* name, char* help, void (*method)(int, char*[], char*));

/**
* [name] _cliccommand
* *[description] cliccommand destructor
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object being destructed
* ![output]
* @par success (int) : integer reveiling the success of destruction of the object
*/
int cliccommand_(cliccommand* self);

/**
* [name] clicc_getName
* *[description] get the name descriptor of a command
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object
* ![output]
* @par name (char*) : name field of the command object
*/
char * clicc_getName(cliccommand* self);

/**
* [name] clicc_getHelp
* *[description] get the help descriptor of a command
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object
* ![output]
* @par help (char*) : help field of the command object
*/
char * clicc_getHelp(cliccommand* self);

/**
* [name] clicc_execute
* *[description] execute the method associated to the command
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object
* ![output]
* @par outputHistory (char*) :  the output history resultant of 
* @                             the execution of the command's associated method
*/
void clicc_execute(cliccommand* self, char * outputHistory);

#endif /* CLIC_H_ */