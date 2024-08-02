#include "../inc/Move.h"


Move::Move(string source, string dest, string disk){
    this->source_peg = source;
    this->dest_peg = dest;
    this->disk_name = disk;

    this->move_name = this->make_move_name(source,dest,disk); 
}


string Move::make_move_name(string source, string dest, string disk){
    return "Move " + disk + " from " + source + " to " + dest;
}




