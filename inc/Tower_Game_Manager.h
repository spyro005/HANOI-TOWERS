#ifndef TOWER_GAME_MANAGER_H
#define TOWER_GAME_MANAGER_H

#include "Tower_Game.h"
#include "Storage_Manager.h"


class Tower_Game_Manager{
    public:

        int number_of_disks;
        int number_of_pegs;

        Tower_Game tower_game;

        Storage_Manager storage_manager;      

        Tower_Game_Manager(int n_disks=3,int n_pegs=3);
        
        Tower_Game Create_Tower_Game_Objects();

        void Default_Setup_Tower_Game();

        bool move_disk(int disk_size,int peg_order);

        bool check_all_disks_on_peg(string peg_name);

        string get_disk_name(int number);

        string get_peg_name(int number);

        int get_total_number_of_disks();

        int get_total_number_of_pegs();


};





#endif