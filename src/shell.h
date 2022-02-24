#ifndef __CPP___SHELL__H__
#define __CPP___SHELL__H__

#pragma once

/*global dependencies*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstring>
/*local dependencies*/
#include "sformat.h"

class Command
{
    private:
        std::string name; // name of the command
        std::string help; // help string of the command
        std::string argsHelp;
        void (*method)(int, char const *[], char*);   // method associated with each command 
    public:

        Command(std::string, std::string, std::string, void(int, char const *[], char *));

        std::string getHelp(); 

        std::string getArgsHelp();

        std::string getName();

        void execute(int, char const *[], char*);
};

class Interpreter
{ 
    private:
        std::map<std::string, Command> commandDict; // dictionary of commands indexed by its own name (faster search results)
        std::vector<std::string> commandStack; // command buffer for an automatic feedthrough of console commands
        std::string historyFileName;
        std::string promptMessage;
        std::string argumentDelimiter;
        std::string parameterDelimiter;
        const int MAXCHAR_ARGV;
        const int MAXARGS;
        const int MAXCHAR_CMDNAME;

        void help();

        bool preProcessCommand(std::string, char*, int*, char*(*[]));

        std::string promptUser(std::string);

        void shell_exit(int, char const *[]);

        std::string exitHelp();

        void automaticCommandFeedthrough(int, char *[], char *);

        std::string acfHelp();

        void setupNewHistoryEntry();

        void updateHistory( char* );
        
    public:
        void overWriteHistoryFileName(std::string);
        
        void addCommand(    std::string, 
                            std::string, 
                            std::string, 
                            void(int, char const *[], char *) 
                        );

        void setUpPromptMessage(const std::string);

        void setUpArgumentDelimiter(const std::string);

        void setUpParameterDelimiter(const std::string);

        int run();

        // constructor
        Interpreter(); 

        // constructor with args
        Interpreter(    std::vector<std::string>, 
                        std::vector<std::string>,  
                        std::vector<std::string>, 
                        std::vector<void (*)(int, char const *[], char *)>, 
                        std::string
                    );
};

#endif // __CPP___SHELL__H__