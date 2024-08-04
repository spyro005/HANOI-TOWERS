#include "../inc/Iterative_Solution.h"
#include <cmath>
#include <cstdlib>

Iterative_Solution::Iterative_Solution(){

}


bool Iterative_Solution::setup_game(int n_disks, int n_pegs){
    this->tower_game_manager = Tower_Game_Manager(n_disks,n_pegs);
    this->tower_game_manager.Create_Tower_Game_Objects();
    this->tower_game_manager.Default_Setup_Tower_Game();
    return true;
}

string Iterative_Solution::get_next_peg_name_clockwise(string current_peg_name){
    vector<string> peg_names_in_order = this->tower_game_manager.tower_game.get_peg_names_in_order(false);
    //fix ascending order
    this->tower_game_manager.tower_game.sort_peg_list_by_order();

    bool found_current_peg = false;
    string next_peg_name = "";
    for(string peg_name: peg_names_in_order){
        if(found_current_peg == true){
            next_peg_name = peg_name;
            break;
        }
        if(current_peg_name == peg_name){
            found_current_peg = true;
        }
    }

    if(found_current_peg && next_peg_name == ""){
        next_peg_name = peg_names_in_order[0];
    }

    return next_peg_name;
}

bool Iterative_Solution::three_peg_three_disks_move_smallest_disk_clockwise(){
    string smallest_disk = this->tower_game_manager.tower_game.get_smallest_disk_name();
    Disk* current_disk = this->tower_game_manager.tower_game.get_disk_by_name(smallest_disk);
    string current_peg_name = current_disk->get_current_peg();
    string next_peg = this->get_next_peg_name_clockwise(current_peg_name);

    return this->tower_game_manager.tower_game.move_disk(smallest_disk,next_peg);
}

bool Iterative_Solution::three_peg_three_disks_make_sole_allowed_move_and_not_smallest_disk(){
    string smallest_disk = this->tower_game_manager.tower_game.get_smallest_disk_name();
    vector<string> disks = this->tower_game_manager.tower_game.get_disk_names_in_order();
    vector<string> pegs = this->tower_game_manager.tower_game.get_peg_names_in_order();
    bool move = false;
    for(string peg_name: pegs){
        Peg* peg = this->tower_game_manager.tower_game.get_peg_by_name(peg_name);
        string top_disk_of_peg = peg->read_top_disk();
        if(top_disk_of_peg != smallest_disk && top_disk_of_peg.length() > 0){
            string current_peg = peg->name; 
            string next_peg = this->get_next_peg_name_clockwise(current_peg);
            while(next_peg != peg->name){
                move = this->tower_game_manager.tower_game.move_disk(top_disk_of_peg,next_peg);
                if(move){
                    if(stoi(getenv("DEBUG")) >= 2){
                        cout << "MOVED DISK " << top_disk_of_peg << " to Peg " << next_peg << "\n";
                    }
                    break;
                }
                next_peg = this->get_next_peg_name_clockwise(next_peg);
            }
            break;
        }
    }

    return move;
}

bool Iterative_Solution::three_peg_three_disks_focs_iterative_solution(){
    cout << "\nTHREE PEG THREE DISKS CLASSIC FOCS ITERATIVE SOLUTION\n";
    this->tower_game_manager.tower_game.print_status();
    int i = 0;
    while(!this->check_final_solution()){
        i++;
        cout << "ITERATION " << i << "\n";
        this->three_peg_three_disks_move_smallest_disk_clockwise();
        this->three_peg_three_disks_make_sole_allowed_move_and_not_smallest_disk();
        this->tower_game_manager.tower_game.print_status();
    }
    
    return true;
}


