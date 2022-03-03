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
* @par inputBuffer (char*) : input buffer register
* @par cmdName (char*) : command's name
* @par argc (int *) : pointer to the commands name
* @par argv (char**) :  array of c-strings
* ![output]
* @par success (int) : integer reporting the success or insuccess of the destruction
*/
int clicshell_preprocessCommand(clicshell* self, char* inputBuffer, char* cmdName, int* argc, char** argv)
{
    //split the received input buffer in multiple tokens
    char* token = strtok(inputBuffer, (const char*)self->variableDelimiter);
    //the first token is the name of the commnd to be executed
    if(token)
    {
        if( strcpy(cmdName, token) );
        else return EXIT_FAILURE;
        token = strtok(NULL, (const char*) self->variableDelimiter ); // token is temporary memmory
        // the remaining variable-argument pairs are to be stored in argv
        *argc = 0;
        while( token != NULL )
        {
            argv[*argc] = (char*) malloc(sizeof(char)*strlen(token)+1);
            strcpy(argv[*argc], token);
            if ( strlen((argv)[*argc] ) );   
            else
                return EXIT_FAILURE;
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
    fgets(inputBuffer, MAXCHAR_INPUTBUF, stdin);
}

/**
* [name] clicshell_setupNewHistoryEntry
* *[description]    Shell command for printting a new date time
* *                 to the console terminal
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par none (void) :
*/
void clicshell_setupNewHistoryEntry(clicshell* self)
{
    /* obtain the current date and time */
    time_t now = time(0);
    char* nowDateTime = ctime(&now);
    /* write to file */
    console_msg(self->logger,sformat("new log> %s\n\r", nowDateTime));
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
void clicshell_exit(clicshell* self, int argc, char** argv)
{
    int exitIndex = 0;
    char* variables[1] = {
        "ei" /* exit index */
    };
    char* receivedVariable;
    char* receivedArgument;
    u_int8_t varAttributed = 0;
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
        varAttributed = 0; /* no var was attributed yet*/
        if( (receivedVariable = strtok(argv[i], (const char*) self->argumentDelimiter ) ) != NULL)
        {    
            if( (receivedArgument = strtok(NULL, (const char*) self->argumentDelimiter ) ) != NULL)
            {
                /* issue variable string comparing phase */
                for(int j = 0; j< size; j++)
                {
                    if(!strcmp(variables[j], receivedVariable))
                    {
                        for(; *receivedArgument; (*receivedArgument)++)
                            if(!isalnum(*receivedArgument))
                            {
                                console_error( self->logger, sformat("Received exiting index [%s] is not an integer.\n", receivedArgument) );
                                return;
                            }
                        exitIndex = atoi(receivedArgument);
                        /* signal var attribution */
                        varAttributed = 1;
                        break; /* break nested for loop */
                    }
                }
                if(!varAttributed)
                {
                    console_error( self->logger, sformat("Unrecognized variable [%s].\n", receivedVariable) );
                    return;
                }        
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
    console_msg( self->logger, sformat("Exiting - %d", &exitIndex) );
    exit(exitIndex);
}

/**
* [name] clicshell_exitHelp
* *[description] Shell command for exiting the shell with a determined success index
* ?[input]
* @par self (clicshell*) : pointer to clicshell objectß
* ![output]
* @par helpString (char*) : string containing the help information of the exit function
*/
void clicshell_exitHelp(clicshell* self)
{
    char* exitHelp = "exit - [description] : exit application - [commands] : ei--[(int) 0-3] application exit state parameter";
    console_msg(self->logger, exitHelp);
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
* @par void (none) :
*/
void clicshell_automaticCommandFeed(clicshell* self, int argc, char** argv)
{
    char filePath[MAXCHAR_INPUTBUF/2] = "";
    char inputBuf[MAXCHAR_INPUTBUF];
    char* variables[1] = {
        "f" /* exit index */
    };
    char* receivedVariable;
    char* receivedArgument;
    u_int8_t varAttributed = 0;
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
        /* signal that no variables was yet attributed */
        varAttributed = 0;
        if( (receivedVariable = strtok(argv[i], (const char*) self->argumentDelimiter ) ) != NULL)
        {    
            if( (receivedArgument = strtok(NULL, (const char*) self->argumentDelimiter ) ) != NULL)
            {
                /* issue variable string comparing phase */
                for(int j = 0; j< size; j++)
                {
                    if(!strcmp(variables[j], receivedVariable))
                    {
                        /* copy the received argument into file path */
                        strcpy(filePath, receivedArgument);
                        if(!strlen(filePath))
                        {
                            console_error(self->logger, "No argument was received.\n");
                            return;
                        }
                        /* signal variable attribution */
                        varAttributed = 1;
                        break;/* break nested for loop */
                    }
                }
                if(!varAttributed)
                {
                    console_error( self->logger, sformat("Unrecognized variable [%s].\n", receivedVariable) );
                    return;
                } 
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
    /* if the file path is not the predefined value, open the file and extract the command strings from there*/
    if(strlen(filePath))
    {
       FILE* commandFeedFile;
       if( ( commandFeedFile = fopen(filePath, "r") ) == NULL)
       {
           console_error( self->logger, sformat("Error opening file - %s\n", filePath) ) ; /* log error to console */
           return; /* perform no further operations */
       }
       // if file opening to read was successfull
       while( fscanf(commandFeedFile, "%s", inputBuf) )
       {
            //store the read line on the command stack
            CommandStack* cs = NULL;
            strcpy(cs->receivedCommand, inputBuf);
            HASH_ADD_INT(self->commandStack, id, cs);
       }
    }
}
/**
* [name] clicshell_acfHelp
* *[description] Help string of the automaticCommandFeed method of the shell
* ?[input]
* @par self (clicshell*) : pointer to clicshell object
* ![output]
* @par helpString (char*) : string containing the help information of the automaticCommandFeedthrough function
*/
void clicshell_acfHelp(clicshell* self)
{
    char* acfHelp = "acf - [description] : automatic command feedthrough - [arguments] : f--[(string) *filepath* ] text file path of commands.\n";
    console_msg(self->logger, acfHelp);
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
    clicshell_acfHelp(self);
    clicshell_exitHelp(self);
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
void clicshell_addCommand( clicshell* self, char* nam, char* help, void (*method)(int, char**) )
{
    cliccommand* cmd = cliccommand_alloc(nam, help, method);
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
    console_msg(self->logger, "CLIC version 1.1\n");
    console_msg(self->logger, "\n[!] Save terminal output to a file: ");
    console_msg(self->logger, "./[main_file_name] > [history_text_file_name].txt\n");
    console_msg(self->logger, "\n[!] View saved terminal output history file: ");
    console_msg(self->logger, "cat [history_text_file_name].txt\n");
    /* initialize a new history entry to the terminal */
    clicshell_setupNewHistoryEntry(self);
    do
    {
        char inputBuf[MAXCHAR_INPUTBUF];
        char cmdName[MAXCHAR_NAME];
        int argc = 0;
        char* argv[MAX_ARGS] = {"\0"};
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
        if (clicshell_preprocessCommand(self, inputBuf, cmdName, &argc, argv) == EXIT_SUCCESS)
        {
            if(!strcmp(cmdName, "help")) /* is help command? */
                clicshell_help(self);
            else if (!strcmp(cmdName, "exit"))  /* is exit command? */
                clicshell_exit(self,argc, argv);
            else if (!strcmp(cmdName, "acf"))  /* is acf command? */
                clicshell_automaticCommandFeed(self, argc, argv);
            else{
                cliccommand* cmd = NULL;
                HASH_FIND_STR(self->commands, cmdName, cmd);
                if(cmd){ /* if command exists in the shell's database */
                    /* execute the command with the respective parameters */
                    cmd->method(argc, argv);
                } else {
                    /* command doesn't exist */
                    console_error( self->logger, sformat("Non existant command - %s\n", cmdName) ); /* issue error log to console*/
                }
            }
        }
        else {
            console_error(self->logger, "Bad command preprocessing.\n");
        }
        
        // clear allocated memory at the end of each creation cycle
        for(int i=0; i<MAX_ARGS; i++)
            if(strlen(argv[i]))
                free(argv[i]);
        free(argv);
        
    } while (1);
}