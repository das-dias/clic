# CLIC - Command Line Interface written in C

Version : 1.1

CLIC is a command line interface written in C that allows for the integration of its command shell with any program written in a language that is possible to be integrated with C (like C++, Rust, Python, ...) through the use of dynamic memmory.
Each added command to the shell interface should be directly linked to a user defined method with a pre-defined (by CLIC itself) interface method type ( void (\*)(int argc, char* argv[]) ).

## Dependencies:
- stdlib.h (C standard library for using memory allocation and reallocation)
- stdio.h (C standard Input/Output library)
- ctype.h (C library for testing the types of each basic variable)
- string.h (C standard library for char array and memmory manipulation)
- time.h (C library for the retrieving of the current date and time)
- uthash.h (Troy D. Hanson, Arthur O'Dwyer's C library for the use of hash-map data structures integration - https://github.com/troydhanson/uthash)
- cliccommand.h (Self-developed C lang. class data structure for saving user defined commands and their assoiated callback methods)
- consolelogger.h (Self-developped C lang. console logging system to display coloured error and warning messages).

## Interface

The use of CLIC is very straight forward, as you can see from the following code snippets.

Import the library:
```C
#import "clic.h"
```
Declare the name of the command, its help string and its method:
```C
/*declare command name*/
char* commandName = "jump";

/*declare command help string*/
char* commandHelp = "[description] : first testing function - [commands] : mark-[(char) y/n ]-> first dummy argument, lannegan-[(int) 0-3]-> second dummy argument";

/*declare command method*/
void commandMethod(int cargc, char* cargv[])
{
    printf("Number of received arguments: %d\n", cargc);
    for(int k = 0; k < cargv; k++)
        printf("Variable - Argument pair: %s\n", cargv[k]);
}
```
Initialize the CLIC shell, add the created command to its interface and launch the shell's console user interface:
```C
int main(void)
{
    /* initialize shell through ocnstructor */
    clicshell* shell = clicshell_alloc();

    /*add the command ot it*/
    clicshell_addCommand(   shell, 
                            commandName,
                            commandHelp,
                            &commandMethod /* pass command method through reference pointer */
                        );
    
    /* run the shell */
    clicshell_run(shell);

    /* after exiting the shell, destroy allocated memory :-)*/
    clicshell_free(shell);
    
    return 0;
}
```
It is also possible to change the shell's prompt message ("clic$>" pre-def), the variable delimiter (" " pre-def) and the argument delimiter ("-" pre-def) according to your needs.
```C
clicshell_overwritePromptMessage(shell, "hello-world >>");
```
## Output:
When the shell starts, the interface will look like this:
```
CLIC version 1.1
new log> Fri Mar  4 00:37:31 2022

clic$>
```
Typing the help command will show the possible commands to be interpreted by the interface:
```
clic$>help
available operations>
jump - [description] : first testing function - [commands] : mark-[(char) y/n ]-> first dummy argument, lannegan-[(int) 0-3]-> second dummy argument
acf - [description] : automatic command feedthrough - [arguments] : f-[(string) *filepath* ] text file path of commands.
exit - [description] : exit application - [commands] : ei-[(int) 0-3] application exit state parameter.
```
As you can see, you can also create a text file (*.txt*) to put your shell commands in each line, so that the shell will automatically fetch these commands from the file and run them!
```
(file.txt):

jump mark-y
exit ei-0
```