bool Iterative_Solution::check_final_solution(){
    vector<string> all_disks = this->tower_game_manager.tower_game.get_disk_names_in_order();
    vector<string> pegs = this->tower_game_manager.tower_game.get_peg_names_in_order();
    string last_peg_name = pegs[pegs.size()-1];

    Peg* last_peg_ptr = tower_game_manager.tower_game.get_peg_by_name(last_peg_name);
    vector<string> peg_disks = last_peg_ptr->get_disk_names_in_order();

    if(peg_disks.size() != all_disks.size()){
            if(stoi(getenv("DEBUG")) >= 2){
                cout << "Peg still does not have all the disks \n";
            }
        return false;
    }

    if(stoi(getenv("DEBUG")) >= 2){
            cout << "Peg has all disks \n";
    }

    return true;

}

bool Iterative_Solution::check_temp_solution(string peg_name){
    return this->tower_game_manager.check_all_disks_on_peg(peg_name);
}

bool Iterative_Solution::three_peg_general_iterative_solution(string in_source_peg , string in_aux_peg , string in_dest_peg,int call){
    int n_disks = this->tower_game_manager.get_total_number_of_disks();
    vector<string> peg_names = this->tower_game_manager.tower_game.get_peg_names_in_order();
    //if((peg_names.size() != 3) && (in_source_peg == "") && (in_aux_peg == "") && (in_dest_peg == "")){
    //    cout << " MUST HAVE 3 PEGS. Not " << peg_names.size()  << "\n";
    //    return false;
    //}
    int total_moves = pow(2,n_disks) - 1;
    //std::uint64_t total_moves_l = pow(2,n_disks) -1; 
    string source_peg = in_source_peg == ""?peg_names[0]:in_source_peg ;
    string aux_peg = in_aux_peg == ""?peg_names[1]:in_aux_peg;
    string dest_peg = in_dest_peg == ""?peg_names[2]:in_dest_peg;
    if(n_disks%2 == 0){
        string a = aux_peg;
        aux_peg = dest_peg;
        dest_peg = a;
    }
    
    string s = "";
    string d = "";
    string top_disk = "";
    int moves_so_far = this->moves.size();

    if(stoi(getenv("DEBUG")) >= 2){
        cout << "STARTING" << call << " ITERATIVE SOLUTION WITH " << n_disks << " DISKS AND " <<  "3" << " PEGS\n";
    }
 
    if(stoi(getenv("DRAW")) == 2){
        cout << "INITIAL GAME DRAW AT CALL " << call << "\n";
        this->tower_game_manager.tower_game.draw_status();
    }
    if(stoi(getenv("DRAW")) == 1){
        cout << "INITIAL GAME DRAW AT CALL " << call << "\n";
        this->tower_game_manager.tower_game.draw_line_status();
    }

    if(stoi(getenv("STATUS")) >= 2){
        cout << "INITIAL STATUS at call" << call  << "\n";
        this->tower_game_manager.tower_game.print_status();
    }

    if(stoi(getenv("DEBUG")) >= 2){
        cout << "TOTAL NUMBER OF DISKS: " << n_disks << "\n";
        cout << "TOTAL NUMBER OF MOVES: " << total_moves << "\n";
    }
    for(int i=1; i <= total_moves;i++){
        moves_so_far++;
        if(stoi(getenv("DEBUG")) >= 2){
            cout << "MOVE " << i << " 3 peg iteration " << call <<"\n";
        }
        if(i%3 == 1){
            s = source_peg;
            d = dest_peg;
            //top_disk =
            bool move_1_a = this->tower_game_manager.tower_game.move_disk_b_pegs(source_peg,dest_peg);
            if(!move_1_a){
                bool move_1_b = this->tower_game_manager.tower_game.move_disk_b_pegs(dest_peg,source_peg);
                if(!move_1_b){
                    return false;
                }
                s = dest_peg;
                d = source_peg;
                
            }
        }else if (i%3 == 2)
        {
            s = source_peg;
            d = aux_peg;
            bool move_2_a = this->tower_game_manager.tower_game.move_disk_b_pegs(source_peg,aux_peg);
            if(!move_2_a){
                bool move_2_b = this->tower_game_manager.tower_game.move_disk_b_pegs(aux_peg,source_peg);
                if(!move_2_b){
                    return false;
                }
                s = aux_peg;
                d = source_peg;
            }
        }else if(i%3 == 0){
            s = aux_peg;
            d = dest_peg;
            bool move_0_a = this->tower_game_manager.tower_game.move_disk_b_pegs(aux_peg,dest_peg);
            if(!move_0_a){
                bool move_0_b = this->tower_game_manager.tower_game.move_disk_b_pegs(dest_peg,aux_peg);
                if(!move_0_b){
                    return false;
                }
                s = dest_peg;
                d = aux_peg;
            }
        }

        top_disk = this->tower_game_manager.tower_game.get_top_disk_of_peg(d); // top disk before movement
        tuple<Move,int> move = tuple(Move(s, d,top_disk),moves_so_far); 
        this->moves.push_back(move);

        if(stoi(getenv("DEBUG")) >= 1){
            std::cout << "\nMOVE #"<< moves_so_far << ") "<< get<0>(move).move_name << "\n";
        }
        
        if(stoi(getenv("STATUS")) >= 3){
            this->tower_game_manager.tower_game.print_status();
        }

        if(stoi(getenv("DRAW_MOVES")) == 2){
            this->tower_game_manager.tower_game.draw_status();
        }
        if(stoi(getenv("DRAW_MOVES")) == 1){
            this->tower_game_manager.tower_game.draw_line_status();
        }
    }

        
    string final_peg = n_disks%2 == 0? aux_peg:dest_peg;
    return this->check_temp_solution(final_peg);

}

