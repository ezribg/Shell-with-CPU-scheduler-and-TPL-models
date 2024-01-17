#include "shell.h"

char* get_command(string prompt) {
    char* command = (char*)"";

    while(strcmp(command, "") == 0) {
        command = readline(prompt.c_str());
    }
    return command;
}

/* display short help message
 * built in functions
 * author names
 */
void help() {
    cout << "\nAUTHORS" << endl;
    cout << "- Abi Sipes\n- Ezri Braid-Grizzell\n" << endl;
    cout << "DESCRIPTION" << endl;
    cout << "- This is a working shell that can run both prebuilt commands and preexisting "
    << "commands such as nano, pwd, etc. The user can also run their own program through this shell.\n" << endl;
    cout << "COMMON COMMANDS" << endl;
    cout << "- exit / quit: terminates shell\n- set: set <input> changes shell prompt to the given input\n"
    << "- echo: echo <input> prints out the given input\n"
    << "- cd: cd <path> changes directory to the given path and displays whether it was successful or not\n" << endl;

}

/* actually change directory
 * so it also needs to read from the new directory
 */
int cd(char* path){
    if (chdir(path) == 0) {
        chdir(path);
        cout << "cd " << path << " successful" << endl;
        return 0;
    } else {
        cout << "cd " << path << " failed: " << strerror(errno) << endl;
        return 1;
    }
}
