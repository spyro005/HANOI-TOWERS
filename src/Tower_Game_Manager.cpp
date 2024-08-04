#include "../inc/Tower_Game_Manager.h"



Tower_Game_Manager::Tower_Game_Manager(int n_disks,int n_pegs){
    if(n_disks < 1){
        if(stoi(getenv("DEBUG")) >= 1){
            cout << "Entered " << to_string(n_disks) << " .Expects at least 1. Making it 1. \n";
        }
        n_disks = 1;
    }
    if(n_disks > 30){
        if(stoi(getenv("DEBUG")) >= 1){
            cout << "Entered " << to_string(n_disks) << " .Expects at most 30. Making it 30. \n";
        }
        n_disks = 30;
    }
    if(n_pegs < 3){
        if(stoi(getenv("DEBUG")) >= 1){
            cout << "Entered " << to_string(n_pegs) << " .Expects at least 3. Making it 3. \n";
        }
        n_pegs =3;
    }
    if(n_pegs > 30){
        if(stoi(getenv("DEBUG")) >= 1){
            cout << "Entered " << to_string(n_pegs) << " .Expects at most 30. Making it 30. \n";
        }
        n_pegs =30;
    }
    this->number_of_disks = n_disks;
    this->number_of_pegs = n_pegs;

    Tower_Game tg = Tower_Game();
    
    Storage_Manager sm = Storage_Manager();
    this->storage_manager = sm;

    tg.storage_manager_ptr = &(this->storage_manager);
    this->tower_game = tg;
}     

Tower_Game Tower_Game_Manager::Create_Tower_Game_Objects(){

    if(stoi(getenv("DEBUG")) >= 1){
        cout << "\n CREATING TOWER GAME OBJECTS: " << this->get_total_number_of_disks() << " Disks and " 
        <<  this->number_of_pegs <<" (number of) pegs  \n\n";  
    }

    for(int a=1;a <= this->number_of_pegs;a++ ){
        this->storage_manager.add_peg_object(Peg(this->get_peg_name(a),a));
    }

    for(int c=1;c <= this->get_total_number_of_disks();c++ ){
        this->storage_manager.add_disk_object(Disk(this->get_disk_name(c),c));
    }

    if(stoi(getenv("DEBUG")) >= 1){
        cout << " FINISHED GAME OBJECTS CREATION \n";
    }

    return this->tower_game;

}

void Tower_Game_Manager::Default_Setup_Tower_Game(){
    if(stoi(getenv("DEBUG")) >= 1){
        cout << "\n SETTING UP HANOI TOWERS GAME WITH " << this->get_total_number_of_disks() << " Disks and " 
        <<  this->number_of_pegs <<" pegs  \n\n";
    }


    for(int i=1; i <= this->number_of_pegs;i++){
        this->tower_game.add_peg_pointer(this->storage_manager.get_peg_ptr(i));
    }

    for(int j=1; j <= this->get_total_number_of_disks();j++){
        this->tower_game.add_disk_pointer(this->storage_manager.get_disk_ptr(j));
    }


    int old_debug = stoi(getenv("DEBUG"));
    char* old_debug_s = to_string(old_debug).data();


    // print disk addition to pegs by changing debug temporarily
    const char* debug_value = "3";
    if (setenv("DEBUG",debug_value,1) == 0){
        std::cout << "DEBUG SET TO " << debug_value << " TEMPORARILY\n";
    }else{
        std::cerr << " DID NOT SET DEBUG VARIABLE SUCCESFULLY. EXITING.." << std::endl;
    }

    for(int k=this->get_total_number_of_disks(); k >= 1 ;k--){
        (this->storage_manager.get_peg_ptr(1))->add_disk_by_ptr(this->storage_manager.get_disk_ptr(k));
    }

    if (setenv("DEBUG",old_debug_s,1) == 0){
        std::cout << "RESETTING DEBUG TO " <<old_debug_s << "\n";
    }else{
        std::cerr << " DID NOT RESET DEBUG VARIABLE SUCCESFULLY. EXITING.." << std::endl;
    }

    if(stoi(getenv("DEBUG")) >= 1){
        cout << " FINISHED GAME CREATION \n";
    }

}


bool Tower_Game_Manager::move_disk(int disk_size, int peg_order){
    return this->tower_game.move_disk(this->get_disk_name(disk_size),this->get_peg_name(peg_order));
}

bool Tower_Game_Manager::check_all_disks_on_peg(string peg_name){
    bool valid_peg_name = this->tower_game.check_valid_peg_name(peg_name);
    if(!valid_peg_name){
        return false;
    }

    Peg* peg_ptr = this->tower_game.get_peg_by_name(peg_name);
    vector<string> disk_names = peg_ptr->get_disk_names_in_order();

    if(disk_names.size() == this->get_total_number_of_disks()){
        if(stoi(getenv("DEBUG")) >= 2){
            cout << "PEG has " << disk_names.size() << " disks. Total number of \
            disks are " << this->get_total_number_of_disks() << "\n";
        }
        
        return true;
    }else{
        
        return false;
    }

}

string Tower_Game_Manager::get_disk_name(int number){
    char disk_name[10];
    snprintf(disk_name,sizeof(disk_name), "Disk %d",number);
    std::string result(disk_name);
    return result;
}

string Tower_Game_Manager::get_peg_name(int number){
    char peg_name[10] ;
    snprintf(peg_name,sizeof(peg_name), "Peg %d",number);
    std::string result(peg_name);
    return result;
}

int Tower_Game_Manager::get_total_number_of_disks(){
    return this->number_of_disks;
}

int Tower_Game_Manager::get_total_number_of_pegs(){
    return this->number_of_pegs;
}