bool Iterative_Solution::general_iterative_solution(){
    
    int total_number_of_pegs = this->tower_game_manager.get_total_number_of_pegs();

    if(total_number_of_pegs < 3){
        cout << "NEED AT LEAST 3 PEGS. HAVE LESS. EXITING \n" ;

        return false;
    }
    if(total_number_of_pegs == 3){
        return this->three_peg_general_iterative_solution();
    }

    bool first_three = three_peg_general_iterative_solution();
    if(!first_three){
        cout << "MOVING ALL DISKS TO THIRD PEG FAILED. EXITING.. \n";
        return false;
    }

    //int quot = total_number_of_pegs / 3;
    //int rem = total_number_of_pegs%3;

    //cout << "quot: " << quot << "\n";

    int i = 0;
    int k = 0;
    vector<string> peg_names = this->tower_game_manager.tower_game.get_peg_names_in_order();
    for(int j=2; j < total_number_of_pegs; j = j+2){
        //cout << "quot iteration " << j << "\n";
        i ++; 
        k = j;
        //cout << "i " << i <<"\n";
        string s_peg = "";
        string aux_peg = "";
        string dest_peg = "";
        try{
            s_peg = peg_names.at(j);
            aux_peg = peg_names.at(j+1);
            dest_peg = peg_names.at(j+2);
        }catch (const std::out_of_range& e) {
            if(stoi(getenv("DEBUG")) >= 1){
                std::cerr << "Error, vector out of range (might be OK to IGNORE in iter. solution): " <<
                 e.what() << " at for loop index " << j << " . Array size is "<< peg_names.size()<< " ." <<std::endl;
            }
            //if(s_peg == "" || aux_peg == "" || dest_peg == ""){
            if(stoi(getenv("DEBUG")) >= 2){
                std::cout << "EXITING QUOT LOOP, NOT ALL 3 PEGS ARE VALID NAMES \n";
                std::cout << "WE CONTINUE WITH THIRD TO LAST PEG AS AUXILARY OR END HERE AT LAST PEG\n";
            }
                break;
            //}
        }
        if(stoi(getenv("DEBUG")) >= 2){
            cout << "THE 3 PEGS: " << s_peg << ", " << aux_peg << ", "<< dest_peg << " \n";
        }
        this->three_peg_general_iterative_solution(s_peg,aux_peg,dest_peg,i+1);
    }

    // if already at last peg
    if(total_number_of_pegs - (k+1) <= 0){
        string last_peg = peg_names[total_number_of_pegs-1];
        return this->check_temp_solution(last_peg);
    }

    // last 3 peg iteration, with third to last as aux peg
    try{
        string s_peg = peg_names.at(k);
        string aux_peg = peg_names.at(k-1);
        string dest_peg = peg_names.at(k+1);
        return this->three_peg_general_iterative_solution(s_peg,aux_peg,dest_peg,i+1);
    
    }catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;    
    }

    
}

