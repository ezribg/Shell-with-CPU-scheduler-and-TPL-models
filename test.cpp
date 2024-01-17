
//tokenizing is the processs of separating a string into words
// id,username,email,password,last_login --- separation = ','
//std::string command = "g++ -o main.cpp -lreadline";
//std::string separator = " ";

//in C it's common to use strtok, or strtok_r

// in C++, it's common to use a vector or getline

#include <cstring>   // for strcpy
#include <iostream>
#include <sstream>   // for stringstream
#include <string>
#include <vector>

using namespace std;

int main() {
    string input = "ls -la /tmp";

    stringstream ss(input);
    vector<const char*> tokens;
    string token;

    while(getline(ss, token, ' ')) {
        char* t = new char[token.length()];
        strcpy(t, token.c_str());
        tokens.push_back(t);
    }

    // after the loop, before printing
    tokens.push_back(NULL);
    tokens.shrink_to_fit();

    for(long unsigned int i=0; i< tokens.size(); i++)
        cout << tokens[i] << endl;

    //now we can use tokens.data with execvp()
    

    return 0;
}