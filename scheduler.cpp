#include "scheduler.h"
#include "process.h"
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

Scheduler::Scheduler() {}

Scheduler::Scheduler(vector<Process*> pro) {
    // copy vector processes into the scheduler
    for (long unsigned int i = 0; i < pro.size(); i++){
        processes.push_back(pro[i]);
    }
    processes.shrink_to_fit();
}

// use to find avg response, turnarount, wait times
void Scheduler::getData(vector<Process*> pro) {
    float res = 0, turn = 0, w = 0;
    for (long unsigned int i = 0; i < pro.size() -1; i++) {
        res += pro[i]->getResponse();
        turn += pro[i]->getTurnaround();
        w += pro[i]->getWait();
    }

    res = res/(pro.size() -1);
    turn = turn/(pro.size() -1);
    w = w/(pro.size() -1);

    // print out avg times
    printstats(res, turn, w);
}

// resets the wait of each process
void Scheduler::clearData() {
    for (long unsigned int i = 0; i < processes.size() - 1; i++){
        processes[i]->clearWait();
        processes[i]->clearWorked();
    }
}

// Round robin
// NOTE: RESPONSE TIME IS OFF BECAUSE START TIMES ARE NOT IMPLEMENTED
void Scheduler::rr() {
    // How much work needs to be done
    int left = 0;
    for (long unsigned int i = 0; i < processes.size() - 1; i++) {
        left += processes[i]->getLength();
    }

    // While work still needs to be done, go to the next process in a loop
    long unsigned int i = 0;
    while (left > 0) {
        // If a process has no work left to be done, skip it
        if (processes[i]->getLength() == processes[i]->getWorked()) {
            if (i == 3) { i = 0;}
            else {i++;}
        }
        // If a process can be done in 10 or less seconds
        else if (processes[i]->getLength() - processes[i]->getWorked() <= 10) {
            // How much still needs to be worked
            int toWork = processes[i]->getLength() - processes[i]->getWorked();
            // run it
            processes[i]->work(toWork);
            // all others +wait time
            for (long unsigned int j = 0; j < processes.size() - 1; j++) {
                if ((j != i) && (processes[j]->getWorked() != processes[j]->getLength())) {
                    processes[j]->wait(toWork);
                }
            }

            // Reduce amt left to work
            left -= toWork;
            // Go to the next processs
            if (i == 3) { i = 0;}
            else {i++;}
        } 
        // If a process has over 10 seconds of work
        else {
            // work for 10 seconds
            processes[i]->work(10);
            // make other processes wait for 10 seconds
            for (long unsigned int j = 0; j < processes.size() - 1; j++) {
                if ((j != i) && (processes[j]->getWorked() != processes[j]->getLength())) {
                    processes[j]->wait(10);
                }
            }

            // Reduce amt left to work
            left -= 10;
            // Go to the next process
            if (i == 3) { i = 0;}
            else {i++;}
        }
    }

    for (long unsigned int i = 0; i < processes.size() - 1; i++) {
        if (i == 0) {processes[i]->setStart(0);}
        else if (i == 1) {processes[i]->setStart(10);}
        else if (i == 2) {processes[i]->setStart(20);}
        else {processes[i]->setStart(30);}
    }

    cout << "\nRR:" << endl;
    getData(processes);
    clearData();
}

/* complete jobs according to arrival time
*/
void Scheduler::fifo() {
    // Run each in order
    for (unsigned long int i = 0; i < processes.size() - 1; i++) {
        // If its the first process, just run
        if (i == 0) {
            processes[i]->wait(0);
        } 
        // Otherwise, wait for the length of the previous process + how long that waited
        else {
            processes[i]->wait(processes[i-1]->getLength() + processes[i-1]->getWait());
        }
        processes[i]->setStart(processes[i]->getWait());
    }

    cout << "\nFIFO:" << endl;
    getData(processes);
    clearData();
}

