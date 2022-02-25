#include "sformat.h"


// todo : Change this function so that it is supported in C89 code
// (re-write in pure C89 code)
char * sformat(char* charBuffer, ...)
{   
    std::string buffer(charBuffer);
    std::string returningString = "";
    std::string argumentIdentifier = "{}";
    size_t count  = 0; // counter to the number of variables inside the buffer string
    // count the number of variables inside the string
    size_t pos = 0;
    size_t prevPos = pos;
    while( ( pos = buffer.find(argumentIdentifier, pos) ) != std::string::npos )
    {
        ++ count; // increment the counter
        prevPos = pos;
        pos += argumentIdentifier.length();
    }
    if (count == 0) throw "No arguments parsed through \"{}\" marker.";
    //then, build the returning string
    std::va_list args;
    int argIndex;
    try{
        va_start(args, charBuffer);
    } catch ( const char * ex1 ) {
        throw ex1;
    }
    try{
        pos = 0;
        prevPos = pos;
        while ( ( pos = buffer.find(argumentIdentifier, pos) ) != std::string::npos )
        {
            returningString += buffer.substr(prevPos,pos);
            returningString += std::string(va_arg(args, const char*));
            pos += argumentIdentifier.length();
            prevPos = pos;
        }
        returningString += buffer.substr(prevPos,pos); // add the last bit of string after the last variable
    } catch (const char * ex2) {
        throw ex2;
    }
    va_end(args);
    return returningString.c_str();
}