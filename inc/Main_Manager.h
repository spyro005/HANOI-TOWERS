#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H

#include <list>
#include <tuple>
#include <string>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>
#include <filesystem>


#include "Iterative_Solution.h"

extern std::ofstream out_stream;

string get_path_of_file_name(string filename);
int delete_file_and_create_new(string filename);

unordered_map<string,int> read_input_file(string filename = "input.txt");
std::streambuf* redirect(string output_file = "output.txt");
void restore_and_close(streambuf* coutbuf);
ofstream open_file(string filename);
int run_solver(int n_disks=3,int n_pegs=3,int debug=1, int status=0, int draw=1, int draw_moves=1,int print_moves=1);



#endif