bool Iterative_Solution::more_pegs_fast_solution(){

    int total_n_disks = this->tower_game_manager.get_total_number_of_disks();
    int total_n_pegs = this->tower_game_manager.get_total_number_of_pegs();
    if(total_n_pegs > total_n_disks ){
        if(stoi(getenv("DEBUG")) >= 2){
            cout << "FAST SOLUTION WITH MORE PEGS THAN DISKS. \n";    
        }
        vector<string> disk_names = this->tower_game_manager.tower_game.get_disk_names_in_order();
        vector<string> peg_names = this->tower_game_manager.tower_game.get_peg_names_in_order();

        string first_peg = peg_names.front();
        string last_peg = peg_names.back();

        cout << first_peg <<" " <<last_peg << " " << total_n_disks << " "<< total_n_pegs <<"\n";

        // 1. all disks must be on fist peg
        if(this->check_temp_solution(first_peg)){
            // share disks on pegs in reverse (small disk at left)
            for(int i = 1;i<= total_n_disks;i++){
                string disk_name = disk_names.at(i-1);
                string target_peg_name = peg_names.at(total_n_pegs-1-(total_n_disks-i));

                string s = this->tower_game_manager.tower_game.get_disk_by_name(disk_name)->current_peg;
                
                bool moved = this->tower_game_manager.tower_game.move_disk(disk_name, target_peg_name);
                if(!moved) {
                    if(stoi(getenv("DEBUG")) >= 2){
                        std::cout << "1) false move DISK "<< disk_name << " to peg " << target_peg_name << "\n";
                    }
                    return false;
                }

                if(stoi(getenv("STATUS")) >= 3){
                    this->tower_game_manager.tower_game.print_status();
                }
                
                tuple<Move,int> move = tuple(Move(s, target_peg_name,disk_name), this->moves.size()+1); 
                this->moves.push_back(move);


                if(stoi(getenv("DEBUG")) >=1 ){
                    std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move).move_name << "\n";
                }

                if(stoi(getenv("DRAW_MOVES")) == 1){
                    this->tower_game_manager.tower_game.draw_line_status();
                }

                if(stoi(getenv("DRAW_MOVES")) == 2){
                    this->tower_game_manager.tower_game.draw_status();
                }



            }

            if(stoi(getenv("DEBUG")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

            // 2. put all disks on last peg
            for(int i = 1;i< total_n_disks;i++){
                string disk_name = disk_names.at(total_n_disks-1-i);

                string s = this->tower_game_manager.tower_game.get_disk_by_name(disk_name)->current_peg;

                bool moved = this->tower_game_manager.tower_game.move_disk(disk_name, last_peg);
                if(!moved) {
                    if(stoi(getenv("DEBUG")) >= 2){
                        std::cout << "2) false move DISK "<< disk_name << " to " << last_peg << "\n";
                    }
                    return false;
                }
                if(stoi(getenv("STATUS")) >= 3){
                    this->tower_game_manager.tower_game.print_status();
                }

                tuple<Move,int> move = tuple(Move(s, last_peg,disk_name), this->moves.size()+1); 
                this->moves.push_back(move);

                if(stoi(getenv("DEBUG")) >=1 ){
                    std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move).move_name << "\n";
                }

                if(stoi(getenv("DRAW_MOVES")) == 1){
                    this->tower_game_manager.tower_game.draw_line_status();
                }

                if(stoi(getenv("DRAW_MOVES")) == 2){
                    this->tower_game_manager.tower_game.draw_status();
                }
            }
            
            return true;


            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

        }

        if(stoi(getenv("DEBUG")) >= 2){
            std::cout << "ALL DISKS MUST BE ON FIRST PEG TO START SOLUTION. EXITING.. \n";
        }

        return false;

    }

    if(stoi(getenv("DEBUG")) >= 2){
        std::cout << "WE NEED MORE PEGS THAN DISKS TO START SOLUTION. EXITING.. \n";
    }

    return false;
    
}


