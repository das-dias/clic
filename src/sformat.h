#ifndef __CPP__SFORMAT__H__
#define __CPP__SFORMAT__H__

#pragma once

#include <sstream>
#include <string>
#include <cstdarg>
/*
[name] sformat
[summary] Formats const char * variables into places marked by "{}" inside the string received in charBuffer, returning the formatted string.
[input] charBuffer          (type) : char*          (summary) : string to be formatted
        ...                 (type) : const char *   (summary) : strings to format into the variables of charBuffer

[output] returningString    (type) : const char *   (summary) : strings to be formatted into char Buffer 
*/
const char * sformat(char*, ...);

#endif // ___SFORMAT__H__