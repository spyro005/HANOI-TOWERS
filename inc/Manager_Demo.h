#ifndef MANAGER_DEMO_H
#define MANAGER_DEMO_H

#include "Tower_Game_Manager.h"


class Manager_Demo{  
    public: 
        Tower_Game_Manager tower_game_manager;

        Manager_Demo(int n_disks=3,int n_pegs=3);
        void setup_demo();
        void play_demo();
};

#endif