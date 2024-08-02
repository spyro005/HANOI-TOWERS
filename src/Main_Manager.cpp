#include "../inc/Main_Manager.h"


std::ofstream out_stream;

string get_path_of_file_name(string filename){
    std::filesystem::path curr_path = std::filesystem::current_path();
    std::filesystem::path filename_path = "main/" + filename;

    std::filesystem::path full_path = curr_path / filename_path;
    cout << "FULL PATH " << curr_path.string() << " " << filename_path.string()  <<" " << full_path.string() << "\n";

    return full_path.string();
}

unordered_map<string,int> read_input_file(string filename ){

    unordered_map<string,int> out_map = unordered_map<string,int>();
    // Create an ifstream object for the input file
    std::ifstream inputFile;

    string file = get_path_of_file_name(filename);

    inputFile.open(file);

    // Check if the file stream is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return out_map;
    }

    // String to hold each line read from the file
    std::string line;

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        // String to hold the word
        std::string variable;
        // Integer and float to hold the values
        int intValue;
        // Create a stringstream from the line
        std::istringstream iss(line);

        // Extract the word and the values
        iss >> variable >> intValue ;

        // Process the extracted values (here we simply print them)
        std::cout << "Variable: " << variable << ", Value: " << intValue << std::endl;

        out_map[variable] = intValue;
    }

    inputFile.close();

    return out_map;

}

streambuf* redirect(string output_file){
    //delete_file_and_create_new(errorfile);
    delete_file_and_create_new(output_file);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    //out_stream = open_file(output_file);
    out_stream.open(get_path_of_file_name("output.txt"));
    std::cout.rdbuf(out_stream.rdbuf()); //redirect std::cout to out.txt!
    return coutbuf;
}

ofstream open_file(string filename){
    ofstream out(get_path_of_file_name("output.txt"));
    return out;
}

void restore_and_close(streambuf* coutbuf){
    std::cout.rdbuf(coutbuf);

    out_stream.close();
}


int delete_file_and_create_new(string filename){
    string full_path = get_path_of_file_name(filename);

    std::filesystem::path filePath = full_path;

    // Delete the file if it exists
    if (std::filesystem::exists(filePath)) {
        std::error_code ec;
        if (std::filesystem::remove(filePath, ec)) {
            std::cout << "File deleted successfully." << std::endl;
        } else {
            std::cerr << "Error deleting file: " << ec.message() << std::endl;
            return 1;
        }
    } else {
        std::cout << "File does not exist, no need to delete." << std::endl;
    }

    // Create a new text file
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << "This is a new file created after deletion." << std::endl;
        outFile.close();
        std::cout << "New file created and written successfully." << std::endl;
    } else {
        std::cerr << "Error creating file." << std::endl;
        return 1;
    }

    return 0;

}




int run_solver(int n_disks,int n_pegs,int debug, int status, int draw, int draw_moves,int print_moves){

        const char* debug_value = to_string(debug).data();
        if (setenv("DEBUG",debug_value,1) == 0){
          std::cout << "DEBUG SET TO " << debug_value << "\n";
        }else{
          std::cerr << " DID NOT SET DEBUG VARIABLE SUCCESFULLY. EXITING.." << std::endl;
          return 0;
        }

        const char* draw_value = to_string(draw).data();
        if (setenv("DRAW",draw_value,1) == 0){
          std::cout << "DRAW SET TO " << draw_value << "\n";
        }else{
          std::cerr << " DID NOT SET DRAW VARIABLE SUCCESFULLY. EXITING.." << std::endl;
          return 0;
        }

        const char* draw_moves_value = to_string(draw_moves).data();
        if (setenv("DRAW_MOVES",draw_moves_value,1) == 0){
          std::cout << "DRAW MOVES SET TO " << draw_moves<< "\n";
        }else{
          std::cerr << " DID NOT SET DRAW MOVES VARIABLE SUCCESFULLY. EXITING.." << std::endl;
          return 0;
        }

        const char* status_value = to_string(status).data();
        if (setenv("STATUS",status_value,1) == 0){
          std::cout << "STATUS SET TO " << draw_value << "\n";
        }else{
          std::cerr << " DID NOT SET STATUS VARIABLE SUCCESFULLY. EXITING.." << std::endl;
          return 0;
        }

        const char* print_moves1 = to_string(print_moves).data();
        if (setenv("PRINT_MOVES",print_moves1,1) == 0){
          std::cout << "DEBUG SET TO " << print_moves1 << "\n";
        }else{
          std::cerr << " DID NOT PRINT MOVE VARIABLE SUCCESFULLY. EXITING.." << std::endl;
          return 0;
        }



        Iterative_Solution is = Iterative_Solution();
        is.setup_game(n_disks,n_pegs);


        cout << "\nDRAWING INITIAL GAME STATUS\n";

        if(stoi(getenv("DRAW")) == 2){
          is.tower_game_manager.tower_game.draw_status();
        }
        if(stoi(getenv("DRAW")) == 1){
          is.tower_game_manager.tower_game.draw_line_status();
        }

        bool solved = is.general_solution_with_iteration();
        string solved_s = solved?"true":"false";
        std::cout << "\nSOLVED GAME: " << solved_s  << "\n";

        //is.tower_game_manager.tower_game.print_status();

        //is.print_all_game_moves();

        //if(strcmp(getenv("DRAW"), "2") ==0){
        std::cout << "\nDRAWING FINAL GAME STATUS\n";
        if(stoi(getenv("DRAW")) == 2){
          is.tower_game_manager.tower_game.draw_status();
        }
        if(stoi(getenv("DRAW")) == 1){
          is.tower_game_manager.tower_game.draw_line_status();
        }

        if(stoi(getenv("PRINT_MOVES")) == 1){
          is.print_all_game_moves();
        }

        return 0;

}