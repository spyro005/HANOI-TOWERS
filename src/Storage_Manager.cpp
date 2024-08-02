#include "../inc/Storage_Manager.h"


Storage_Manager::Storage_Manager(){
    this->Disk_objects = vector<Disk>();
    this->Peg_objects = vector<Peg>();

}

bool Storage_Manager::add_disk_object(Disk new_disk){
    this->Disk_objects.push_back(new_disk);
    return true;
}

bool Storage_Manager::add_peg_object(Peg new_peg){
    this->Peg_objects.push_back(new_peg);
    return true;
}

Disk Storage_Manager::get_disk_object(int disk_order){
    return this->Disk_objects[disk_order-1];
}

Peg Storage_Manager::get_peg_object(int peg_order){
    return this->Peg_objects[peg_order-1];
}

Disk* Storage_Manager::get_disk_ptr(int disk_order){
    return &(this->Disk_objects[disk_order-1]);
}

Peg* Storage_Manager::get_peg_ptr(int peg_order){
    return &(this->Peg_objects[peg_order-1]);
}