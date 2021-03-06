/*
* *****************************************************************************
* *[author] Diogo André (git-hub : das-dias)
* *[date] 24-02-2022
* *[filename] cliccommand.h
* *[summary] Console Line Interpreter written in C (CLIC) is a command line interpreter library
                fully written in C, allowing for the fast and easy integration of the library in other
                console applications, and with another languages such as Rust-lang.
                Command Class implementation file.
MIT License

Copyright (c) 2022 Diogo André Silvares Dias

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
* *****************************************************************************
*/
#include "cliccommand.h"
/**
* [name] cliccommand_alloc
* *[description] cliccommand constructor
* ?[input]
* @par name (char*) : name of the command
* @par help (char*) : help string descriptor of the command and its arguments
* @par method (void (*)(int, char*[])) : command's associated method to be executed
* ![output]
* @par self (cliccommand*) : pointer to cliccommand object being constructed
*/
cliccommand* cliccommand_alloc(char* name, char* help, void (*method)(int, char**))
{
    cliccommand* self = (cliccommand*) malloc(sizeof *self);
    self->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(self->name, name);
    self->help = (char*)malloc(sizeof(char)*(strlen(help)+1));
    strcpy(self->help, help);
    self->method = method;
    return self;
}

/**
* [name] cliccommand_free
* *[description] cliccommand destructor
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object being destructed
* ![output]
* @par success (int) : integer reveiling the success of destruction of the object
*/
int cliccommand_free(cliccommand* self)
{
    if(self){
        free(self);
        return RETURN_SUCCESS;
    }
    return RETURN_FAILURE;
}
/**
* [name] cliccommand_getName
* *[description] get the name descriptor of a command
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object
* ![output]
* @par name (char*) : name field of the command object
*/
char * cliccommand_getName(cliccommand* self)
{
    return self->name;
}

/**
* [name] cliccommand_getHelp
* *[description] get the help descriptor of a command
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object
* ![output]
* @par help (char*) : help field of the command object
*/
char * cliccommand_getHelp(cliccommand* self)
{
    return self->help;
}

/**
* [name] cliccommand_execute
* *[description] execute the method associated to the command
* ?[input]
* @par self (cliccommand*) : pointer to cliccommand object
* @par argc (int)
* @par argv (char*[])
* ![output]
* @par none (void) : 
*/
void cliccommand_execute(cliccommand* self, int argc, char** argv)
{
    self->method(argc, argv);
}
