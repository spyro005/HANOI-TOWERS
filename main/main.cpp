#include <iostream>
#include <list>
#include <tuple>
#include <string>
#include <cstdlib>

//#include "../inc/Demo.h"
#include "../inc/Main_Manager.h"


using namespace std;

int main () {


        unordered_map<string,int> var_map = read_input_file("input.txt");

        int n_disks = var_map["NDISKS"];
        int n_pegs = var_map["NPEGS"];

        int debug = var_map["DEBUG"];
        int status = var_map["STATUS"];
        int draw = var_map["DRAW"];
        int draw_value = var_map["DRAW_MOVES"];
        int print_moves = var_map["PRINT_MOVES"];

        int out_to_file = var_map["REDIRECT_OUTPUT"];


        if(out_to_file){
            cout << "\n\n SOLVER OUTPUT TO OUTPUT.TXT FILE\n\n";
            streambuf* sbf = redirect("output.txt");

            run_solver(n_disks, n_pegs, debug, status, draw, draw_value, print_moves);

            restore_and_close(sbf);
            
            return 0;
        }

        cout << "\nSOLVER OUTPUT ON TERMINAL \n";
        run_solver(n_disks, n_pegs, debug, status, draw, draw_value,print_moves);


        //run_solver(3,3,1,0,1,1);

        //cout << stoi(getenv("DRAW")) << " DRAW\n";
        //cout << stoi(getenv("DEBUG")) << " DEBUG\n";

        return 0;

}









 