#include "../inc/Tower_Game.h"

#include <cstdlib>


using namespace std;

Tower_Game::Tower_Game(){
    this->disk_object_list = list<Disk*>() ;
    this->peg_object_list = list<Peg*>();
}

Disk* Tower_Game::get_disk_by_name(string disk_name){
    for(Disk* disk: this->disk_object_list){
        if (disk->name == disk_name){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "Found and returning disk named  " << disk_name << "\n";
            }
            return disk;
        }
    }
    if(stoi(getenv("DEBUG")) >= 2){
        std::cout << "Did not find disk named in the game" << disk_name ;
    }
    return nullptr;
}

Peg* Tower_Game::get_peg_by_name(string peg_name){
    for(Peg* peg: this->peg_object_list){
        if (peg->name == peg_name){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "Found and returning peg named  " << peg_name << "\n";
            }
            return peg;
        }
    }
    std::cout << "Did not find peg named in the game" << peg_name ;
    return nullptr;
}

bool Tower_Game::add_disk_pointer(Disk* new_disk){
    if (new_disk == nullptr){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Given disk is null, we cannot add it" << " \n";
        }
        return false;
    }
    if (new_disk->name == "" || new_disk->order == -1){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Current disk has not-initialized values (name or order) so we cannot add " << " \n";
        }
        return false;
    }

    // make sure disk has unique name and size
    for(Disk* disk: this->disk_object_list){
        if (disk->name == new_disk->name){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "New disk has same name as other disk named '" << disk->name << "' with order " << disk->order <<" - Cannot add \n";
            }
            return false;
        }

        if (disk->order == new_disk->order){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "New disk has same order as other disk named '" << disk->name << "' , with order " << disk->order <<" - Cannot add \n";
            }
            return false;
        }
    }

    this->disk_object_list.push_back(new_disk);
    if(stoi(getenv("DEBUG")) >= 1){
        std::cout << "Added disk " << new_disk->name  << " to game " << "\n";
    }
    return true;
}

bool Tower_Game::add_disk_object(Disk new_disk){
    return this->add_disk_pointer(&new_disk);
}

bool Tower_Game::add_peg_pointer(Peg* new_peg){
    if (new_peg == nullptr){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Given peg is null, we cannot add it" << " \n";
        }
        return false;
    }
    if (new_peg->name == "" || new_peg->order == -1){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Current disk has not-initialized values (name or order) so we cannot add " << " \n";
        }
        return false;
    }

    // make sure peg has unique name and order
    for(Peg* peg: this->peg_object_list){
        if (peg->name == new_peg->name){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "New peg has same name as other peg named '" << peg->name << "' with order " << peg->order <<" -  we cannot add it \n";
            }
            return false;
        }

        if (peg->order == new_peg->order){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "New peg has same order as other peg named '" << peg->name << "' , with order " << peg->order <<" - we cannot add it \n";
            }
            return false;
        }
    }

    this->peg_object_list.push_back(new_peg);
    if(stoi(getenv("DEBUG")) >= 1){
        std::cout << "Added peg named '" << new_peg->name << "' to game " << "\n";
    }
    return true;
}

bool Tower_Game::add_peg_object(Peg new_peg){
    return this->add_peg_pointer(&new_peg);
}


bool Tower_Game::move_disk(string disk_name, string target_peg_name){
    Peg* target_peg = nullptr;
    Peg* disk_peg = nullptr;
    string top_disk_name = "";
    int top_disk_order = -1;

    if(stoi(getenv("DEBUG")) >= 2){
        std::cout << "Attempting to move disk named " << disk_name << 
            " to peg named '" << target_peg_name << "'\n ";
    }

    //finding target peg object
    for(Peg* peg: this->peg_object_list ){
        if(peg->name == target_peg_name){
            target_peg = peg;
        }
    }

    if(target_peg == nullptr){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Could not find peg object for peg named " << target_peg_name << " \n";
        }
        return false;
    }

    for(Peg* peg: this->peg_object_list ){
        if (peg->disk_names_list.size() == 0){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "Peg named " << peg->name << " has no disks. Continuing with next... " << "\n";
            }
            continue;
        }else{
            top_disk_name = peg->read_top_disk();
            if (top_disk_name == disk_name){
                //top_disk_name = peg->read_top_disk();
                top_disk_order = stoi(peg->read_top_disk(true));
                disk_peg = peg;
                break;
            } 
        }
    }


    if(disk_peg == nullptr){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Could not find peg object that has disk named " << disk_name << " at its top \n";
        }
        return false;
    }

    if(top_disk_name == "" || top_disk_order == -1){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Could not get top disk name and order for this disk" << "\n";
        }
        return false;
    }

    // attempt move
    bool removed = false;
    bool added = target_peg->add_disk_by_name(top_disk_name, top_disk_order);
    if (added){
        // remove from previous peg
        removed = disk_peg->remove_top_disk();
        // if not removed succesfully, remove the added disk
        if(! removed){
            if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "Disk not removed succesfully from previous peg, removing from \
            peg where recently added" << "\n";
            }
            bool removed2 = target_peg -> remove_top_disk();
            if(stoi(getenv("DEBUG")) >= 2){
            std::string success = removed2 ? "successfully":"unsuccesfully";
            std::cout << "Disk was removed " << success  << " from peg where it was recently added" << " \n";
            }
        }
    }
    if(added&&removed){
        this->get_disk_by_name(disk_name)->current_peg = target_peg_name;
    }

    return added && removed;

}

