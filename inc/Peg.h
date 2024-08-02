#ifndef PEG_H
#define PEG_H

#include "Disk.h"

using namespace std;

class Peg{
    public:
        string name = "";
        int order = -1;
        list<tuple<string,int> > disk_names_list = {};

        Peg(){};

        Peg(string name, int order);

        bool add_disk_by_name(string disk_name,int order);

        bool add_disk_by_name(string disk_name);

        bool add_disk_by_ptr(Disk* disk);

        bool remove_top_disk();

        string read_top_disk(bool order=false);

        vector<string> get_disk_names_in_order();

        list<tuple<string,int> > get_disks_with_order_list();

        list<tuple<string,int> > return_disks_copy_ordered(bool ascending =true);

        vector<tuple<string, int>> convert_disk_list_to_vector(bool ascending=true);

        void print_status();

};

#endif


