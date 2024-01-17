#include "process.h"
#include <vector>
#include <iostream>
using namespace std;

#ifndef SCHED
#define SCHED

// get/set the policy to run
// get process parameters
// implement the scheduling policies, FIFO, SJF, RR, and Lottery
// print or return some statss on the run(s)

class Scheduler {

    public:
        vector<Process*> processes; // list of 4 lengths
        vector<Process*> sorted;

        Scheduler();
        Scheduler(vector<Process*> pro);

        void getData(vector<Process*> pro);
        void clearData();

        void rr();
        void fifo();
        void sjf();
        void lottery();
        void printstats(float res, float turn, float w);

};
#endif