#include "../inc/Disk.h"

#include <cstdlib>


Disk::Disk(string name, int order, string current_peg ){
            this->name = name;
            this->order = order;
            this->current_peg = current_peg;
            if(stoi(getenv("DEBUG")) >= 1){
                cout << "Created disk named " << name << " with size " << order << " on peg " << this->current_peg << "\n";
            }
        }

void Disk::update_peg(string new_peg){
            string cpeg = this->current_peg;
            this->current_peg = new_peg;
            if(stoi(getenv("DEBUG")) >= 3){
                cout << "Updated current peg of disk from '" << cpeg << "' to " << new_peg << "\n";
            }
        }