bool Tower_Game::move_disk_b_pegs(string source_peg, string dest_peg){
    string top_disk = this->get_top_disk_of_peg(source_peg);
    if(top_disk == ""){
        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "PEG HAS NO TOP DISK\n";
        }
        return false;
    }
    return this->move_disk(top_disk,dest_peg);

}

string Tower_Game::get_top_disk_of_peg(string peg_name){
    Peg* s_peg = this->get_peg_by_name(peg_name);
    if(s_peg == nullptr){
        return "";
    }
    string top_disk = s_peg->read_top_disk();
    return top_disk;
}

void Tower_Game::sort_disk_list_by_size(bool ascending){
    this->disk_object_list.sort([ascending](const Disk* disk1, const Disk* disk2){
        bool result = (ascending)? (disk1->order < disk2->order): (disk1->order > disk2->order);
        return result;
    }); 
}

void Tower_Game::sort_peg_list_by_order(bool ascending){
    this->peg_object_list.sort([ascending](const Peg* peg1, const Peg* peg2){
        bool result = (ascending)? (peg1->order < peg2->order): (peg1->order > peg2->order); 
        return result;
    }); 
}

vector<string> Tower_Game::get_disk_names_in_order(bool ascending){
    this->sort_disk_list_by_size(ascending);
    vector<string> disk_names = vector<string>();
    //string order = ascending ? "ASCENDING":"DESCENDING";
    //std::cout << "PRINTING DISK NAMES IN ORDER " <<  order << " \n" ;
    for(Disk* disk:this->disk_object_list ){
        disk_names.push_back(disk->name);
        //std::cout << disk->name << "\n";
    }
    //std::cout << "END PRINT\n";

    return disk_names;
}

list<Peg*> Tower_Game::get_peg_objects_in_order(bool ascending){
    this->peg_object_list.sort([ascending](const Peg* peg1,const Peg* peg2){
        bool result = ascending? peg1->order < peg2->order : peg1->order > peg2->order ;
        return result;
    });

    return this->peg_object_list;
}

vector<string> Tower_Game::get_peg_names_in_order(bool ascending){
    this->sort_peg_list_by_order(ascending);
    vector<string> peg_names = vector<string>();
    //string order = ascending ? "ASCENDING":"DESCENDING";
    //std::cout << "PRINTING PEG NAMES IN ORDER " <<  order << " \n" ;
    for(Peg* peg:this->peg_object_list ){
        peg_names.push_back(peg->name);
        //std::cout << peg->name << "\n";
    }
    //std::cout << "END PRINT \n";

    return peg_names;
}

string Tower_Game::get_smallest_disk_name(){
    this->sort_disk_list_by_size();
    return this->disk_object_list.front()->name;
}

bool Tower_Game::check_valid_peg_name(string peg_name){
    vector<string> peg_names = this->get_peg_names_in_order();
    for(string name:peg_names){
        if(name == peg_name){
            return true;
        }
    }
    if(stoi(getenv("DEBUG")) >= 2){
        std::cout << "INVALID PEG NAME: " << peg_name << "\n";
    }
    return false;
}


void Tower_Game::print_status(){
    std::cout << "\n\n GAME PEG STATUS \n";
    for(Peg* peg: this->peg_object_list ){
        string cur_peg_name = peg->name;
        std::cout << "\n Status for peg named " << cur_peg_name << " with order "<< peg->order << "\n";
        if (peg->disk_names_list.size() == 0){
            std::cout << "Peg has no disks ... continuing to next peg ... " << "\n";
            continue;
        }
        std::cout << " Peg has the following disks: " << " \n";

        list<tuple<string,int>> disks_ordered = peg->return_disks_copy_ordered();
        // check disks for each peg peg->disk_names_list
        for(tuple<string,int> t : disks_ordered ){
            string disk_name = get<0>(t);
            int order = get<1>(t);
            std::cout << "Disk named '" << disk_name << "' with size (order) " << order << "\n";
            
        }
    }

    std::cout << "No other pegs in game \n";

}

string copy_n_times(int n, const string& input){
    if(n < 0) n =0;
    string repeated;
    repeated.reserve(input.size()*n);
    for(int i=0; i < n;i++){
        repeated += input;
    }

    return repeated;
}

