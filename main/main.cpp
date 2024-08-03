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

        // if statements have default values for variables

        int n_disks = var_map["NDISKS"];
        if(var_map.find("NDISKS") == var_map.end()){
            n_disks = 3;
        }
        int n_pegs = var_map["NPEGS"];
        if(var_map.find("NPEGS") == var_map.end()){
            n_disks = 3;
        }

        int debug = var_map["DEBUG"];
        if(var_map.find("DEBUG") == var_map.end()){
            n_disks = 3;
        }
        int status = var_map["STATUS"];
        if(var_map.find("STATUS") == var_map.end()){
            status = 0;
        }
        int draw = var_map["DRAW"];
        if(var_map.find("DRAW") == var_map.end()){
            draw = 1;
        }

        int draw_value = var_map["DRAW_MOVES"];
        if(var_map.find("DRAW_MOVES") == var_map.end()){
            draw_value = 1;
        }

        int print_moves = var_map["PRINT_MOVES"];
        if(var_map.find("PRINT_MOVES") == var_map.end()){
            print_moves = 1;
        }

        int out_to_file = var_map["REDIRECT_OUTPUT"];
        if(var_map.find("REDIRECT_OUTPUT") == var_map.end()){
            out_to_file = 1;
        }


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









 