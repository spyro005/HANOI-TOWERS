#ifndef MOVE_H
#define MOVE_H

#include <string>
using namespace std;

class Move{
    public:

        Move(string source, string dest, string disk);

        string source_peg;
        string dest_peg;
        string disk_name;

        string move_name;

        string make_move_name(string source, string dest, string disk);

};

#endif