#include <iostream>
#include <fstream>
#include <deque>

const static std::string path = "./Data/";
const static std::string match_fname = "match_2_cpp.txt";

int32_t evaluate_score(std::string window, std::string query) {
    int32_t score = 0;
    for (size_t i = 0; i < query.size(); i++) {
        int32_t char_score = window[i] == query[i] ? 3 : -3;
        score += char_score;
    }
    return score;
}

int main(int argc, char ** argv) {

    std::string fname = "data.txt";
    std::string query = "CACCA";
    bool only_exact = false;

    if(argc > 1){
        query = std::string(argv[1]);
    }
    if(argc > 2) {
        fname = std::string(argv[2]) + ".txt";
    }
    if(argc > 3) {
        only_exact = std::stoi(argv[3]);
    }
    
    std::cout << "Looking for query " + query + " in file " + fname << std::endl;

    std::ifstream data_file(path + fname);
    std::ofstream match_file(path + match_fname);

    std::string moving_window(query.length(), 'x');                                           
    int32_t read_chars = 0;

    while(data_file.good()) {
        data_file.read(&moving_window[0], query.length());

        read_chars += query.length();
        if (read_chars % 100000 == 0) {
            std::cout << "Read " + std::to_string(read_chars) << std::endl;
        }

        int32_t score = evaluate_score(moving_window, query);
        if(score >= 3) {
            if((only_exact && score == 3 * query.length()) || !only_exact) {
                uint32_t cur_pos = data_file.tellg();
                match_file << cur_pos << "\t" + moving_window + "\t" << score << std::endl;
            }
        }
        
        data_file.seekg(1 - query.length(), std::ios::cur);

    }
    

    data_file.close();
    match_file.close();

    return 0;

}