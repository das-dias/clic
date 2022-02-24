/** **********************************
* *[author] Diogo André (git-hub : das-dias)
* *[date] 24-02-2022
* *[filename] clic.h
* *[summary] Console Line Interpreter written in C (CLIC) is a command line interpreter library
                fully written in C, allowing for the fast and easy integration of the library in other
                console applications, and with another languages such as Rust-lang.
 ***********************************
*/
#ifndef CLIC_H_
#define CLIC_H_

#include <stdlib.h> /* for using malloc/realloc/free */
#include <string.h> /* for using memcpy/memmove */

/**
 * * in case C library malloc() needs extra protection,
 * * allow these defines to be overridden.
 */
#ifndef cliccommand_clib_free
#define cliccommand_clib_free free
#endif
#ifndef cliccommand_clib_malloc
#define cliccommand_clib_malloc malloc
#endif
#ifndef cliccommand_clib_calloc
#define cliccommand_clib_calloc calloc
#endif
#ifndef cliccommand_clib_realloc
#define cliccommand_clib_realloc realloc
#endif

#ifndef clicshell_clib_free
#define clicshell_clib_free free
#endif
#ifndef clicshell_clib_malloc
#define clicshell_clib_malloc malloc
#endif
#ifndef clicshell_clib_calloc
#define clicshell_clib_calloc calloc
#endif
#ifndef clicshell_clib_realloc
#define clicshell_clib_realloc realloc
#endif

/**
* *[name] CLICCommand
* *[description] Command unit structure of the CLIC interface
* ?[variables]
* @par name ( char* ) : Name of the command used to call it;
* @par help ( char* ) : Help string stating the description of the command and its variables/arguments
* @par method ( void (*)(int, char*[], char*) ) : Associated method to the command;
*/
typedef struct CLICCommand {
    char* name; // name of the command
    char* help; // help string of the command
    void (*method)(int, char*[], char*); // associated method of the command
} CLICCommand;

/**
* [name] _CLICCommand 
* *[description] CLICCommand constructor
* ?[input]
* @par <param name> (type) : <first input description>
* ![output]
* @par <param name> (type) : <first output description>
*/
#define _CLICCommand(name, help, method)\
    do{                                 \
        CLICCommand self;               \        
        self.name = name;               \       
        self.help = help;               \
        self.method = method;           \       
    } while(0)                          \
    (self)
                   

#endif /* CLIC_H_ */