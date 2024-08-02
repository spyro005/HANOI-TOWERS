#ifndef TOWER_GAME_H
#define TOWER_GAME_H


#include "Peg.h"
#include "Storage_Manager.h"


class Tower_Game{
    public: 
        list<Disk*> disk_object_list;
        list<Peg*> peg_object_list ;

        Storage_Manager* storage_manager_ptr;

        Tower_Game();

        Disk* get_disk_by_name(string disk_name);

        Peg* get_peg_by_name(string peg_name);

        vector<string> get_disk_names_in_order(bool ascending = true);

        list<Peg*> get_peg_objects_in_order(bool ascending=true);

        vector<string> get_peg_names_in_order(bool ascending = true);

        string get_smallest_disk_name();

        void sort_disk_list_by_size(bool ascending=true);

        void sort_peg_list_by_order(bool ascending=true);

        bool add_disk_pointer(Disk* new_disk);

        bool add_disk_object(Disk new_disk);

        bool add_peg_pointer(Peg* new_peg);

        bool add_peg_object(Peg new_peg);

        bool move_disk(string disk_name, string target_peg_name);

        bool move_disk_b_pegs(string source_peg, string dest_peg);

        bool check_valid_peg_name(string peg_name);

        string get_top_disk_of_peg(string peg_name);

        bool check_disks_w_pegs(bool update_written_peg = true);

        void print_status();

        void draw_status();

        void draw_line_status();

};

#endif