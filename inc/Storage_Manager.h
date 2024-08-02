#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include "Peg.h"
#include "Disk.h"

class Storage_Manager{
    public: 
        vector<Peg> Peg_objects;
        vector<Disk> Disk_objects;

        Storage_Manager();

        bool add_disk_object(Disk new_disk);
        bool add_peg_object(Peg new_peg);

        Peg get_peg_object(int peg_index);
        Peg* get_peg_ptr(int peg_index);
        Disk get_disk_object(int disk_index);
        Disk* get_disk_ptr(int disk_index);

        

};


#endif