#include <iostream>
#include <fstream>
#include <deque>

const static std::string path = "./Data/";
const static std::string match_fname = "match_cpp.txt";

int32_t evaluate_score(std::deque<char> window, std::string query) {
    int32_t score = 0;
    for (size_t i = 0; i < query.size(); i++) {
        uint32_t window_idx = window.size() - 1 - i;                    // deque is reversed => last character is the first read!!
        int32_t char_score = window[window_idx] == query[i] ? 3 : -3;
        score += char_score;
    }
    return score;
}

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

    if(argc > 1){
        query = std::string(argv[1]);
    }
    if(argc > 2) {
        fname = std::string(argv[2]) + ".txt";
    }
    
    std::cout << "Looking for query " + query + " in file " + fname << std::endl;

    std::ifstream data_file(path + fname);
    std::ofstream match_file(path + match_fname);

    std::deque<char> moving_window;                                           
    std::deque<int32_t> cumsums;                                    // Contains cumulative sums, in order: {previous 2, previous, current}

    int32_t read_chars = 0;

    while(data_file.good()) {
        char in_char;
        data_file.get(in_char);

        read_chars++;
        if (read_chars % 100000 == 0) {
            std::cout << "Read " + std::to_string(read_chars) << std::endl;
        }

        if(moving_window.size() != query.length()) {
            moving_window.push_front(in_char); // pop_back
            if(moving_window.size() == query.length()) {
                cumsums.push_front(evaluate_score(moving_window, query));
            }
            continue;
        }
        moving_window.pop_back();
        moving_window.push_front(in_char);
        if(cumsums.size() != 3) {
            cumsums.push_front(evaluate_score(moving_window, query) + cumsums.front());
            continue;        
        }

        cumsums.pop_back();
        cumsums.push_front(evaluate_score(moving_window, query) + cumsums.front());

        if(cumsums[0] < cumsums[1] && cumsums[2] < cumsums[1]) {        // Maximum condition
            uint32_t cur_pos = data_file.tellg();
            data_file.seekg(-(query.length() + 1), std::ios::cur);
            std::string last_chars(query.length(), 'x');
            data_file.read(&last_chars[0], query.length()); 
            match_file << data_file.tellg() << "\t" << cumsums[1] << "\t" + last_chars + "\t" << evaluate_score(last_chars, query) << std::endl;
            int32_t last_sum = cumsums.front();
            cumsums.clear();
            cumsums.push_front(last_sum);
            data_file.seekg(cur_pos);
        }
    }
    

    data_file.close();
    match_file.close();

    return 0;

}