bool Iterative_Solution::eq_pegs_disks_fast_solution(){
    int total_n_disks = this->tower_game_manager.get_total_number_of_disks();
    int total_n_pegs = this->tower_game_manager.get_total_number_of_pegs();
    if(total_n_pegs == total_n_disks ){
        if(stoi(getenv("DEBUG")) >= 2){
            cout << "EQ PEGS WITH DISKS SOLUTION \n";
        }

        vector<string> disk_names = this->tower_game_manager.tower_game.get_disk_names_in_order();
        vector<string> peg_names = this->tower_game_manager.tower_game.get_peg_names_in_order();

        string first_peg = peg_names.front();
        string last_peg = peg_names.back();

        if(stoi(getenv("DEBUG")) >= 2){
            cout << first_peg <<" " <<last_peg << " " << total_n_disks << " "<< total_n_pegs <<"\n";
        }

        //1. all disks must be on fist peg
        if(this->check_temp_solution(first_peg)){
            // share disks on pegs in reverse (small disk at right)
            for(int i = 1;i< total_n_disks;i++){
                string disk_name = disk_names.at(i-1);
                string target_peg_name = peg_names.at(total_n_pegs-1-(i-1));

                string s1 = this->tower_game_manager.tower_game.get_disk_by_name(disk_name)->current_peg;

                bool moved = this->tower_game_manager.tower_game.move_disk(disk_name, target_peg_name);
                if(!moved) {
                    if(stoi(getenv("DEBUG")) >= 2){
                        cout << "1) false move "<< disk_name << " " << target_peg_name << "\n";
                    }
                    return false;
                }
                if(stoi(getenv("STATUS")) >= 3){
                    this->tower_game_manager.tower_game.print_status();
                }
                tuple<Move,int> move1 = tuple(Move(s1, target_peg_name,disk_name), this->moves.size()+1); 
                this->moves.push_back(move1);

                if(stoi(getenv("DEBUG")) >=1 ){
                    std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move1).move_name << "\n";
                }

                if(stoi(getenv("DRAW_MOVES")) == 1){
                    this->tower_game_manager.tower_game.draw_line_status();
                }

                if(stoi(getenv("DRAW_MOVES")) == 2){
                    this->tower_game_manager.tower_game.draw_status();
                }


            }

            
            if(stoi(getenv("STATUS")) >= 2){
                    this->tower_game_manager.tower_game.print_status();
            }
            
            // 2. move first disk on pre last peg
            string pre_last_peg = peg_names[total_n_pegs-1-1];
            string first_disk = disk_names[0];
            string s2 = this->tower_game_manager.tower_game.get_disk_by_name(first_disk)->current_peg;
            bool moved = this->tower_game_manager.tower_game.move_disk(first_disk, pre_last_peg);
            if(!moved) {
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "2) false move "<< first_disk << " " << pre_last_peg << "\n";
                }
                return false;
            }

            tuple<Move,int> move2 = tuple(Move(s2, pre_last_peg,first_disk), this->moves.size()+1); 
            this->moves.push_back(move2);


            if(stoi(getenv("DEBUG")) >=1 ){
                std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move2).move_name << "\n";
            }

            if(stoi(getenv("DRAW_MOVES")) == 1){
                this->tower_game_manager.tower_game.draw_line_status();
            }

            if(stoi(getenv("DRAW_MOVES")) == 2){
                this->tower_game_manager.tower_game.draw_status();
            }

            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

            // move largest disk to last peg
            string last_disk = disk_names[total_n_disks-1];
            string s3 = this->tower_game_manager.tower_game.get_disk_by_name(last_disk)->current_peg;

            moved = this->tower_game_manager.tower_game.move_disk(last_disk, last_peg);


            if(!moved) {
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "3) false move "<< last_disk << " " << last_peg << "\n";
                }
                return false;
            }

            tuple<Move,int> move3 = tuple(Move(s3, last_peg,last_disk), this->moves.size()+1); 
            this->moves.push_back(move3);

            if(stoi(getenv("DEBUG")) >=1 ){
                std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move3).move_name << "\n";
            }

            if(stoi(getenv("DRAW_MOVES")) == 1){
                this->tower_game_manager.tower_game.draw_line_status();
            }

            if(stoi(getenv("DRAW_MOVES")) == 2){
                this->tower_game_manager.tower_game.draw_status();
            }
        
            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

            // 4. put all disks on last peg except first two
            for(int i = 1;i< total_n_disks-2;i++){
                string disk_name = disk_names.at(total_n_disks-1-i);
                string s4 = this->tower_game_manager.tower_game.get_disk_by_name(disk_name)->current_peg;
                bool moved = this->tower_game_manager.tower_game.move_disk(disk_name, last_peg);
                if(!moved){
                    if(stoi(getenv("DEBUG")) >= 2){
                        cout << "4) false move "<< disk_name << " " << last_peg << "\n";
                    }
                    return false;
                } 

                tuple<Move,int> move4 = tuple(Move(s4, last_peg,disk_name), this->moves.size()+1); 
                this->moves.push_back(move4);

                if(stoi(getenv("DEBUG")) >=1 ){
                    std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move4).move_name << "\n";
                }

                if(stoi(getenv("DRAW_MOVES")) == 1){
                    this->tower_game_manager.tower_game.draw_line_status();
                }

                if(stoi(getenv("DRAW_MOVES")) == 2){
                    this->tower_game_manager.tower_game.draw_status();
                }

                if(stoi(getenv("STATUS")) >= 3){
                   this->tower_game_manager.tower_game.print_status();
               }

            }

            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

            //5. put smalles disk on pre pre last peg
            string pre_pre_last_peg = peg_names[total_n_pegs-1-2];
            string s5 = this->tower_game_manager.tower_game.get_disk_by_name(first_disk)->current_peg;
            moved = this->tower_game_manager.tower_game.move_disk(first_disk, pre_pre_last_peg);
            if(!moved) {
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "5) false move "<< last_disk << " " << first_peg << "\n";
                }
                return false;
            }

            tuple<Move,int> move5 = tuple(Move(s5, pre_pre_last_peg, first_disk), this->moves.size()+1); 
            this->moves.push_back(move5);

            if(stoi(getenv("DEBUG")) >=1 ){
                std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move5).move_name << "\n";
            }

            if(stoi(getenv("DRAW_MOVES")) == 1){
                this->tower_game_manager.tower_game.draw_line_status();
            }

            if(stoi(getenv("DRAW_MOVES")) == 2){
                this->tower_game_manager.tower_game.draw_status();
            }

            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

            //6. put second  disk on last peg
            string second_disk = disk_names[1];
            string s6 = this->tower_game_manager.tower_game.get_disk_by_name(second_disk)->current_peg;
            moved = this->tower_game_manager.tower_game.move_disk(second_disk, last_peg);
            if(!moved) {
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "6) false move "<< second_disk << " " << last_peg << "\n";
                }
                return false;
            }

            tuple<Move,int> move6 = tuple(Move(s6, last_peg,second_disk), this->moves.size()+1); 
            this->moves.push_back(move6);

            if(stoi(getenv("DEBUG")) >=1 ){
                std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move6).move_name << "\n";
            }

            if(stoi(getenv("DRAW_MOVES")) == 1){
                this->tower_game_manager.tower_game.draw_line_status();
            }

            if(stoi(getenv("DRAW_MOVES")) == 2){
                this->tower_game_manager.tower_game.draw_status();
            }

            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }

            //7. put first disk on last peg
            string s7 = this->tower_game_manager.tower_game.get_disk_by_name(first_disk)->current_peg;
            moved = this->tower_game_manager.tower_game.move_disk(first_disk, last_peg);
            if(!moved) {
                if(stoi(getenv("DEBUG")) >= 2){
                    cout << "7) false move "<< second_disk << " " << last_peg << "\n";
                }
                return false;
            }

            tuple<Move,int> move7 = tuple(Move(s7,last_peg,first_disk), this->moves.size()+1); 
            this->moves.push_back(move7);

            if(stoi(getenv("DEBUG")) >=1 ){
                std::cout << "\nMove #" << to_string(this->moves.size()) << ") " << get<0>(move7).move_name << "\n";
            }

            if(stoi(getenv("DRAW_MOVES")) == 1){
                this->tower_game_manager.tower_game.draw_line_status();
            }

            if(stoi(getenv("DRAW_MOVES")) == 2){
                this->tower_game_manager.tower_game.draw_status();
            }

            if(stoi(getenv("STATUS")) >= 2){
                this->tower_game_manager.tower_game.print_status();
            }


            return true;

        }

        return false;

    }

    return false;
}

