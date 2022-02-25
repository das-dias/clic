#include "clic.h"

void interfaceFunc1(int argc, char const * argv[], char * outputHistory);

void interfaceFunc2(int argc, char const * argv[], char * outputHistory);

void interfaceFunc3(int argc, char const * argv[], char * outputHistory);

char** commandNames = {
    "int1",
    "int2",
    "int3"
};
char** commandHelps = {
    "[description] : first testing function - [commands] : mark--[(char) y/n ]-> first dummy argument, lannegan--[(int) 0-3]-> second dummy argument",
    "[description] : second testing function - [commands] : curt--[(char) y/n ]-> first dummy argument, cobain--[(string) ...]-> second dummy argument",
    "[description] : third testing function - [commands] : chino--[(char) y/n ]-> first dummy argument, moreno--[(int) 0-3]-> second dummy argument"
};

typedef void (*function_array)(int, char const *[], char *); /* define a function array */

function_array commandMethods[3] = {
    &interfaceFunc1,
    &interfaceFunc2,
    &interfaceFunc3
};

int main(int argc, char *argv[])
{
    printf("CLIC SAYS : Hello, World!\n");
    char* historyFilename = "./clic_hist.txt";
    // setup the shell

    //add the new command to the interpreter
    //myInterpreter.addCommand(name3, help3, argsHelp3, &interfaceFunc3);
    //run the shell
    //myInterpreter.run();
    return EXIT_SUCCESS;
}

void interfaceFunc1(int argc, char const * argv[], char * outputHistory){
    for (int i = 0; i < argc; i++) {
        printf( "%s\n", argv[i]);
    }
    outputHistory = strcpy(outputHistory,"Func 1 says : everything is cool for now! :-)");
}

void interfaceFunc2(int argc, char const * argv[], char * outputHistory){
    for (int i = 0; i < argc; i++) {
        printf( "%s\n", argv[i]);
    }
    outputHistory = strcpy(outputHistory,"Func 2 says : everything is cool for now! :-)");
}

void interfaceFunc3(int argc, char const * argv[], char * outputHistory){
    for (int i = 0; i < argc; i++) {
        printf( "%s\n", argv[i]);
    }
    outputHistory = strcpy(outputHistory, "Func 3 says : everything is cool for now! :-)");
}