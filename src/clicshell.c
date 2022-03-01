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
clicshell* clicshell_alloc(void)
{
    clicshell* self = NULL;

    self->logger = console_alloc();
    self->commands = NULL;
    self->commandStack = NULL;
    self->historyFilepath = (char*) malloc(sizeof(char) * MAXCHAR_HISTFILE);
    strcpy( self->historyFilepath, "./history-log.txt" );
    self->promptMessage = (char*) malloc(sizeof(char) * MAXCHAR_PROMPT);
    strcpy( self->promptMessage, "clic$>" );
    self->variableDelimiter = (char*) malloc(sizeof(char) * MAXCHAR_VARDELIM);
    strcpy( self->variableDelimiter, " " );
    self->argumentDelimiter = (char*) malloc(sizeof(char) * MAXCHAR_ARGDELIM);
    strcpy( self->argumentDelimiter, "-");
    return self;
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
    if(self)
    {   
        console_free(self->logger);
        if(self->commands) free(self->commands);
        if(self->commandStack) free(self->commandStack);
        free(self);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
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
    return self->historyFilepath;
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
    self->historyFilepath = (char*) realloc( self->historyFilepath, sizeof(char) * (strlen( newHistoryFilepath ) + 1) );
    strcpy(self->historyFilepath, newHistoryFilepath);
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
    return self->promptMessage;
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
    self->promptMessage = (char*) realloc( self->promptMessage, sizeof(char) * (strlen( newPromptMEssage ) + 1)  );
    strcpy(self->promptMessage, newPromptMEssage);
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
    return self->variableDelimiter;
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
    self->variableDelimiter = (char*) realloc( self->variableDelimiter, sizeof(char) * (strlen( newVariableDelimiter ) + 1)  );
    strcpy(self->variableDelimiter, newVariableDelimiter);
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
    return self->argumentDelimiter;
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
    self->argumentDelimiter = (char*) realloc( self->argumentDelimiter, sizeof(char) * (strlen( newArgumentDelimiter ) + 1)  );
    strcpy(self->argumentDelimiter, newArgumentDelimiter);
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
    //split the received input buffer in multiple tokens
    char* token = strtok(inputBuffer, (const char*)self->variableDelimiter);
    //the first token is the name of the commnd to be executed
    if(token)
    {
        if( strcpy(cmdName, token) );
        else return EXIT_FAILURE;
        token = strtok(NULL, (const char*) self->variableDelimiter );
        // the remaining variable-argument pairs are to be stored in argv
        *argc = 0;
        while( token != NULL )
        {
            if ( strcpy((*argv)[*argc],token) );   
            else return EXIT_FAILURE;
            token = strtok(NULL, (const char*) self->variableDelimiter );
            (*argc)++;
        }
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
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
void clicshell_promptUser(clicshell* self, char* inputBuffer)
{
    console_msg( self->logger, sformat("%s",self->promptMessage) );
    char receivedChar;
    fgets(inputBuffer, MAXCHAR_INPUTBUF, stdin);
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
    FILE* histFile;
    /* open to append to history file */
    if( ( histFile = fopen(self->historyFilepath, "w+") )== NULL)
    {
        console_error(self->logger, sformat("Could not open file %s.\n", self->historyFilepath) );
        return EXIT_FAILURE;
    }
    /* obtain the current date and time */
    time_t now = time(0);
    char* nowDateTime = ctime(&now);
    /* write to file */
    fprintf( histFile, "new log> %s\n\r", nowDateTime);
    fclose(histFile);
    return EXIT_SUCCESS;
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
    FILE* histFile;
    /* open to append to history file */
    if( ( histFile = fopen(self->historyFilepath, "w+") ) == NULL)
    {
        console_error(self->logger, sformat("Could not open file %s.\n", self->historyFilepath) );
        return EXIT_FAILURE;
    }
    /* if opening was successful, append new history to file */
    fprintf( histFile, "%s\n\r", newHistory );
    fclose(histFile);
    return EXIT_SUCCESS;
}

/**
* *[name] clicshell_callBackWrapper
* *[description] A wrapper to extract the several possible arguments of each variable 
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* @par argc (int) : number of arguments received and contained within argv
* @par argv (char*[]) : received array of strings containing the severall 
* @                     received varibale-argument pairs
* @par variables (char *) : possible variables to correspond to the etracted arguments
* @functions (func_type *) : array of function points determining the action for each variable
* ![output]
* @par none (void)
*/
void clicshell_argumentExtractingWrapper(clicshell* self, int argc, char *argv[], char* variables[], func_type* functions, list_t* list)
{
    char* receivedVariable;
    char* receivedArgument;
    /* 
    * the size of the variables array has to be greater 
    * or equal to the number of received arguments
    */
    int size = sizeof(variables) / sizeof(*variables);
    /* for each of the arguments received */
    if(argc>size){
        console_error(self->logger, sformat("Too many arguments. Expected %d ; Received %d.\n",size, argc));
        return;
    }
    for(int i = 0; i < argc; argc++)
    {
        if(receivedVariable = strtok(argv[i], (const char*) self->argumentDelimiter ) != NULL)
        {    
            if(receivedArgument = strtok(NULL, (const char*) self->argumentDelimiter ) != NULL)
            {
                /* issue variable string comparing phase */
                for(int j = 0; j< size; j++)
                {
                    if(!strcmp(variables[j], receivedVariable))
                    {
                        (functions[j])(self, receivedArgument, list[j].data);
                    }
                }
                console_error( self->logger, sformat("Unrecognized variable [%s].\n", receivedVariable) );
                return;
            } 
            else 
            {
                console_error( self->logger, sformat("Non-existing argument to parsed variable [%s].\n", receivedVariable) ); /* log error message */
                return;
            }
        } 
        else
        {
            console_error( self->logger, "No variable received.\n"); /* log error message */
            return;
        }
    }
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
    int exitIndex = 0;
    char* variables[] = {
        "ei" /* exit index */
    };
    /* each var will be associated with one function */
    list_t vars[] = { 
        list_init(exitIndex) 
    };
    void clicshell_exit_func1(clicshell* self, char* receivedArgument, int* exitIndex);
    func_type functions[] ={
        &clicshell_exit_func1
    };
    clicshell_argumentExtractingWrapper(self, argc, argv, variables, functions, vars);
    console_msg( self->logger, sformat("Exiting - %d", exitIndex) );
    exit(exitIndex);
}

inline void clicshell_exit_func1(clicshell* self, char* receivedArgument, int* exitIndex)
{
    for(; *receivedArgument; (*receivedArgument)++)
        if(!isalnum(*receivedArgument))
        {
            console_error( self->logger, sformat("Received exiting index [%s] is not an integer.\n", receivedArgument) );
            return;
        }
    *exitIndex = atoi(receivedArgument);
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
    return "exit - [description] : exit application - [commands] : ei--[(int) 0-3] application exit state parameter";
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
    char filePath[MAXCHAR_INPUTBUF/2] = "";
    char inputBuf[MAXCHAR_INPUTBUF];
    char* variables[] = {
        "f" /* exit index */
    };
    list_t list[]={
        array_list_init(filePath)
    };
    void clicshell_acf_func1(clicshell* shell, char* receivedArgument, char* filePath);
    func_type functions[] = {
        &clicshell_acf_func1
    };
    clicshell_argumentExtractingWrapper(self, argc, argv, variables, functions, list);
    /* if the file path is not the predefined value, open the file and extract the command strings from there*/
    if(filePath != NULL)
    {
       FILE* commandFeedFile;
       if( commandFeedFile = fopen(filePath, "r") == NULL)
       {
           console_error( self->logger, sformat("Error opening file - %s\n", filePath) ) ; /* log error to console */
           return; /* perform no further operations */
       }
       // if file opening to read was successfull
       while( fscanf(commandFeedFile, "%s", inputBuf) )
       {
            //store the read line on the command stack
            CommandStack* cs;
            strcpy(cs->receivedCommand, inputBuf);
            HASH_ADD_INT(self->commandStack, id, cs);
       }
    }
}

void clicshell_acf_func1(clicshell* shell, char* receivedArgument, char* filePath)
{
    /* copy the received argument into file path */
    filePath = strcpy(filePath, receivedArgument);
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
    return "acf - [description] : automatic command feedthrough - [arguments] : f--[(string) *filepath* ] text file path of commands.\n";
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
    console_msg( self->logger, " #########################\n\tAvailable Operations:\n#########################\n" );
    while((self->commands)++)
    {
        console_msg( self->logger, sformat("%s\n",*self->commands->help) );
    }
    console_msg( self->logger, sformat("%s\n", clicshell_acfHelp(self) ) );
    console_msg( self->logger, sformat("%s\n", clicshell_exitHelp(self) ) );
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
void clicshell_addCommand( clicshell* self, char* nam, char* help, void (*method)(int, char*[], char*) )
{
    cliccommand* cmd;
    strcpy(cmd->name, nam);
    strcpy(cmd->help, help);
    cmd->method = method;
    HASH_ADD_STR(self->commands, name, cmd);
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
    /* initialize a new history entry on the history file */
    clicshell_setupNewHistoryEntry(self);
    do
    {
        char inputBuf[MAXCHAR_INPUTBUF];
        char outputHistory[MAXCHAR_OUTHIST];
        char cmdName[MAXCHAR_NAME];
        int argc = 0;
        char argv[MAX_ARGS][MAXCHAR_ARGV];
        if(self->commandStack) /* if there are commands to read from stack */
        {
            strcpy(inputBuf, self->commandStack->receivedCommand);
            /* delete head command string pointer (pop_head) */
            HASH_DEL(self->commandStack,self->commandStack);
        }    
        else {
            clicshell_promptUser(self, inputBuf);
        }
        /* after absorbing user input, preprocess the received string */
        if (clicshell_preprocessCommand(self, inputBuf, cmdName, &argc, &argv) == EXIT_SUCCESS)
        {
            if(!strcmp(cmdName, "help")) /* is help command? */
                clicshell_help(self);
            else if (!strcmp(cmdName, "exit"))  /* is exit command? */
                clicshell_exit(self,argc, argv);
            else if (!strcmp(cmdName, "acf"))  /* is acf command? */
                clicshell_automaticCommandFeed(self, argc, argv, outputHistory);
            else{
                cliccommand* cmd;
                HASH_FIND_STR(self->commands, cmdName, cmd);
                if(cmd){ /* if command exists in the shell's database */
                    /* execute the command with the respective parameters */
                    cmd->method(argc, argv, outputHistory);
                } else {
                    /* command doesn't exist */
                    console_error( self->logger, sformat("Non existant command - %s\n", cmdName) ); /* issue error log to console*/
                }
            }
        }

    } while (1);
}