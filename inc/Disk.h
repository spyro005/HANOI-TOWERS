#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <list>
#include <tuple>
#include <string>


using namespace std;



class Disk{
    public:
        string name = "";
        int order = -1;
        string current_peg = "";

        Disk(string name, int order, string current_peg ="");

        void update_peg(string new_peg);

        string get_current_peg(){
            return this->current_peg;
        }
};

#endif