bool Iterative_Solution::general_solution_with_iteration() {
    if(this->tower_game_manager.get_total_number_of_pegs() > this->tower_game_manager.get_total_number_of_disks()){
        return this->more_pegs_fast_solution();
    }else if(this->tower_game_manager.get_total_number_of_disks() == this->tower_game_manager.get_total_number_of_pegs()){
        return this->eq_pegs_disks_fast_solution();
    }else{
        return this->general_iterative_solution();
    }
    
    return true;
}

void Iterative_Solution::sort_moves(bool ascending){
    this->moves.sort([ascending](const tuple<Move,int> &move_tuple1,const tuple<Move,int> &move_tuple2){
        bool result = ascending ? (get<1>(move_tuple1) < get<1>(move_tuple2)): (get<1>(move_tuple1) > get<1>(move_tuple2))  ; 
        return result;
    });
}

void Iterative_Solution::print_all_game_moves(bool ascending){
    cout << "\n\n Printing moves \n\n";
    this->sort_moves(ascending);
    int start_size = this->moves.size(); 
    for(int i=0;i < start_size;i++){
        string move_name = get<0>(this->moves.front()).move_name; 
        cout <<"#" << to_string(i+1) << ") "<< move_name << "\n";
        this->moves.pop_front();
    }

}


     




