#include "process.h"
using namespace std;

Process::Process() {
    arrival = 0;
}

Process::Process(int len) {
    length = len;
    arrival = 0;
    start = 0;
    waited = 0;
    worked = 0;
}

/*Process::Process(int pid, int amount, int arr) {
    arrival = arr;
    id = pid;
    length = amount;
}*/

//getters and setters

/*int Process::getPriority() {return priority;}
void Process::setPriority(int p) {priority =p;}*/
int Process::getLength() {return length;}

int Process::getStart() {return arrival;}
void Process::setStart(int s) {start =s;}

int Process::getWait() {return waited;}
void Process::wait(int amount) {waited += amount;}

void Process::clearWait() {waited = 0;}
void Process::clearWorked() {worked = 0;}

int Process::getWorked() {return worked;}
void Process::work(int amount) { worked += amount;}

// Calculate turnaround/remaining time

int Process::getResponse() {return start - arrival;}

int Process::getTurnaround() {return length + waited;}

int Process::getRemaining() {return length - worked;}
