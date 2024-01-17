
// Authors: Ezri Braid-Grizzell and Abi Sipes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "shell.h"
#include "scheduler.h"

int main (int argc, char *argv[]) {

    srand(time(0));

    string prompt = "$ ";
    char* command;

    while (1) {
        command = get_command(prompt);

        //tokenize command
        stringstream ss(command);
        vector<char*> data;
        string token;

        while(getline(ss, token, ' ')) {
            char* t = new char[token.length()];
            strcpy(t, token.c_str());
            data.push_back(t);
        }

        data.push_back(NULL);
        data.shrink_to_fit();

        // system calls
        if (strcmp("help", data[0]) == 0) {help();}
        else if(strcmp("quit", data[0]) == 0 ||
            strcmp("exit", data[0]) == 0) {exit(0);}
        else if(strcmp("set", data[0]) == 0) {
            string p = string(data[1]) + "$ ";
            prompt = p;
        } 
        else if(strcmp("echo", data[0]) == 0) {
            for(long unsigned int i = 1; i < data.size() - 1; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
        else if (strcmp("cd", data[0]) == 0) {cd(data[1]);}
        else if (strcmp("sched", data[0]) == 0) {
            // four every time
            vector<int> burst = {48, 12, 16, 60};
            cout << "Runs on a premade list of burst lenghts: {48, 12, 16, 60}" << endl;
            cout << "These can be changed through hard coding" << endl;

            // create a vector of process lengths
            vector<Process*> pros;

            for (int i = 0; i < 4; i++) {
                Process *p = new Process(burst[i]);
                pros.push_back(p);
            }
            pros.push_back(NULL);
            pros.shrink_to_fit();

            // pass it to schedulers and print all of them out
            Scheduler *sched = new Scheduler(pros);
            //ISSUE - if a process is run before fifo, the data from fifo is printed for the other functions data
            sched->fifo();
            sched->sjf();
            sched->rr();
            sched->lottery();
        }
        else {
            //run the command .. it's a rpogram: fork(), execvp(), and wait()
            pid_t pid = fork();
            if (pid < 0) {    
                //error occurred 
                fprintf(stderr, "fork() failed\n");
                return 1;
            }

            else if (pid == 0) {     
                //child process
                //use vp takes parameter and then an array of parameter
                execvp (data[0], data.data());
            }

            else {
                // parent process
                pid = wait(NULL);
            }
        }
    }

    return EXIT_SUCCESS;
}