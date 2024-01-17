#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sstream>
#include <vector>
#include <readline/readline.h>

using namespace std;

#ifndef SHELL_H
#define SHELL_H

char* get_command(string prompt);
void help();
int cd(char* path);

#endif
