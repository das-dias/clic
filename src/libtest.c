#include "clic.h"

void interfaceFunc1(int argc, char* argv[]);

void interfaceFunc2(int argc, char* argv[]);

void interfaceFunc3(int argc, char* argv[]);

char* commandNames[3] = {
    "int1",
    "int2",
    "int3"
};
char* commandHelps[3] = {
    "[description] : first testing function - [commands] : mark--[(char) y/n ]-> first dummy argument, lannegan--[(int) 0-3]-> second dummy argument",
    "[description] : second testing function - [commands] : curt--[(char) y/n ]-> first dummy argument, cobain--[(string) ...]-> second dummy argument",
    "[description] : third testing function - [commands] : chino--[(char) y/n ]-> first dummy argument, moreno--[(int) 0-3]-> second dummy argument"
};

typedef void (*function_array)(int, char *[]); /* define a function array */

function_array commandMethods[3] = {
    &interfaceFunc1,
    &interfaceFunc2,
    &interfaceFunc3
};

int main(void)
{
    printf("CLIC SAYS : Hello, World!\n");

    /* clic shell constructor */
    clicshell* shell = clicshell_alloc();

    /* get the number of commands*/
    int size = sizeof(commandNames) / sizeof(*commandNames);

    /* setup the possible clic shell commands */
    for(int i=0; i<size; i++)
        clicshell_addCommand(   shell, 
                                commandNames[i],
                                commandHelps[i],
                                commandMethods[i]
                            );
    clicshell_run(shell);
    
    return 0;
}

void interfaceFunc1(int argc, char * argv[]){
    for (int i = 0; i < argc; i++) {
        printf( "%s\n", argv[i]);
    }
    printf("Func 1 says : everything is cool for now! :-)");
}

void interfaceFunc2(int argc, char * argv[]){
    for (int i = 0; i < argc; i++) {
        printf( "%s\n", argv[i]);
    }
    printf("Func 2 says : everything is cool for now! :-)");
}

void interfaceFunc3(int argc, char * argv[]){
    for (int i = 0; i < argc; i++) {
        printf( "%s\n", argv[i]);
    }
    printf("Func 3 says : everything is cool for now! :-)");
}