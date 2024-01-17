#include <iostream>

#ifndef PROC
#define PROC

class Process {
    private:
        //int id;
        //int priority; // lower numbers to be higher priority
        int length; // total length of the job 

        int arrival; // when process arrives
        int start; // when the process begins
        int waited; // how long this process waited for other processes;

        int worked; // how much is already done

    public:
        Process();
        Process(int length);
        //Process(int pid, int amount, int arr);

        //int getPriority();
        //void setPriority(int p);
        int getLength();

        int getStart();
        void setStart(int s);
        int getWait();
        void wait(int amount);

        void clearWait();
        void clearWorked();

        int getWorked();
        void work(int amount);

        int getResponse();
        int getRemaining(); // remaining amount to be worked
        int getTurnaround(); // amount of time from arrival to completion

};

#endif