/*
        bool Iterative_Solution::setup_solution(){
            //assume tower game is initialized
            int number_disks = 0;
            int number_pegs = 0;

            Tower_Game* tg = this->tower_game;

            int highest_order_peg = -1;
            Peg* last_peg;
            for(Peg* peg : tg->peg_object_list){
                number_pegs += 1;
                if(peg->order > highest_order_peg ){
                    highest_order_peg = peg->order;
                    last_peg = peg;
                }
            }

            int previous_order = 1000000;
            for(Disk* disk : tg->disk_object_list){
                number_disks += 1;
                //looking for smallest disk
                if(disk->order < previous_order){
                    //cout << disk->order << " smaller\n" 
                    this->smallest_disk =  disk;
                    previous_order = disk->order;
                }

            }

            this->number_disks = number_disks;
            this->number_pegs = number_pegs;
            this->last_peg = last_peg;

            return true;


        }

        bool Iterative_Solution::check_final_state(){
            //check number of disks at last peg
            int n_disks_last_peg = 0;
            for(tuple<string,int> t : this->last_peg->disk_names_list){
                n_disks_last_peg += 1;
            }

            if (n_disks_last_peg < this->number_disks){
                cout << "Was expecting " << to_string(this->number_disks) << " disks at last peg but found " << to_string(n_disks_last_peg) + " \n" ;
                return false;
            }

            //check disk order

            int previous_order = get<1>(this->last_peg->disk_names_list.front());
            int number_of_disks = 0;
            for(tuple<string,int> t : this->last_peg->disk_names_list){
                number_disks += 1;
                if (get<1>(t) > previous_order){
                    cout << "Was expecting disk size less than " << to_string(previous_order) <<  
                    "  but found disk size " << to_string(get<1>(t)) + " for disk number  " << number_of_disks <<  " on the peg \n" ;
                    return false;
                }
            }

            return true;

        }

*/

