#include "../inc/Demo.h"

using namespace std;


Demo::Demo(){

}

void Demo::play_demo(){

        cout << "One Peg Demo" << "\n";
        Peg p1 = Peg("Peg 1",1);
        
        
        p1.add_disk_by_name("disk 5",5);
        p1.add_disk_by_name("disk 2",2);
        p1.add_disk_by_name("disk 1",1);
        p1.remove_top_disk();
        p1.remove_top_disk();

        cout << "Tower Game Demo" << "\n";

        Tower_Game t;

        Disk d1 = Disk("Disk 1",1);
        Disk d2 = Disk("Disk 2",2);
        Disk d3 = Disk("Disk 3",3);
        Disk d4 = Disk("Disk 4",4);

        Peg pA = Peg("A",1);
        Peg pB = Peg("B",2);
        Peg pC = Peg("C",3);

        t.add_peg_pointer(&pA);
        t.add_peg_pointer(&pB);
        t.add_peg_pointer(&pC);

        t.add_disk_pointer(&d1);
        t.add_disk_pointer(&d2);
        t.add_disk_pointer(&d3);

        pA.add_disk_by_ptr(&d3);
        pA.add_disk_by_ptr(&d2);
        pA.add_disk_by_ptr(&d1);

        t.print_status();

        t.move_disk("Disk 1","C");
        t.move_disk("Disk 2","B");
        t.move_disk("Disk 2","C");
        
        t.print_status();

        t.move_disk("Disk 1","B");
        t.move_disk("Disk 3","C");
        t.move_disk("Disk 1","C");
        t.move_disk("Disk 2","A");
        t.move_disk("Disk 1","A");

        t.print_status();

        t.move_disk("Disk XXCXXX","A");
        t.move_disk("Disk XXCXXX","XXX");
        t.move_disk("Disk 3","A");
        t.move_disk("Disk 3","XXX");

        t.print_status();



        /*
        cout << "Iterative Solution Demo" << "\n";
        Tower_Game t2;
        Iterative_Solution its = Iterative_Solution(&t);

        its.setup_solution();
        cout << its.number_disks << " \n";
        cout << its.number_pegs << " \n";
        cout << its.smallest_disk->name << " \n";

        pB.add_disk_by_ptr(&d3);

        t.add_peg_pointer(&pB);
        t.add_peg_pointer(&pA);

        t.check_disks_w_pegs();

        pA.add_disk_by_ptr(&d2);
        pA.add_disk_by_ptr(&d1);

        pB.add_disk_by_ptr(&d3);
        

        t.add_disk_object(&d1);
        t.add_disk_object(&d2);
        t.add_disk_object(&d3);

        t.add_disk_object(&d3);

        t.check_disks_w_pegs();

        t.add_peg_pointer(&pC);
        t.print_status();
        pC.add_disk_by_ptr(&d4);
        t.print_status();
        pB.add_disk_by_ptr(&d3);
        pA.add_disk_by_ptr(&d3);
        t.print_status();
        pA.remove_top_disk();
        pC.remove_top_disk();
        t.print_status();
        pC.add_disk_by_ptr(&d4);
        t.move_disk("Disk 2","C");
        t.print_status();
        t.move_disk("Disk 3","C");
        t.print_status();
        */

}