/* complete jobs accordign to the shortest length first
*  NOTE: CHANGES ORDER OF PROCESSES
*/
void Scheduler::sjf() {
    // sort them smallest to largest
    for (long unsigned int i = 0; i < processes.size(); i++){
        sorted.push_back(processes[i]);
    }
    sorted.shrink_to_fit();

    Process *temp;
    for (long unsigned int i = 0; i < sorted.size() - 2; i++) {
        if (sorted[i]->getLength() > sorted[i + 1]->getLength()) {
            temp = sorted[i];
            sorted[i] = sorted[i + 1];
            sorted[i + 1] = temp;
            i = -1;
        }
    }

    // Same as FIFO
    for (unsigned long int i = 0; i < sorted.size() - 1; i++) {
        if (i == 0) {
            sorted[i]->wait(0);
        } else {
            sorted[i]->wait(sorted[i-1]->getLength() + sorted[i-1]->getWait());
        }
        sorted[i]->setStart(sorted[i]->getWait());
    }
    
    cout << "\nSJF:" << endl;
    getData(sorted);
    clearData();
}


void Scheduler::lottery() {
    int left = 0;
    for (long unsigned int i = 0; i < processes.size() - 1; i++) {
        left += processes[i]->getLength();
    }
    int totTic = left;

    // while there's work to be done
    while (left > 0) {
        // pull a random ticket
        int tic = 1 + rand() % (totTic - 1 + 1);
        // assign number of tickets according to burst length
        if (tic < processes[0]->getLength() + 1 && processes[0]->getLength() != processes[0]->getWorked()) {
            if (processes[0]->getWorked() == 0){
                processes[0]->setStart(totTic - left);
            }

            processes[0]->work(1);
            for (long unsigned int j = 0; j < processes.size() - 1; j++) {
                if ((j != 0) && (processes[j]->getWorked() != processes[j]->getLength())) {
                    processes[j]->wait(1);
                }
            }
            left -= 1;
        }

        else if (tic < processes[0]->getLength() + processes[1]->getLength() + 1 && processes[1]->getLength() != processes[1]->getWorked()) {
            if (processes[1]->getWorked() == 0){
                processes[1]->setStart(totTic - left);
            }

            processes[1]->work(1);
            for (long unsigned int j = 0; j < processes.size() - 1; j++) {
                if ((j != 1) && (processes[j]->getWorked() != processes[j]->getLength())) {
                    processes[j]->wait(1);
                }
            }
            left -= 1;
        }

        else if (tic < processes[0]->getLength() + processes[1]->getLength() + processes[2]->getLength() + 1 &&  processes[2]->getLength() != processes[2]->getWorked()) {
            if (processes[2]->getWorked() == 0){
                processes[2]->setStart(totTic - left);
            }

            processes[2]->work(1);
            for (long unsigned int j = 0; j < processes.size() - 1; j++) {
                if ((j != 2) && (processes[j]->getWorked() != processes[j]->getLength())) {
                    processes[j]->wait(1);
                }
            }
            left -= 1;
        }
        
        else if (tic < totTic + 1 && processes[3]->getLength() != processes[3]->getWorked()) {
            if (processes[3]->getWorked() == 0){
                processes[3]->setStart(totTic - left);
            }

            processes[3]->work(1);
            for (long unsigned int j = 0; j < processes.size() - 1; j++) {
                if ((j != 3) && (processes[j]->getWorked() != processes[j]->getLength())) {
                    processes[j]->wait(1);
                }
            }
            left -= 1;
        }
    }

    cout << "\nLOTTERY:" << endl;
    getData(processes);
    clearData();
}

void Scheduler::printstats(float res, float turn, float w) {
    cout << "avg turnaround time: " << turn << " ms" << endl;
    cout << "avg response time: " << res << " ms" << endl;
    cout << "avg wait time: " << w << " ms" << endl;
}