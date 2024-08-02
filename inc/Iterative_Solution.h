#ifndef ITERATIVE_SOLUTION_H
#define ITERATIVE_SOLUTION_H

#include "Tower_Game_Manager.h"

#include "Move.h"

class Iterative_Solution{
    public:
        Tower_Game_Manager tower_game_manager;

        list<tuple<Move,int>> moves;

        Iterative_Solution();

        bool setup_game(int n_disks=3,int n_pegs=3);

        string get_next_peg_name_clockwise(string current_peg);

        bool eq_pegs_disks_fast_solution();
        
        bool more_pegs_fast_solution();

        bool general_solution_with_iteration();

        bool general_iterative_solution();

        bool three_peg_general_iterative_solution(string in_source_peg = "", 
        string in_aux_peg = "", string in_dest_peg = "", int call =1);

        bool three_peg_three_disks_move_smallest_disk_clockwise();

        bool three_peg_three_disks_make_sole_allowed_move_and_not_smallest_disk();

        bool three_peg_three_disks_focs_iterative_solution();

        bool check_temp_solution(string peg_name);

        bool check_final_solution();

        void sort_moves(bool acending=true);
        void print_all_game_moves(bool ascending=true);



};

#endif