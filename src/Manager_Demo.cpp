#include "../inc/Manager_Demo.h"


Manager_Demo::Manager_Demo(int n_disks,int n_pegs){
    Tower_Game_Manager tgm = Tower_Game_Manager(n_disks,n_pegs);
    this->tower_game_manager = tgm;
}

void Manager_Demo::setup_demo(){

    

    this->tower_game_manager.Create_Tower_Game_Objects();



    this->tower_game_manager.Default_Setup_Tower_Game();
    this->tower_game_manager.tower_game.print_status();

    //tgm.tower_game.move_disk(tgm.get_disk_name(2),tgm.get_peg_name(5));


}

void Manager_Demo::play_demo(){
    //move smallest disk to 
    this->tower_game_manager.move_disk(1,this->tower_game_manager.number_of_pegs);
    this->tower_game_manager.move_disk(2,this->tower_game_manager.number_of_pegs-1);
    this->tower_game_manager.tower_game.print_status();

    this->tower_game_manager.tower_game.get_disk_names_in_order();
    this->tower_game_manager.tower_game.get_peg_names_in_order();

    cout << this->tower_game_manager.tower_game.get_smallest_disk_name() <<"\n";

}