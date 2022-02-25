/** **********************************
* *[author] Diogo André (git-hub : das-dias)
* *[date] 24-02-2022
* *[filename] clicshell.h
* *[summary] Console Line Interpreter written in C (CLIC) is a command line interpreter library
                fully written in C, allowing for the fast and easy integration of the library in other
                console applications, and with another languages such as Rust-lang.
                Shell class implementation file
 ***********************************
*/
#include "clicshell.h"

/**
* [name] clicshell_alloc
* *[description] clicshell constructor
* ?[input]
* @par void
* ![output]
* @par self (clicshell*) : pointer to clicshell object being constructed (shell object)
*/
clicshell clicshell_alloc(void)
{

}

/**
* [name] clicshell_free
* *[description] clicshell destructor
* ?[input]
* @par self (clicshell*) : pointer to clicshell object being destructed
* ![output]
* @par success (int) : integer reporting the success or insuccess of the destruction
*/
int clicshell_free(clicshell* self)
{

}

/**
* [name] clicshell_getHistoryFilepath
* *[description] See the currently settked history file path
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par historyFilepath (char*) : return the currently selected history file path
*/
char* clicshell_getHistoryFilepath(clicshell* self)
{

}

/**
* [name] clicshell_overwritePromptMessage
* *[description] Settle a new history filepath for the shell
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newHistoryFilepath (char*) : the new history filepath
* ![output]
* @par none (void)
*/
void clicshell_overwriteHistoryFilepath(clicshell* self, char* newHistoryFilepath)
{

}

/**
* [name] clicshell_getPromptMessage
* *[description] See the currently settked prompting message
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par promptMessage (char*) : return the currently selected prompting message
*/
char* clicshell_getPromptMessage(clicshell* self)
{

}

/**
* [name] clicshell_overwritePromptMessage
* *[description] Settle a new prompting message
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newPromptMessage (char*) : the new prompting message
* ![output]
* @par none (void)
*/
void clicshell_overwritePromptMessage(clicshell* self, char* newPromptMEssage)
{

}

/**
* [name] clicshell_getVariableDelimiter
* *[description] See the currently settled variable delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par variableDelimiter (char*) : return the currentçy selected characters delimitting variables
*/
char* clicshell_getVariableDelimiter(clicshell* self)
{

}

/**
* [name] clicshell_overwriteVariableDelimiter
* *[description] Change the currently settled variable delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newVariableDelimiter (char*) : the new variable delimiter set of characters
* ![output]
* @par none (void)
*/
void clicshell_overwriteVariableDelimiter(clicshell* self, char* newVariableDelimiter)
{

}

/**
* [name] clicshell_getArgumentDelimiter
* *[description] See the currently settled argument delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell objectß
* ![output]
* @par argumentDelimiter (char*) : return the currentçy selected characters that are delimiting arguments from variables
*/
char* clicshell_getArgumentDelimiter(clicshell* self)
{

}

/**
* [name] clicshell_overwriteArgumentDelimiter
* *[description] Change the currently settled argument delimiter
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newArgumentDelimiter (char*) : the new argument delimiter to be used
* ![output]
* @par none (void)
*/
void clicshell_overwriteArgumentDelimiter(clicshell* self, char* newArgumentDelimiter)
{

}

/**
* [name] clicshell_processCommand
* *[description] Apply pre processing on the received input string from console
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par success (int) : integer reporting the success or insuccess of the destruction
*/
int clicshell_preprocessCommand(clicshell* self, char* inputBuffer, char* cmdName, int* argc, char* (*argv[]))
{

}

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
void clicshell_promptUser(clicshell* self, char* promptMessage, char* receivedMessage)
{

}

/**
* [name] clicshell_setupNewHistoryEntry
* *[description]    Shell command for setting up the header of
* *                   new history file entries
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par success (int) : integer indicating the success of the method's operation
*/
int clicshell_setupNewHistoryEntry(clicshell* self)
{

}

/**
* [name] clicshell_updateHistory
* *[description]    Shell command for writting a new history file entry
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par newHistory (char*) : new history entry to add to the history tex file
* ![output]
* @par success (int) : integer indicating the success of the method's operation
*/
int clicshell_updateHistory(clicshell* self, char* newHistory)
{

}

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
void clicshell_exit(clicshell* self, int argc, char *argv[])
{

}

/**
* [name] clicshell_exitHelp
* *[description] Shell command for exiting the shell with a determined success index
* ?[input]
* @par self (clicshell*) : pointer to clicshell objectß
* ![output]
* @par helpString (char*) : string containing the help information of the exit function
*/
char* clicshell_exitHelp(clicshell* self)
{

}

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
void clicshell_automaticCommandFeed(clicshell* self, int argc, char *argv[], char* outputHistory)
{

}

/**
* [name] clicshell_acfHelp
* *[description] Help string of the automaticCommandFeed method of the shell
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par helpString (char*) : string containing the help information of the automaticCommandFeedthrough function
*/
char* clicshell_acfHelp(clicshell* self)
{

}

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
void clicshell_help(clicshell* self)
{

}

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
int clicshell_addCommand( clicshell* self, char* name, char* help, void (*method)(int, char*[], char*) )
{

}

/**
* [name] clicshell_run
* *[description]    Shell command for running main loop
* todo : This method is ought to run in a parallel processing thread
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par none (void)
*/
void clicshell_run(clicshell* self)
{

}