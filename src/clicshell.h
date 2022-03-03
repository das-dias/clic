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
#include <ctype.h>
#include <stdio.h>
#include <string.h> /* for using memcpy/memmove */
#include <time.h>
#include "cliccommand.h" /* for interfacing shell commands with the shell itself */
#include "lib/c-consolelogger/src/consolelogger.h"



#ifndef RETURN_SUCCESS
#define RETURN_SUCCESS 0
#endif
#ifndef RETURN_FAILURE 
#define RETURN_FAILURE 1
#endif

#ifndef MAXCHAR_HISTFILE
#define MAXCHAR_HISTFILE 26
#endif

#ifndef MAXCHAR_PROMPT
#define MAXCHAR_PROMPT 15
#endif

#ifndef MAXCHAR_ARGDELIM
#define MAXCHAR_ARGDELIM 3
#endif

#ifndef MAXCHAR_VARDELIM
#define MAXCHAR_VARDELIM 3
#endif

#ifndef MAXCHAR_INPUTBUF
#define MAXCHAR_INPUTBUF 127
#endif

#ifndef MAXCHAR_OUTHIST
#define MAXCHAR_OUTHIST 255
#endif

#ifndef MAX_ARGS
#define MAX_ARGS 63
#endif

#ifndef MAXCHAR_ARGV
#define MAXCHAR_ARGV 15
#endif

typedef struct CommandStack{
    int id; // key of the hashed item
    char receivedCommand[MAXCHAR_INPUTBUF]; /* item to be hashed */
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
    console* logger;
    struct cliccommand* commands; /* hashmap of the commands belonging to the shell, hashable by their name */
    struct CommandStack* commandStack; /* hashmap stack of the received console strings */
    char* promptMessage;
    char* variableDelimiter; /* Delimiter of the several possible variable/argument pairs to be parsed through the shell */
    char* argumentDelimiter; /* Delimiter between the variable and its associated parameter */
} clicshell;

/*
* func_type - definition of the type of function to be accepted for each possible variable's argument extraction
*/
typedef void (*func_type)(clicshell* self, char*, void*);

/**
* [name] clicshell_alloc
* *[description] clicshell constructor
* ?[input]
* @par void
* ![output]
* @par self (clicshell*) : pointer to clicshell object being constructed (shell object)
*/
clicshell* clicshell_alloc(void);

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
* [name] clicshell_getPromptMessage
* *[description] See the currently settked prompting message
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par promptMessage (char*) : return the currently selected prompting message
*/
char* clicshell_getPromptMessage(clicshell* self);

/**
* [name] clicshell_overwritePromptMessage
* *[description] Settle a new prompting message
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newPromptMessage (char*) : the new prompting message
* ![output]
* @par none (void)
*/
void clicshell_overwritePromptMessage(clicshell* self, char* newPromptMEssage);

/**
* [name] clicshell_getVariableDelimiter
* *[description] See the currently settled variable delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par variableDelimiter (char*) : return the currentçy selected characters delimitting variables
*/
char* clicshell_getVariableDelimiter(clicshell* self);

/**
* [name] clicshell_overwriteVariableDelimiter
* *[description] Change the currently settled variable delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newVariableDelimiter (char*) : the new variable delimiter set of characters
* ![output]
* @par none (void)
*/
void clicshell_overwriteVariableDelimiter(clicshell* self, char* newVariableDelimiter);

/**
* [name] clicshell_getArgumentDelimiter
* *[description] See the currently settled argument delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell objectß
* ![output]
* @par argumentDelimiter (char*) : return the currentçy selected characters that are delimiting arguments from variables
*/
char* clicshell_getArgumentDelimiter(clicshell* self);

/**
* [name] clicshell_overwriteArgumentDelimiter
* *[description] Change the currently settled argument delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newArgumentDelimiter (char*) : the new argument delimiter to be used
* ![output]
* @par none (void)
*/
void clicshell_overwriteArgumentDelimiter(clicshell* self, char* newArgumentDelimiter);

/**
* [name] clicshell_processCommand
* *[description] Apply pre processing on the received input string from console
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par inputBuffer (char*) : input buffer register
* @par cmdName (char*) : command's name
* @par argc (int *) : pointer to the commands name
* @par argv (char**) :  array of c-strings
* ![output]
* @par success (int) : integer reporting the success or insuccess of the destruction
*/
int clicshell_preprocessCommand(clicshell* self, char* inputBuffer, char* cmdName, int *argc, char** argv);

/**
* [name] clicshell_promptUser
* *[description]  Prompt the shell user for a new input command and return it.
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par promptMessage (char*) : Message appearing when prompting the user for input
* @par receivedMessage (char*) : Message that was received after prompting the user
* ![output]
* @par (void) : nothing
*/
void clicshell_promptUser(clicshell* self, char* inputBuffer);

/**
* [name] clicshell_setupNewHistoryEntry
* *[description]    Shell command for printting a new date time
* *                 to the console terminal
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par none (void) :
*/
void clicshell_setupNewHistoryEntry(clicshell* self);

/**
* [name] clicshell_exit
* *[description] Shell command for exiting the shell with a determined success index
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par argc (int) : number of arguments received and contained within argv
* @par argv (char*[]) : received array of strings containing the severall 
* @                     received varibale-argument pairs
* ![output]
* @par none (void)
*/
void clicshell_exit(clicshell* self, int argc, char** argv);

/**
* [name] clicshell_exitHelp
* *[description] Shell command for exiting the shell with a determined success index
* ?[input]
* @par self (clicshell*) : pointer to clicshell objectß
* ![output]
* @par helpString (char*) : string containing the help information of the exit function
*/
void clicshell_exitHelp(clicshell* self);

/**
* [name] clicshell_automaticCommandFeed
* *[description]    Shell command for reading and ordered sequence of commands
* *                 from a file which will be contained within the input arguments
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par argc (int) : number of arguments received and contained within argv
* @par argv (char*[]) : received array of strings containing the severall 
* @                     received varibale-argument pairs
* ![output]
* @par outputHistory (char*) : output history of the functions print-to-console operations
*/
void clicshell_automaticCommandFeed(clicshell* self, int argc, char** argv);

/**
* [name] clicshell_acfHelp
* *[description] Help string of the automaticCommandFeed method of the shell
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par helpString (char*) : string containing the help information of the automaticCommandFeedthrough function
*/
void clicshell_acfHelp(clicshell* self);

/**
* [name] clicshell_help
* *[description]    Shell command for outputing to console the
* *                 commands that belong to the shell and info. on their
* *                 respective variable-argument pairs
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par none (void)
*/
void clicshell_help(clicshell* self);

/**
* [name] clicshell_addCommand
* *[description]    Shell command for outputing to console the
* *                 commands that belong to the shell and info. on their
* *                 respective variable-argument pairs
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par name (char*) : name of the command
* @par help (char*) : help string descriptor of the command and its arguments
* @par method (void (*)(int, char*[], char*)) : command's associated method to be executed
* ![output]
* @par success (int) : integer encoding the success of the function
*/
void clicshell_addCommand( clicshell* self, char* nam, char* help, void (*method)(int, char**) );

/**
* [name] clicshell_run
* *[description]    Shell command for running main loop
* todo : This method is ought to run in a parallel processing thread
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par none (void)
*/
void clicshell_run(clicshell* self);

#endif /* _CLICSHELL_H_ */