void Tower_Game::draw_status(){
    if(stoi(getenv("DEBUG")) >=2 ){
        std::cout << "\n\n DRAWING GAME STATUS \n";
    }else{
        std::cout <<"\n";
    }
    //int total_pegs = this->peg_object_list.size();
    int total_disks = this->disk_object_list.size();
    int peg_length = (total_disks + 1) > 11 ? (total_disks + 1) : 11;
    string space = " ";
    string line = "_";
    string peg_seg = "&";


    for(int j=total_disks*3;j >= -2;j--){

        for(Peg* peg: this->get_peg_objects_in_order()){

            vector<tuple<string,int>> vector_ordered = peg->convert_disk_list_to_vector(false);
            int disks_on_peg = vector_ordered.size();
                if (j > 3*disks_on_peg){
                    std::cout << copy_n_times(peg_length,space)  << " ";
                }
                if(j <= 3*disks_on_peg && j >=1){
                    int o=0;
                    if(j/3 < vector_ordered.size()) {
                        o=j/3;
                    }else{
                        o=0;
                    }
                    tuple<string,int> t = vector_ordered[o];
                    int disk_order = get<1>(t);

                    string disk_name_start = "| DISK ";
                    string left = (j%3 == 1)? (copy_n_times(peg_length,"^")):(j%3 == 2?(disk_name_start):(copy_n_times(peg_length,line)));
                    int center_int = peg_length-disk_name_start.length()-to_string(disk_order).length()-1;
                    int center_int_n = center_int >0?center_int:0;
                    string center = (j%3 == 2)? (to_string(disk_order) + copy_n_times(center_int_n ,space)):"";
                    string right = (j%3 == 1)? (""):(j%3 == 2?("|"):(""));
                    std::cout << left  << center << right << " ";
                }
                if(j <=0 ){
                    if(j == 0){
                        std::cout << copy_n_times(peg_length, "~") + space ;
                    }else if(j == -1){
                        int n = peg_length-6-(to_string(peg->order).length())-2;
                        int n_c = n>0?n:0;
                        std::cout << "$ PEG " + to_string(peg->order) + copy_n_times(n_c,space) + " $ " ;
                    }else if (j == -2){
                        std::cout << copy_n_times(peg_length, "~") + space ;
                    }
                }

        }
        std::cout<<"\n";
    }

}


void Tower_Game::draw_line_status(){

    if(stoi(getenv("DEBUG")) >=2 ){
        std::cout << "\n\n DRAWING LINE GAME STATUS \n";
    }else{
        std::cout <<"\n";
    }

    int total_disks = this->disk_object_list.size();
    int peg_length = (total_disks + 4) > 14 ? (total_disks + 4) : 14;
    string space = " ";
    string line = "_";
    string peg_seg = "&";


    for(int j=total_disks;j >= -1;j--){

        for(Peg* peg: this->get_peg_objects_in_order()){

            vector<tuple<string,int>> vector_ordered = peg->convert_disk_list_to_vector(false);
            int disks_on_peg = vector_ordered.size();
                if (j > disks_on_peg){
                    std::cout << copy_n_times(peg_length,space)  << " ";
                }
                if(j <= disks_on_peg && j >=1){
                    tuple<string,int> t = vector_ordered[j-1];
                    int disk_order = get<1>(t);
                    int disk_order_length = to_string(disk_order).length();

                    string left = (copy_n_times(disk_order,line));
                    string center = "D" + to_string(disk_order);
                    int right_init = peg_length-disk_order - 1- disk_order_length; 
                    int right_n =  right_init > 0? right_init :0;
                    string right = (copy_n_times(right_n,space));
                    std::cout << left  << center << right << " ";
                }
                if(j <=0 ){
                    if(j == 0){
                        std::cout << copy_n_times(peg_length, "~") + space ;
                    }else if(j == -1){
                        int peg_order_length = to_string(peg->order).length();
                        std::cout << "$ PEG " + to_string(peg->order) + copy_n_times(peg_length-6-(peg_order_length)-2,space) + " $ " ;
                    }
                }

        }
        std::cout<<"\n";

    }


}




/*
bool Tower_Game::check_disks_w_pegs(bool update_written_peg ){
    bool found_inaccuracy = false;
    for(Peg* peg: this->peg_object_list ){
        string cur_peg_name = peg->name;
        std::cout << "Checking peg named " << cur_peg_name << "\n";
        if (peg->disk_names_list.size() == 0){
            std::cout << "Peg has no disks ... continuing to next peg " << cur_peg_name << "\n";
        }
        // check disks for each peg
        for(tuple<string,int> t : peg->disk_names_list){
            string disk_name = get<0>(t);
            std::cout << "Checking disk named " << disk_name << "\n";
            Disk* disk = this->get_disk_by_name(disk_name);
            if(disk->current_peg == cur_peg_name){
                std::cout << "Current disk of the peg is also written on the disk " << "\n ";
            }else{
                std::cout << "Current disk is at the peg "<<peg->name  << " but has other peg written: " << disk->current_peg  <<"\n ";
                if(update_written_peg){
                    std::cout << "Updating peg name on disk object to "<< peg->name << " ...\n";
                    disk->update_peg(peg->name); 
                }
                found_inaccuracy = true;
            }
        }
    }

    return !found_inaccuracy;
}
*/
