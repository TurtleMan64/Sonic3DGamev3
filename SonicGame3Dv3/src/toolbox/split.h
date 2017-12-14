#ifndef SPLIT_H
#define SPLIT_H

/* Parse a line and return an array of the
individual tokens. Original line is modified. */
char** split(char* line, char delim, int* length);

#endif