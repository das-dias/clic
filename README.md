# CLIC - Command Line Interface wirtten in C

CLIC is a command line interface written in C that allows for the integration of its command shell with any program written in a language that is possible to be integrated with C (like C++, Rust, Python, ...) through the use of dynamic memmory.
Each added command to the shell interface should be directly linked to a user defined method with a pre-defined (by CLIC itself) interface method type ( void (*)(int argc, char* argv[]) ).