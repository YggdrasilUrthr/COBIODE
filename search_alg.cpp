#include <iostream>
#include <fstream>
#include <deque>

const static std::string path = "./Data/";

int32_t evaluate_score(std::deque<char> window, std::string query) {
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

    std::deque<char> moving_window;                                           
    std::deque<int32_t> cumsums;                                    // Contains cumulative sums, in order: {previous 2, previous, current}

    while(data_file.good()) {
        char in_char;
        data_file.get(in_char);

        //int32_t test = cumsums.size() > 0 ? cumsums.front() : -70;

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

        if(cumsums[1] <= 0) {
            moving_window.clear();
            cumsums.clear();
            continue;
        }
        

        if(cumsums[0] < cumsums[1] && cumsums[2] < cumsums[1]) {        // Maximum condition
            data_file.seekg(-11, std::ios::cur);
            std::string last_chars(10, 'x');
            data_file.read(&last_chars[0], 10); 
            std::cout << data_file.tellg() << "\t" << cumsums[1] << "\t" + last_chars << std::endl;
            moving_window.clear();
            cumsums.clear();
        }
    }
    

    data_file.close();

    return 0;

}