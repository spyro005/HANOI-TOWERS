#include "../inc/Peg.h"

#include <cstdlib>


using namespace std;




        Peg::Peg(string name, int order){
            this->name = name;
            this->order = order;
            if(stoi(getenv("DEBUG")) >= 2){
                cout << "Created peg named " << name << " in peg order " << order << "\n";
            }
        }

        bool Peg::add_disk_by_name(string disk_name,int order){
            if (this->disk_names_list.size() == 0){
                this->disk_names_list.push_back(tuple<string,int>(disk_name,order));
                if(stoi(getenv("DEBUG")) >= 3){
                    cout << "Added disk named " << disk_name << " to peg named " << (this->name) << "\n" ;
                }
                return true;
            }else{
                if (get<1>(this->disk_names_list.back()) > order){
                    this->disk_names_list.push_back(tuple<string,int>(disk_name,order));
                    if(stoi(getenv("DEBUG")) >= 3){
                        cout << "Added disk named " << disk_name << " to peg named " << (this->name) << "\n" ;
                    }
                    return true;
                }else{
                    if(stoi(getenv("DEBUG")) >= 3){
                    cout << "Cannot add disk with size " << order << "to this peg '"<< this->name << "' . Disk at the top of the peg has lower size "\
                    " " << get<1>(this->disk_names_list.back()) << "\n" ;
                    }
                    return false;
                }
            }
        }

        bool Peg::add_disk_by_name(string disk_name){
            if (disk_names_list.size() == 0){
                int default_size = 3;
                disk_names_list.push_back(tuple<string,int>(disk_name,default_size));
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "Added disk named " << disk_name << " to peg named" << (this->name) << "\n" ;
                }
                return true;
            }else{
                    int top_disk_order = get<1>(disk_names_list.back());
                    if (top_disk_order <= 1){
                        if(stoi(getenv("DEBUG")) >= 3){
                            cout << "Cannot add disk, top disk has order " << top_disk_order << " \n";
                        }
                        return false;
                    }
                    if(stoi(getenv("DEBUG")) >= 3){
                    cout << "Adding disk named " << disk_name << " to peg named" << (this->name) <<  \
                    " with size one less than the top one : " << top_disk_order <<" (size of the current top) \n";
                    disk_names_list.push_back(tuple<string,int>(disk_name, top_disk_order - 1));
                    cout << "Added disk named " << disk_name << " to peg named" << (this->name) << "\n" ;
                    }
                    
                    return true;
            }
        }

        bool Peg::add_disk_by_ptr(Disk* disk){
            if (disk == nullptr){
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "Given disk pointer is empty, cannot proceed " << " \n";
                }
                return false;
            }
            string disk_name = disk->name;
            int order = disk->order;

            if (name == "" || order < 1 ){
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "Cannot add disk, the given disk object has no name or order " << " \n";
                }
                return false;
            }
            disk->current_peg = this->name;
            return this->add_disk_by_name(disk_name,order);
        }

        bool Peg::remove_top_disk(){
            if (disk_names_list.size() == 0){
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "Peg " << this->name << " is empty, nothing to remove" << "\n" ;
                }
                return false;
            }else{
                string top_disk_name = get<0>(disk_names_list.back()) ;
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "Removing top disk named " << top_disk_name  <<" from this peg " << this->name << "\n" ;
                }
                disk_names_list.pop_back();
                return true;
            }
        }

        string Peg::read_top_disk(bool order){
            if (disk_names_list.size() == 0){
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "Peg is empty, no disk to read" << "\n" ;
                }
                return "";
            }else{
                if(order){
                    string top_disk_name = get<0>(disk_names_list.back()) ;
                    int disk_order = get<1>(disk_names_list.back()) ;
                    if(stoi(getenv("DEBUG")) >= 2){
                        cout << "Top disk of peg " << this->name << " is named "<< top_disk_name  << \
                        " and has order " << to_string(disk_order)  <<"\n" ;
                    }
                    return to_string(disk_order);
                }else{
                    string top_disk_name = get<0>(disk_names_list.back()) ;
                    if(stoi(getenv("DEBUG")) >= 2){
                        cout << "Top disk of peg " << this->name << " is named "<< top_disk_name  << "\n" ;
                    }
                    return top_disk_name;
                }
            }
        }

        list<tuple<string,int>> Peg::get_disks_with_order_list(){
            return this->disk_names_list;
        }

        list<tuple<string,int>> Peg::return_disks_copy_ordered(bool ascending){
            list<tuple<string, int>> or_disks = this->get_disks_with_order_list();
            list<tuple<string, int>> cloned_disks;
            std::copy(or_disks.begin(),or_disks.end(),std::back_inserter(cloned_disks));

            cloned_disks.sort([ascending](const tuple<string,int> &tuple1, const tuple<string,int> &tuple2){
                bool result = ascending? get<1>(tuple1) < get<1>(tuple2) : get<1>(tuple1) > get<1>(tuple2); 
                return result;
            });

            return cloned_disks;
        }

        vector<tuple<string,int>> Peg::convert_disk_list_to_vector(bool ascending){
            list<tuple<string,int>> disks_ordered = this->return_disks_copy_ordered(ascending);
            vector<tuple<string,int>> vector_ordered;
            vector_ordered.reserve(disks_ordered.size());
            std::copy(disks_ordered.begin(),disks_ordered.end(),std::back_inserter(vector_ordered)); 
            return vector_ordered;

        }


        vector<string> Peg::get_disk_names_in_order(){
            list<tuple<string,int> > list_disks_ordered = this->get_disks_with_order_list();
            vector<string> disk_names_vector = vector<string>();
            for(tuple<string,int> t: list_disks_ordered){
                string disk_name = get<0>(t);
                disk_names_vector.push_back(disk_name);
            }

            return disk_names_vector;
        }

        void Peg::print_status(){
            cout << "Status for peg named " << this->name << " in peg order " << this->order << "\n" ;
            cout << "Peg has the following disks on it, with given names and size:";
            list<tuple<string,int> > disks_ordered = this->return_disks_copy_ordered();
            for(tuple<string,int> disk_tuple : disks_ordered){
                cout << "Disk named " << get<0>(disk_tuple) << " and size - order  " << get<1>(disk_tuple) <<"\n";
            } 
        }


